// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelBounds.h"
#include "Engine/LevelScriptActor.h"
#include "GameFramework/DefaultPhysicsVolume.h"
#include "GameFramework/Info.h"
#include "InstancedFoliageActor.h"
#include "LandscapeGizmoActor.h"
#include "LandscapeProxy.h"
#include "NavigationData.h"
#include "UObject/NoExportTypes.h"
#include "ProceduralPlacementData.generated.h"



/*
TODO : Condition
PerlinNoise
*/

USTRUCT(BlueprintType)
struct FProceduralPlacementConditionArgs
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement", meta = (AllowAbstract = "false"))
		TSubclassOf<class UProceduralPlacementCondition> Condition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		float ConditionValue;
	UPROPERTY(AdvancedDisplay, EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		bool bHasRange = false;
	UPROPERTY(AdvancedDisplay, EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement", meta = (EditCondition = "bHasRange"))
		float ConditionValueMax;
	UPROPERTY(AdvancedDisplay, EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		TArray<FSoftObjectPath> ConditionObjects;
};

USTRUCT(BlueprintType)
struct FProceduralPlacementActionArgs
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement", meta = (AllowAbstract = "false"))
		TSubclassOf<class UProceduralPlacementAction> Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		float ActionValue;
	UPROPERTY(AdvancedDisplay, EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		bool bHasRange = false;
	UPROPERTY(AdvancedDisplay, EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement", meta = (EditCondition = "bHasRange"))
		float ActionValueMax;
};

USTRUCT(BlueprintType)
struct FProceduralPlacementArgs
{
	GENERATED_BODY()
public:
	FProceduralPlacementArgs()
	{
		ExcludedActorClasses = 
		{
			AInfo::StaticClass(),
			ALevelBounds::StaticClass(),
			ALevelScriptActor::StaticClass(),
			ADefaultPhysicsVolume::StaticClass(),
			ANavigationData::StaticClass(),
			ALandscapeGizmoActor::StaticClass(),
			ALandscapeProxy::StaticClass(),
			AInstancedFoliageActor::StaticClass()
		};
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement", meta = (AllowAbstract = "false"))
		TSubclassOf<class UProceduralPlacementMethod> PlacementMethod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement", meta = (AllowAbstract = "false"))
		TSubclassOf<class AActor> TargetActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement", meta = (AllowAbstract = "false"))
		TArray<TSubclassOf<class AActor>> ExcludedActorClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement", meta = (AllowAbstract = "false"))
		TArray<TSubclassOf<class AActor>> SpawnActorClasses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		TSubclassOf<class AProceduralPlacementShape> Shape;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		TArray<FProceduralPlacementConditionArgs> Conditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		TArray<FProceduralPlacementActionArgs> Actions;
	UPROPERTY(AdvancedDisplay, EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		int32 Iteration = 1;
};

/**
 *
 */
UCLASS()
class PROCEDURALPLACEMENT_API UProceduralPlacementData : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(CallInEditor, Category = "ProceduralPlacement")
		void RandomSeed()
	{
		this->Seed = FMath::Rand();
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		int32 Seed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralPlacement")
		TArray<FProceduralPlacementArgs> Args;
};
