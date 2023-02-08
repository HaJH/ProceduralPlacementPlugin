// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/ProceduralAction_ProjectToGround.h"
#include "Engine/World.h"

void UProceduralAction_ProjectToGround::RunProceduralAction_Implementation(FProceduralPlacementActionArgs ActionArg, FRandomStream& RandomStream, AActor* TargetActor, AActor* SpawnedActor)
{
	if (SpawnedActor == nullptr)
		return;
	
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(TargetActor);
	Params.AddIgnoredActor(SpawnedActor);

	SpawnedActor->GetWorld()->LineTraceSingleByChannel(
		Hit, SpawnedActor->GetActorLocation(),
		SpawnedActor->GetActorLocation() - FVector(0, 0, ActionArg.ActionValue),
		ECollisionChannel::ECC_Visibility,
		Params
	);

	if (Hit.bBlockingHit)
	{
		SpawnedActor->SetActorLocation(Hit.Location);
		SpawnedActor->SetActorRotation(Hit.ImpactNormal.Rotation());
	}
	else
	{
		UE_LOG(LogClass, Error, TEXT("Delete not projected actor! : %s"), *SpawnedActor->GetName());
		SpawnedActor->Destroy();
	}
}
