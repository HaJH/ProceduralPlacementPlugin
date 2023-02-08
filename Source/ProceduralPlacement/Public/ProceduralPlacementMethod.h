// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "ProceduralPlacementMethod.generated.h"

/**
 *
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class PROCEDURALPLACEMENT_API UProceduralPlacementMethod : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "ProceduralPlacement", CallInEditor)
		AActor* RunProceduralMethod(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass);
	virtual AActor* RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass);

	UFUNCTION(BlueprintNativeEvent, Category = "ProceduralPlacement", CallInEditor)
		FText GetMethodDescription();
	virtual FText GetMethodDescription_Implementation();
};
