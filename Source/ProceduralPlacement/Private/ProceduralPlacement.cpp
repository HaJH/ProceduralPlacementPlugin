// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralPlacement.h"
#include "ProceduralPlacementData.h"
#include "ProceduralPlacementFunctions.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Editor.h"
#include "Misc/ScopedSlowTask.h"
#include "ProceduralPlacementShape.h"
#include "ProceduralPlacementMethod.h"
#include "ProceduralPlacementAction.h"
#include "Engine/LevelBounds.h"
#include "GameFramework/Info.h"
#include "ProceduralPlacementCondition.h"
#include "Engine/LevelScriptActor.h"
#include "GameFramework/DefaultPhysicsVolume.h"
#include "NavigationData.h"
#include "LandscapeGizmoActor.h"
#include "LandscapeProxy.h"
#include "InstancedFoliageActor.h"

#define LOCTEXT_NAMESPACE "FProceduralPlacement"

using namespace ProceduralPlacement;
UProceduralPlacement* UProceduralPlacement::Instance(nullptr);

UProceduralPlacement::UProceduralPlacement()
	:
	Super(),
	RandomStream(),
	ProceduralData(nullptr)
{

}

UProceduralPlacement* UProceduralPlacement::Get()
{
	return Instance;
}

void UProceduralPlacement::OnDataChanged(const FAssetData& ChangedAsset)
{
	ProceduralData = nullptr;
	if (ChangedAsset.IsValid())
	{
		UObject* Obj = ChangedAsset.GetAsset();
		if (Obj)
		{
			ProceduralData = Cast<UProceduralPlacementData>(Obj);
		}
	}
}

void UProceduralPlacement::Run()
{
	UE_LOG(LogClass, Log, TEXT("ProceduralPlacement::Run Placement"));
	if (ProceduralData == nullptr || ProceduralData->IsValidLowLevelFast() == false)
	{
		UE_LOG(LogClass, Error, TEXT("ProceduralPlacement::Invalid Data"));
		return;
	}

	RandomStream.Initialize(ProceduralData->Seed);
	UE_LOG(LogClass, Log, TEXT("ProceduralPlacement::Random Seed : %d"), ProceduralData->Seed);

	//For all procedural step of Data
	TArray<FProceduralPlacementArgs> PlacementArgs = ProceduralData->Args;
	for (const FProceduralPlacementArgs& PlacementArg : PlacementArgs)
	{
		if (PlacementArg.PlacementMethod == nullptr || PlacementArg.PlacementMethod->IsValidLowLevelFast() == false)
		{
			UE_LOG(LogClass, Error, TEXT("ProceduralPlacement::Method is null"));
			return;
		}

		//Create Method
		UProceduralPlacementMethod* Method = NewObject<UProceduralPlacementMethod>(GetTransientPackage(), PlacementArg.PlacementMethod);
		UE_LOG(LogClass, Log, TEXT("ProceduralPlacement::Method=%s"), *PlacementArg.PlacementMethod->GetName());

		//Collect target actor
		if (PlacementArg.TargetActorClass == nullptr || PlacementArg.TargetActorClass->IsValidLowLevelFast() == false)
		{
			UE_LOG(LogClass, Error, TEXT("ProceduralPlacement::TargetActorClass is null"));
			return;
		}
		UE_LOG(LogClass, Log, TEXT("ProceduralPlacement::Target Actor Class = %s"), *PlacementArg.PlacementMethod->GetName());

		UWorld* World = GetWorldInEditor();
		if (World == nullptr)
		{
			UE_LOG(LogClass, Error, TEXT("ProceduralPlacement::WorldInEditor is null"));
			return;
		}

		TArray<AActor*> TargetActors;
		UGameplayStatics::GetAllActorsOfClass(World, PlacementArg.TargetActorClass, TargetActors);
		UE_LOG(LogClass, Log, TEXT("ProceduralPlacement::Collected Target Actor Amount = %d"), TargetActors.Num());

		//Show task dialog
		FScopedSlowTask ProceduralMethodTask(TargetActors.Num(), LOCTEXT("ProceduralPlacement", "ProceduralPlacement"));
		ProceduralMethodTask.MakeDialog();

		//Prepare iteration - Create Condition, Action, Shape objects
		AProceduralPlacementShape* ProceduralShape = CreateProceduralShape(PlacementArg.Shape);
		TMap<UClass*, UProceduralPlacementAction*> Actions = CreateProceduralActionObjects(PlacementArg);
		TMap<UClass*, UProceduralPlacementCondition*> Conditions = CreateProceduralConditionObjects(PlacementArg);

		//Run procedural method to all target actors
		for (AActor* TargetActor : TargetActors)
		{
			ProceduralMethodTask.EnterProgressFrame(1.f, Method->GetMethodDescription());

			if (IsExcludedActor(TargetActor, PlacementArg))
			{
				continue;
			}

			bool bCondition = true;
			for (auto ConditionArgs : PlacementArg.Conditions)
			{
				UProceduralPlacementCondition* Condition = Conditions[ConditionArgs.Condition];
				bCondition &= Condition->GetProceduralCondition(ConditionArgs, RandomStream, TargetActor);
			}
			if (bCondition == false)
			{
				continue;
			}

			for (int i = 0; i < PlacementArg.Iteration; i++)
			{
				UClass* SpawnClass = SelectSpawnClass(PlacementArg);
				AActor* SpawnedActor = Method->RunProceduralMethod(World, TargetActor, SpawnClass);
				UE_LOG(LogClass, Log, TEXT("ProceduralPlacement:: Method = %s (%s, %s)"), *Method->GetName(), TargetActor ? *TargetActor->GetName() : *FString(), SpawnedActor ? *SpawnedActor->GetName() : *FString());

				if (SpawnedActor && ProceduralShape)
				{
					//Apply ProceduralShape ( mainly location )
					FTransform SpawnTransform = ProceduralShape->GetProceduralTransform(TargetActor/*, RandomStream*/);
					SpawnedActor->SetActorTransform(SpawnTransform);

					for (auto ActionArg : PlacementArg.Actions)
					{
						if(Actions.Contains(ActionArg.Action))
						{
							UProceduralPlacementAction* Action = Actions[ActionArg.Action];
							Action->RunProceduralAction(ActionArg, RandomStream, TargetActor, SpawnedActor);
						}
					}
				}
			}
		}

		if (ProceduralShape && ProceduralShape->IsPendingKill() == false)
		{
			ProceduralShape->Destroy();
		}
	}
}

