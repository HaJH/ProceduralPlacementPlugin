// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralPlacementAction.h"
#include "ProceduralAction_ScaleRandomly.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALPLACEMENT_API UProceduralAction_ScaleRandomly : public UProceduralPlacementAction
{
	GENERATED_BODY()
public:
	virtual void RunProceduralAction_Implementation(FProceduralPlacementActionArgs ActionArg, FRandomStream& RandomStream, AActor* TargetActor, AActor* SpawnedActor) override;
};
