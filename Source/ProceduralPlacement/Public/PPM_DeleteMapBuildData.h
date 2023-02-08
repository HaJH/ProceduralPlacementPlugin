// // Copyright 2019-2020 JackTo, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralPlacementMethod.h"
#include "PPM_DeleteMapBuildData.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALPLACEMENT_API UPPM_DeleteMapBuildData : public UProceduralPlacementMethod
{
	GENERATED_BODY()
public:
	AActor* RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass) override;
};