AProceduralPlacementShape* UProceduralPlacement::CreateProceduralShape(TSubclassOf<AProceduralPlacementShape> ShapeClass)
{
	AProceduralPlacementShape* ProceduralShape = nullptr;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (ShapeClass != nullptr || ShapeClass->IsValidLowLevelFast())
	{
		ProceduralShape = GetWorldInEditor()->SpawnActor<AProceduralPlacementShape>(ShapeClass, SpawnParams);
	}
	else
	{
		ProceduralShape = GetWorldInEditor()->SpawnActor<AProceduralPlacementShape>(SpawnParams);
	}

	//ProceduralShape->SetRandomStream(&RandomStream);

	return ProceduralShape;
}

TMap<UClass*, UProceduralPlacementAction*> UProceduralPlacement::CreateProceduralActionObjects(FProceduralPlacementArgs Args)
{
	TMap<UClass*, class UProceduralPlacementAction*> ActionMap;
	for (auto ActionArg : Args.Actions)
	{
		if (ActionArg.Action == nullptr)
		{
			continue;
		}

		UProceduralPlacementAction* Action = NewObject<UProceduralPlacementAction>(GetTransientPackage(), ActionArg.Action);
		ActionMap.Emplace(ActionArg.Action, Action);
	}
	return ActionMap;
}

TMap<UClass*, UProceduralPlacementCondition*> UProceduralPlacement::CreateProceduralConditionObjects(FProceduralPlacementArgs Args)
{
	TMap<UClass*, class UProceduralPlacementCondition*> ConditionMap;
	for (auto Arg : Args.Conditions)
	{
		if (Arg.Condition == nullptr)
		{
			continue;
		}

		UProceduralPlacementCondition* Condition = NewObject<UProceduralPlacementCondition>(GetTransientPackage(), Arg.Condition);
		ConditionMap.Emplace(Arg.Condition, Condition);
	}
	return ConditionMap;
}

bool UProceduralPlacement::IsExcludedActor(AActor* TargetActor, FProceduralPlacementArgs Args)
{
	//Filter Target Actor Classes
	bool bFiltered = false;
	for (UClass* ExcludedClass : Args.ExcludedActorClasses)
	{
		bFiltered |= TargetActor->GetClass()->IsChildOf(ExcludedClass);
	}
	if (bFiltered)
	{
		return true;
	}

	return false;
}

UClass* UProceduralPlacement::SelectSpawnClass(FProceduralPlacementArgs Args)
{
	UClass* SpawnClass = nullptr;
	if (Args.SpawnActorClasses.Num() == 1)
	{
		SpawnClass = Args.SpawnActorClasses[0];
	}
	else if (Args.SpawnActorClasses.Num() > 1)
	{
		//int32 Index = RandomStream.RandRange(0, Args.SpawnActorClasses.Num() - 1);
		int32 Index = FMath::RandRange((int32)0, (int32)Args.SpawnActorClasses.Num() - 1);
		SpawnClass = Args.SpawnActorClasses[Index];
	}
	return SpawnClass;
}

void UProceduralPlacement::SetInstance(UProceduralPlacement* Inst)
{
	Instance = Inst;
	Instance->AddToRoot();
}


#undef LOCTEXT_NAMESPACE