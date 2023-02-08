// // Copyright 2019-2020 JackTo, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralPlacementMethod.h"
#include "PPM_DeleteDuplication.generated.h"

/**
 * 
 */
UCLASS()
class UPPM_DeleteDuplication : public UProceduralPlacementMethod
{
	GENERATED_BODY()
public:
	virtual AActor* RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass) override;
};
