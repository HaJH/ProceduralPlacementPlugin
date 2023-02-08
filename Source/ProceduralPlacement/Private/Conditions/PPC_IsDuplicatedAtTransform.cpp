// // Copyright 2019-2020 JackTo, Inc. All Rights Reserved.


#include "Conditions/PPC_IsDuplicatedAtTransform.h"
#include "ProceduralPlacementData.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

bool UPPC_IsDuplicatedAtTransform::GetProceduralCondition_Implementation(const FProceduralPlacementConditionArgs& ConditionArgs, FRandomStream& RandomStream, AActor* TargetActor)
{
	if(TargetActor == nullptr) return false;
	UWorld* World = TargetActor->GetWorld();
	return false;
}

