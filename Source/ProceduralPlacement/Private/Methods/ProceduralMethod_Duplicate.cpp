// Fill out your copyright notice in the Description page of Project Settings.


#include "Methods/ProceduralMethod_Duplicate.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "ProceduralPlacementFunctions.h"

#include "Engine/LevelBounds.h"
#include "GameFramework/Info.h"
#include "InstancedFoliageActor.h"
#include "LandscapeGizmoActor.h"
#include "GameFramework/DefaultPhysicsVolume.h"
#include "Engine/LevelScriptActor.h"
#include "NavigationData.h"
#include "LandscapeProxy.h"

using namespace ProceduralPlacement;

AActor* UProceduralMethod_Duplicate::RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass)
{
	if (TargetActor->GetClass()->IsChildOf(AInfo::StaticClass()) ||
		TargetActor->GetClass()->IsChildOf(ABrush::StaticClass()) ||
		TargetActor->GetClass()->IsChildOf(ALevelBounds::StaticClass()) ||
		TargetActor->GetClass()->IsChildOf(ALevelScriptActor::StaticClass()) ||
		TargetActor->GetClass()->IsChildOf(ADefaultPhysicsVolume::StaticClass()) ||
		TargetActor->GetClass()->IsChildOf(ANavigationData::StaticClass()) ||
		TargetActor->GetClass()->IsChildOf(ALandscapeGizmoActor::StaticClass()) ||
		TargetActor->GetClass()->IsChildOf(ALandscapeProxy::StaticClass()) ||
		TargetActor->GetClass()->IsChildOf(AInstancedFoliageActor::StaticClass())
		)
	{
		UE_LOG(LogClass, Error, TEXT("%s :: %s Skipped moving because of Class(%s)."), *TargetActor->GetName(), *TargetActor->GetClass()->GetName());
		return nullptr;
	}

	if (TargetActor->IsHiddenEd() || TargetActor->IsHidden())
	{
		UE_LOG(LogClass, Error, TEXT("%s :: %s Skipped moving because of Visiblity."), *TargetActor->GetName());
		return nullptr;
	}
	
	//Duplicate ver.
	FActorSpawnParameters SpawnParams;
	SpawnParams.Template = TargetActor;
	SpawnParams.Name = TargetActor->GetFName();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* SpawnedActor = World->SpawnActor<AActor>(TargetActor->GetClass(), SpawnParams);
	SpawnedActor->SetActorLabel(TargetActor->GetActorLabel());
	SpawnedActor->Rename((const TCHAR*)0, GetWorldInEditor()->GetCurrentLevel());
	SpawnedActor->ClearCrossLevelReferences();

	return SpawnedActor;
}
