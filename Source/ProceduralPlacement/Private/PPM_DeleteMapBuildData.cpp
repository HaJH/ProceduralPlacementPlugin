// // Copyright 2019-2020 JackTo, Inc. All Rights Reserved.


#include "PPM_DeleteMapBuildData.h"
#include "Engine/MapBuildDataRegistry.h"

AActor* UPPM_DeleteMapBuildData::RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor,
	TSubclassOf<AActor> SpawnClass)
{
	auto Levels = World->GetLevels();
	for (auto* Level : Levels)
	{
		Level->MapBuildData = nullptr;
		Level->Modify();
	}
	return nullptr;
}
