// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralPlacementMethod.h"

AActor* UProceduralPlacementMethod::RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass)
{
	UE_LOG(LogClass, Error, TEXT("Please implement this function at derived class. (UProceduralPlacementMethod::RunProceduralMethod)"));
	return nullptr;
}

FText UProceduralPlacementMethod::GetMethodDescription_Implementation()
{
	FString Text = FString::Printf(TEXT("ProceduralPlacementMethod"));
	return FText::FromString(Text);
}
