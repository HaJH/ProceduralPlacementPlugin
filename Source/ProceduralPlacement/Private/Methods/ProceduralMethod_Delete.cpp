// Fill out your copyright notice in the Description page of Project Settings.


#include "Methods/ProceduralMethod_Delete.h"

AActor* UProceduralMethod_Delete::RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass)
{
	if (TargetActor)
	{
		TargetActor->Destroy(true, true);
	}
	if (World)
	{
		World->Modify();
	}
	return nullptr;
}

FText UProceduralMethod_Delete::GetMethodDescription_Implementation()
{
	return FText::FromString(FString::Printf(TEXT("Deleting Actor...")));
}
