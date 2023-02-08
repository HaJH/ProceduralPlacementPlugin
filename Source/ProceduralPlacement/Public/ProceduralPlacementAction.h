// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProceduralPlacementData.h"
#include "ProceduralPlacementAction.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType)
class PROCEDURALPLACEMENT_API UProceduralPlacementAction : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = ProceduralPlacement, CallInEditor)
		void RunProceduralAction(FProceduralPlacementActionArgs ActionArg, FRandomStream& RandomStream, AActor* TargetActor, AActor* SpawnedActor);
	virtual void RunProceduralAction_Implementation(FProceduralPlacementActionArgs ActionArg, FRandomStream& RandomStream, AActor* TargetActor, AActor* SpawnedActor);
};
