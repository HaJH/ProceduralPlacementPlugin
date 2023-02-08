// Fill out your copyright notice in the Description page of Project Settings.


#include "Shapes/ProceduralShape_BoundOrigin.h"

AProceduralShape_BoundOrigin::AProceduralShape_BoundOrigin() : Super()
{

}

FTransform AProceduralShape_BoundOrigin::GetProceduralTransform_Implementation(AActor* TargetActor/*, FRandomStream& Random*/)
{
	if (TargetActor == nullptr)
	{
		return FTransform();
	}

	FVector Origin, Extent;
	TargetActor->GetActorBounds(false, Origin, Extent);
	FTransform Transform;
	Transform.SetLocation(Origin);
	return Transform;
}
