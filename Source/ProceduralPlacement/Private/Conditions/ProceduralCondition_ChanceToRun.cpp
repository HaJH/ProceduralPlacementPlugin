// Fill out your copyright notice in the Description page of Project Settings.


#include "Conditions/ProceduralCondition_ChanceToRun.h"
#include "ProceduralPlacementData.h"

bool UProceduralCondition_ChanceToRun::GetProceduralCondition_Implementation(const FProceduralPlacementConditionArgs& ConditionArgs, FRandomStream& RandomStream, AActor* TargetActor)
{
	return RandomStream.FRand() < ConditionArgs.ConditionValue;
}
