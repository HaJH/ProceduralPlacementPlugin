// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ProceduralAction_RotateRandomly.h"
#include "GameFramework/Actor.h"

void UProceduralAction_RotateRandomly::RunProceduralAction_Implementation(FProceduralPlacementActionArgs ActionArg, FRandomStream& RandomStream, AActor* TargetActor, AActor* SpawnedActor)
{
	float Roll = RandomStream.FRandRange(0, 360);
	float Pitch = RandomStream.FRandRange(0, 360);
	float Yaw = RandomStream.FRandRange(0, 360);

	FRotator Rot(Pitch, Yaw, Roll);
	SpawnedActor->SetActorRotation(Rot);
}
