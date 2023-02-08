// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ProceduralAction_ScaleRandomly.h"
#include "GameFramework/Actor.h"

void UProceduralAction_ScaleRandomly::RunProceduralAction_Implementation(FProceduralPlacementActionArgs ActionArg, FRandomStream& RandomStream, AActor* TargetActor, AActor* SpawnedActor)
{
	float Scale = 1.0f;
	if (ActionArg.bHasRange)
	{
		if (ActionArg.ActionValue != 0 || ActionArg.ActionValueMax != 0)
		{
			Scale = RandomStream.FRandRange(ActionArg.ActionValue, ActionArg.ActionValueMax);
		}
	}
	else
	{
		Scale = ActionArg.ActionValue != 0 ? ActionArg.ActionValue : 1.0f;
	}

	SpawnedActor->SetActorScale3D(FVector(Scale));
}
