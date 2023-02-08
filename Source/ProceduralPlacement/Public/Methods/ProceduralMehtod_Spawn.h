// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralPlacementMethod.h"
#include "ProceduralMehtod_Spawn.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALPLACEMENT_API UProceduralMehtod_Spawn : public UProceduralPlacementMethod
{
	GENERATED_BODY()
public:
	virtual AActor* RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass) override;
	virtual FText GetMethodDescription_Implementation() override;
};
