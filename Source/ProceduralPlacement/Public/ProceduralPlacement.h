// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "IAssetTools.h"
#include "ProceduralPlacementModule.h"
#include "ProceduralPlacement.generated.h"

struct FProceduralPlacementArgs;
/**
 *
 */
UCLASS()
class PROCEDURALPLACEMENT_API UProceduralPlacement : public UObject
{
	GENERATED_BODY()

public:
	UProceduralPlacement();
	static UProceduralPlacement* Get();
	void Run();

	void OnDataChanged(const FAssetData& ChangedAsset);
private:
	class AProceduralPlacementShape* CreateProceduralShape(TSubclassOf<AProceduralPlacementShape> ShapeClass);
	TMap<UClass*, class UProceduralPlacementAction*> CreateProceduralActionObjects(FProceduralPlacementArgs Args);
	TMap<UClass*, class UProceduralPlacementCondition*> CreateProceduralConditionObjects(FProceduralPlacementArgs Args);
	bool IsExcludedActor(class AActor* TargetActor, FProceduralPlacementArgs Args);
	UClass* SelectSpawnClass(FProceduralPlacementArgs Args);
public:
	UPROPERTY(Transient)
		FRandomStream RandomStream;
protected:
	UPROPERTY(Transient)
		class UProceduralPlacementData* ProceduralData;
private:
	friend FProceduralPlacementModule;
	static void SetInstance(UProceduralPlacement* Inst);
	static UProceduralPlacement* Instance;
};
