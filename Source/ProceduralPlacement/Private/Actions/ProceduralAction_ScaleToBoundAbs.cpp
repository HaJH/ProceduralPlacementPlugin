// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ProceduralAction_ScaleToBoundAbs.h"
#include "ProceduralPlacementFunctions.h"
#include "Builders/CubeBuilder.h"
#include "GameFramework/Volume.h"

using namespace ProceduralPlacement;

void UProceduralAction_ScaleToBoundAbs::RunProceduralAction_Implementation(FProceduralPlacementActionArgs ActionArg, FRandomStream& RandomStream, AActor* TargetActor, AActor* SpawnedActor)
{
	if (SpawnedActor == nullptr || SpawnedActor->IsValidLowLevelFast() == false || TargetActor == nullptr || TargetActor->IsValidLowLevelFast() == false)
		return;

	FVector Origin, Extent;
	TargetActor->GetActorBounds(false, Origin, Extent);

	//if (Extent.IsZero() || Extent.X == 0 || Extent.Y == 0 || Extent.Z == 0)
	//{
	//	UE_LOG(LogClass, Error, TEXT("ProceduralAction_ScaleToBoundAbs:: Target( %s ) has invalid bound."), *TargetActor->GetName());
	//	return;
	//}

	float BoundScale = ActionArg.ActionValue;
	float BoundScaleAbs = ActionArg.ActionValueMax;
	
	UCubeBuilder* Builder = NewObject<UCubeBuilder>();
	float Bound = 2 * BoundScale;
	Builder->X = Extent.X * Bound;
	Builder->Y = Extent.Y * Bound;
	Builder->Z = Extent.Z * Bound + BoundScaleAbs;

	if (Builder->X == 0)
		Builder->X = 1;
	if (Builder->Y == 0)
		Builder->Y = 1;

	if (AVolume* Volume = Cast<AVolume>(SpawnedActor))
	{
		CreateBrushForVolumeActor(Volume, Builder);
		Volume->AddActorWorldOffset(FVector(0, 0, -BoundScaleAbs / 2.0f));
	}
}
