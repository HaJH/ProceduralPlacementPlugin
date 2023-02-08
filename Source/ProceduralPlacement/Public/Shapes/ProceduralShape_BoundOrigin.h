// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralPlacementShape.h"
#include "ProceduralShape_BoundOrigin.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALPLACEMENT_API AProceduralShape_BoundOrigin : public AProceduralPlacementShape
{
	GENERATED_BODY()
public:
	AProceduralShape_BoundOrigin();
	virtual FTransform GetProceduralTransform_Implementation(AActor* TargetActor/*, FRandomStream& Random*/) override;
};
