// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/NativeWidgetHost.h"
#include "AssetData.h"

#include "ProceduralDataAssetWidget.generated.h"

/**
 *
 */
UCLASS()
class PROCEDURALPLACEMENT_API UProceduralDataAssetWidget : public UNativeWidgetHost
{
	GENERATED_BODY()
public:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	UFUNCTION()
		void OnAssetChanged(const FAssetData& ChangedAsset);
	UFUNCTION()
		FString GetCurrentAssetPath() const;
private:
	FAssetData CurrentAsset;
};
