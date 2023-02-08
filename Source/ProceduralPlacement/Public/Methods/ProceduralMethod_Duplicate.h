// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralPlacementMethod.h"
#include "ProceduralMethod_Duplicate.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALPLACEMENT_API UProceduralMethod_Duplicate : public UProceduralPlacementMethod
{
	GENERATED_BODY()
public:
	ULevel* GetCurrentLevel();
	AActor* RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass) override;
};
