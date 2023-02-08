// // Copyright 2019-2020 JackTo, Inc. All Rights Reserved.


#include "PPM_DeleteDuplication.h"
#include "Kismet/GameplayStatics.h"
#include "Editor.h"

AActor* UPPM_DeleteDuplication::RunProceduralMethod_Implementation(UWorld* World, AActor* TargetActor,
                                                                   TSubclassOf<AActor> SpawnClass)
{
	TArray<AActor*> Actors;
	TArray<AActor*> TargetActors;
	TargetActors.Reserve(10000);
	UGameplayStatics::GetAllActorsOfClass(TargetActor, AActor::StaticClass(), Actors);
	TMap<FVector, AActor*> ActorMap;
	ActorMap.Reserve(100000);
	TSet<AActor*> Already;

	TArray<AActor*> SameLocationActors;
	
	for(AActor* Actor : Actors)
	{
		if(Actor == nullptr || Actor->IsValidLowLevel() == false){ continue; }
		if(Actor->IsHidden() || Actor->IsHiddenEd() || Actor->GetActorLocation() == FVector::ZeroVector){continue;}
		if(Already.Contains(Actor)){continue;}

		if(ActorMap.Contains(Actor->GetActorLocation()) == false)
		{
			ActorMap.Emplace(Actor->GetActorLocation(), Actor);
			Already.Emplace(Actor);
		}
		else
		{
			//Test Loc and Scale
			//Test with same mesh
			AActor* PrevActor = *ActorMap.Find(Actor->GetActorLocation());
			if(PrevActor->GetActorLocation() != Actor->GetActorLocation() || PrevActor->GetActorRotation() != Actor->GetActorRotation() || PrevActor->GetActorScale() != Actor->GetActorScale())
			{
				continue;
			}
			
			UActorComponent* PrevComp = PrevActor->GetComponentByClass(UStaticMeshComponent::StaticClass());
			UActorComponent* CurComp = Actor->GetComponentByClass(UStaticMeshComponent::StaticClass());
			if(PrevComp == nullptr || CurComp == nullptr)
			{
				continue;
			}else
			{
				auto* PrevMeshComp = Cast<UStaticMeshComponent>(PrevComp);
				auto* CurMeshComp = Cast<UStaticMeshComponent>(CurComp);
				if(PrevMeshComp->GetStaticMesh() == CurMeshComp->GetStaticMesh())
				{
					TargetActors.Emplace(Actor);
				}
			}
		}
	}

	for(auto* Actor : TargetActors)
	{
		GEditor->SelectActor(Actor, true, false);
	}
	
	return nullptr;
}
