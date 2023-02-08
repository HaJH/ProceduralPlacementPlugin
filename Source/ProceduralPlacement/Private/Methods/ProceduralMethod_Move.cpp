// Fill out your copyright notice in the Description page of Project Settings.


#include "Methods/ProceduralMethod_Move.h"

#include "Engine/World.h"
#include "Engine/Level.h"
#include "Engine/LevelBounds.h"

#include "Kismet/GameplayStatics.h"
#include "AssetData.h"
#include "AssetRegistryModule.h"

#include "GameFramework/Info.h"
#include "InstancedFoliageActor.h"
#include "LandscapeGizmoActor.h"
#include "GameFramework/DefaultPhysicsVolume.h"
#include "Engine/LevelScriptActor.h"
#include "NavigationData.h"
#include "LandscapeProxy.h"

#include "ProceduralPlacementFunctions.h"

using namespace ProceduralPlacement;

AActor* UProceduralMethod_Move::RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass)
{
	AActor* Actor = TargetActor;
	
	if (Actor->GetClass()->IsChildOf(AInfo::StaticClass()) ||
		Actor->GetClass()->IsChildOf(ABrush::StaticClass()) ||
		Actor->GetClass()->IsChildOf(ALevelBounds::StaticClass()) ||
		Actor->GetClass()->IsChildOf(ALevelScriptActor::StaticClass()) ||
		Actor->GetClass()->IsChildOf(ADefaultPhysicsVolume::StaticClass()) ||
		Actor->GetClass()->IsChildOf(ANavigationData::StaticClass()) ||
		Actor->GetClass()->IsChildOf(ALandscapeGizmoActor::StaticClass()) ||
		Actor->GetClass()->IsChildOf(ALandscapeProxy::StaticClass()) ||
		Actor->GetClass()->IsChildOf(AInstancedFoliageActor::StaticClass())
		)
	{
		UE_LOG(LogClass, Error, TEXT("Method_Move :: %s Skipped moving because of Class(%s)."), *Actor->GetName(), *Actor->GetClass()->GetName());
		return nullptr;
	}

	if (Actor->IsHiddenEd() || Actor->IsHidden())
	{
		UE_LOG(LogClass, Error, TEXT("Method_Move :: %s Skipped moving because of Visiblity."), *Actor->GetName());
		return nullptr;
	}

	Actor->ClearCrossLevelReferences();
	//Move ver.
	Actor->Rename((const TCHAR*)0, GetCurrentLevel()); //Set the outer of Actor to NewLevel
	GetCurrentLevel()->Actors.Add(Actor);
	
	return Actor;
}
