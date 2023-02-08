// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ProceduralAction_RotateRandomly.h"
#include "ProceduralAction_RotateYaw.generated.h"

/**
 *
 */
UCLASS()
class PROCEDURALPLACEMENT_API UProceduralAction_RotateYaw : public UProceduralAction_RotateRandomly
{
	GENERATED_BODY()
public:
	virtual void RunProceduralAction_Implementation(FProceduralPlacementActionArgs ActionArg, FRandomStream& RandomStream, AActor* TargetActor, AActor* SpawnedActor) override;

};
