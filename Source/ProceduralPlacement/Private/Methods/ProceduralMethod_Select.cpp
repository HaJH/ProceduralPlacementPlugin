// Fill out your copyright notice in the Description page of Project Settings.


#include "Methods/ProceduralMethod_Select.h"
#include <Editor.h>
#include <Engine/Selection.h>

AActor* UProceduralMethod_Select::RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor, TSubclassOf<AActor> SpawnClass)
{
	GEditor->GetSelectedActors()->Select(TargetActor, true);
	return nullptr;
}