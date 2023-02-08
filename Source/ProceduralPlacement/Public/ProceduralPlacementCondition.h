// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProceduralPlacementData.h"
#include "ProceduralPlacementCondition.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)
class PROCEDURALPLACEMENT_API UProceduralPlacementCondition : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, Category = ProceduralPlacement, CallInEditor)
		bool GetProceduralCondition(const FProceduralPlacementConditionArgs& ConditionArgs, FRandomStream& RandomStream, AActor* TargetActor);
	virtual bool GetProceduralCondition_Implementation(const FProceduralPlacementConditionArgs& ConditionArgs, FRandomStream& RandomStream, AActor* TargetActor);
};
