// Fill out your copyright notice in the Description page of Project Settings.


#include "Methods/ProceduralMehtod_Spawn.h"

AActor* UProceduralMehtod_Spawn::RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* SpawnedActor = World->SpawnActor<AActor>(SpawnClass, SpawnParams);
	
	return SpawnedActor;
}

FText UProceduralMehtod_Spawn::GetMethodDescription_Implementation()
{
	return FText::FromString(FString::Printf(TEXT("Spawning Actor...")));
}
