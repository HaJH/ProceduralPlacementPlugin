// Fill out your copyright notice in the Description page of Project Settings.


#include "Conditions/ProceduralCondition_HasBound.h"
#include "GameFramework/Actor.h"

bool UProceduralCondition_HasBound::GetProceduralCondition_Implementation(const FProceduralPlacementConditionArgs& ConditionArgs, FRandomStream& RandomStream, AActor* TargetActor)
{
	if (TargetActor == nullptr || TargetActor->IsValidLowLevelFast() == false)
		return false;

	FVector Origin, Extent;
	TargetActor->GetActorBounds(false, Origin, Extent);
	if (Extent.IsZero() || Extent.X == 0 || Extent.Y == 0 || Extent.Z == 0)
	{
		return false;
	}

	return true;
}
