// // Copyright 2019-2020 JackTo, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralPlacementCondition.h"
#include "PPC_IsDuplicatedAtTransform.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALPLACEMENT_API UPPC_IsDuplicatedAtTransform : public UProceduralPlacementCondition
{
	GENERATED_BODY()
public:
	bool GetProceduralCondition_Implementation(const FProceduralPlacementConditionArgs& ConditionArgs, FRandomStream& RandomStream, AActor* TargetActor) override;
};
