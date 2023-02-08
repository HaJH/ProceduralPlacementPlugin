// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ProceduralAction_ScaleToBound.h"
#include "ProceduralPlacementFunctions.h"
#include "Builders/CubeBuilder.h"
#include "GameFramework/Volume.h"

using namespace ProceduralPlacement;

void UProceduralAction_ScaleToBound::RunProceduralAction_Implementation(FProceduralPlacementActionArgs ActionArg, FRandomStream& RandomStream, AActor* TargetActor, AActor* SpawnedActor)
{
	if (SpawnedActor == nullptr || SpawnedActor->IsValidLowLevelFast() == false || TargetActor == nullptr || TargetActor->IsValidLowLevelFast() == false)
		return;

	FVector Origin, Extent;
	TargetActor->GetActorBounds(false, Origin, Extent);

	//if (Extent.IsZero() || Extent.X == 0 || Extent.Y == 0 || Extent.Z == 0)
	//{
	//	UE_LOG(LogClass, Error, TEXT("ProceduralAction_ScaleToBound:: Target( %s ) has invalid bound."), *TargetActor->GetName());
	//	return;
	//}

	float BoundScale = 1.0f;
	if (ActionArg.bHasRange)
	{
		BoundScale = RandomStream.FRandRange(ActionArg.ActionValue, ActionArg.ActionValueMax);
	}
	else
	{
		BoundScale = ActionArg.ActionValue;
	}

	UCubeBuilder* Builder = NewObject<UCubeBuilder>();
	float Bound = 2 * BoundScale;
	Builder->X = Extent.X * Bound;
	Builder->Y = Extent.Y * Bound;
	Builder->Z = Extent.Z * Bound;

	if (Builder->X == 0)
		Builder->X = 1;
	if (Builder->Y == 0)
		Builder->Y = 1;

	if (AVolume* Volume = Cast<AVolume>(SpawnedActor))
	{
		CreateBrushForVolumeActor(Volume, Builder);
	}
	else
	{
		UE_LOG(LogClass, Error, TEXT("Scale transform instead of brush"));
		//Get SpawnedActor bound
		FVector SpawnedOrigin, SpawnedExtent;
		TargetActor->GetActorBounds(false, Origin, SpawnedExtent);
		//if (Extent.IsZero() || Extent.X == 0 || Extent.Y == 0 || Extent.Z == 0)
		//{
		//	UE_LOG(LogClass, Error, TEXT("ProceduralAction_ScaleToBound::Spawned Actor( %s ) has invalid bound."), *SpawnedActor->GetName());
		//	return;
		//}
		//Diff to target
		FVector Scale = FVector(Extent.X / SpawnedExtent.X, Extent.Y / SpawnedExtent.Y, Extent.Z / SpawnedExtent.Z);
		//Scale it
		SpawnedActor->SetActorScale3D(Scale);
	}
}
