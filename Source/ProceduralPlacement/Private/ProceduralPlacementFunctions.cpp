// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralPlacementFunctions.h"
#include "ProceduralFoliageBlockingVolume.h"
#include "ProceduralPlacement.h"
#include "ProceduralPlacementData.h"

#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"
#include "Components/BrushComponent.h"

#include "BSPOps.h"

#include "Kismet/GameplayStatics.h"
#include "Editor.h"
#include "Builders/CubeBuilder.h"

#define LOCTEXT_NAMESPACE "FProceduralPlacement"

namespace ProceduralPlacement
{
	UWorld* GetWorldInEditor()
	{
		return GEditor->GetEditorWorldContext().World();
	}

	ULevel* GetCurrentLevel()
	{
		ULevel* CurrentLevel = GetWorldInEditor()->GetCurrentLevel();
		if (CurrentLevel->IsValidLowLevelFast() == false)
		{
			CurrentLevel = nullptr;
		}
		return CurrentLevel;
	}


	// Copied from ActorFactory.cpp
	// Helper function for the volume actor factories, not sure where it should live
	void CreateBrushForVolumeActor(AVolume* NewActor, UBrushBuilder* BrushBuilder)
	{
		if (NewActor != NULL)
		{
			// this code builds a brush for the new actor
			NewActor->PreEditChange(NULL);

			NewActor->PolyFlags = 0;
			NewActor->Brush = NewObject<UModel>(NewActor, NAME_None, RF_Transactional);
			NewActor->Brush->Initialize(nullptr, true);
			NewActor->Brush->Polys = NewObject<UPolys>(NewActor->Brush, NAME_None, RF_Transactional);
			NewActor->GetBrushComponent()->Brush = NewActor->Brush;
			if (BrushBuilder != nullptr)
			{
				NewActor->BrushBuilder = DuplicateObject<UBrushBuilder>(BrushBuilder, NewActor);
			}

			BrushBuilder->Build(NewActor->GetWorld(), NewActor);

			FBSPOps::csgPrepMovingBrush(NewActor);

			// Set the texture on all polys to NULL.  This stops invisible textures
			// dependencies from being formed on volumes.
			if (NewActor->Brush)
			{
				for (int32 poly = 0; poly < NewActor->Brush->Polys->Element.Num(); ++poly)
				{
					FPoly* Poly = &(NewActor->Brush->Polys->Element[poly]);
					Poly->Material = NULL;
				}
			}

			NewActor->PostEditChange();
		}
	}
}

using namespace ProceduralPlacement;



void UProceduralPlacementFunctions::RunProceduralPlacement()
{
	UProceduralPlacement::Get()->Run();
}

float UProceduralPlacementFunctions::GetRandomFloat()
{
	return UProceduralPlacement::Get()->RandomStream.FRand();
}

float UProceduralPlacementFunctions::GetRandomFloatRange(float Min, float Max)
{
	return UProceduralPlacement::Get()->RandomStream.FRandRange(Min, Max);
}

//void UProceduralPlacementFunctions::DeleteAllActors(UClass* ActorClass)
//{
//	UWorld* World = GetWorldInEditor();
//	ensure(World);
//	if (World == nullptr)
//	{
//		return;
//	}
//	TArray<AActor*> Actors;
//	UGameplayStatics::GetAllActorsOfClass(World, ActorClass, Actors);
//
//	FScopedSlowTask SpawnVolumeTask(Actors.Num(), LOCTEXT("DeleteActorsText", "Delete Actors..."));
//	SpawnVolumeTask.MakeDialog();
//
//	for (AActor* Actor : Actors)
//	{
//		SpawnVolumeTask.EnterProgressFrame();
//		Actor->Destroy(true, true);
//	}
//
//	World->Modify();
//}
//
//void UProceduralPlacementFunctions::SpawnProceduralFoliageBlockingVolume(float BoundScale)
//{
//	UWorld* World = GetWorldInEditor();
//	ensure(World);
//	if (World == nullptr)
//	{
//		return;
//	}
//
//	TArray<AActor*> AllActors;
//	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), AllActors);
//
//	FScopedSlowTask SpawnVolumeTask(AllActors.Num(), LOCTEXT("SpawnPFBVText", "Spawn Volumes..."));
//	SpawnVolumeTask.MakeDialog();
//
//	for (AActor* TargetActor : AllActors)
//	{
//		SpawnVolumeTask.EnterProgressFrame();
//		//If it is level bound or another volume
//		if (TargetActor->GetClass()->IsChildOf<ALevelBounds>() ||
//			TargetActor->GetClass()->IsChildOf<AVolume>())
//		{
//			continue;
//		}
//
//
//		FVector Origin, Extent;
//		TargetActor->GetActorBounds(false, Origin, Extent);
//
//
//		//FActorSpawnParameters SpawnParams;
//		//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//		//AProceduralFoliageBlockingVolume* SpawnedVolume = World->SpawnActor<AProceduralFoliageBlockingVolume>(
//		//	AProceduralFoliageBlockingVolume::StaticClass(),
//		//	FTransform(Origin),
//		//	SpawnParams
//		//	);
//
//		if (Origin.IsZero() || Extent.IsZero() || Extent.X == 0 || Extent.Y ==0 || Extent.Z == 0)
//		{
//			continue;
//		}
//		UCubeBuilder* Builder = NewObject<UCubeBuilder>();
//		float Bound = 2 * BoundScale;
//		Builder->X = Extent.X * Bound;
//		Builder->Y = Extent.Y * Bound;
//		Builder->Z = Extent.Z * Bound;
//		//CreateBrushForVolumeActor(SpawnedVolume, Builder);
//	}
//}


#undef LOCTEXT_NAMESPACE