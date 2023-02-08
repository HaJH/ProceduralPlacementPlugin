// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralPlacementCondition.h"
#include "ProceduralCondition_ChanceToRun.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALPLACEMENT_API UProceduralCondition_ChanceToRun : public UProceduralPlacementCondition
{
	GENERATED_BODY()
	
public:
	virtual bool GetProceduralCondition_Implementation(const FProceduralPlacementConditionArgs& ConditionArgs, FRandomStream& RandomStream, AActor* TargetActor) override;
};
