// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralPlacementShape.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PROCEDURALPLACEMENT_API AProceduralPlacementShape : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralPlacementShape();
	UFUNCTION(BlueprintNativeEvent, Category=ProceduralPlacement, CallInEditor)
		FTransform GetProceduralTransform(AActor* TargetActor/*, FRandomStream& Random*/);
	virtual FTransform GetProceduralTransform_Implementation(AActor* TargetActor/*, FRandomStream& Random*/);
	
	//void SetRandomStream(FRandomStream* Random) { RandomStream = Random; }
	//UFUNCTION(BlueprintPure, Category=ProceduralPlacement, CallInEditor)
	//	FRandomStream& GetRandomStream();

public:
	UPROPERTY(BlueprintReadOnly, Category = ProceduralPlacement, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* RootScene;
	FRandomStream* RandomStream;
};
