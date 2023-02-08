// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralPlacementShape.h"
#include "Components/SceneComponent.h"

// Sets default values
AProceduralPlacementShape::AProceduralPlacementShape() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;
}

FTransform AProceduralPlacementShape::GetProceduralTransform_Implementation(AActor* TargetActor/*, FRandomStream& Random*/)
{
	if (TargetActor)
	{
		SetActorLocation(TargetActor->GetActorLocation());
	}

	return GetActorTransform();
}

//FRandomStream& AProceduralPlacementShape::GetRandomStream()
//{
//	return *RandomStream;
//}
