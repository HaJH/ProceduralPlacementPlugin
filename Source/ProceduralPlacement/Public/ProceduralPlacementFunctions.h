// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Volume.h"
#include "ProceduralPlacementFunctions.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALPLACEMENT_API UProceduralPlacementFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "ProceduralPlacement", CallInEditor)
		static void RunProceduralPlacement();
	UFUNCTION(BlueprintPure, Category = "ProceduralPlacement", CallInEditor)
		static float GetRandomFloat();
	UFUNCTION(BlueprintPure, Category = "ProceduralPlacement", CallInEditor)
		static float GetRandomFloatRange(float Min, float Max);
	//UFUNCTION(BlueprintCallable, Category = "ProceduralPlacement")
	//	static void DeleteAllActors(UClass* ActorClass);
	//UFUNCTION(BlueprintCallable, Category = "ProceduralPlacement")
	//	static void SpawnProceduralFoliageBlockingVolume(float BoundScale = 1.0f);
};

namespace ProceduralPlacement
{
	UWorld* GetWorldInEditor();
	ULevel* GetCurrentLevel();
	PROCEDURALPLACEMENT_API void CreateBrushForVolumeActor(AVolume* NewActor, UBrushBuilder* BrushBuilder);
}
