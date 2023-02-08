// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ProceduralAction_RotateYaw.h"
#include <GameFramework/Actor.h>

void UProceduralAction_RotateYaw::RunProceduralAction_Implementation(FProceduralPlacementActionArgs ActionArg, FRandomStream& RandomStream, AActor* TargetActor, AActor* SpawnedActor)
{
	Super::RunProceduralAction_Implementation(ActionArg, RandomStream, TargetActor, SpawnedActor);
	SpawnedActor->SetActorRotation(FRotator(0, SpawnedActor->GetActorRotation().Yaw, 0));
}