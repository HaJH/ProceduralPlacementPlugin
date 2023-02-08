// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralDataAssetWidget.h"
#include "ProceduralPlacement.h"

#include "PropertyEditorModule.h"
#include "PropertyCustomizationHelpers.h"
#include "ProceduralPlacementData.h"

TSharedRef<SWidget> UProceduralDataAssetWidget::RebuildWidget()
{
	
	return SNew(SObjectPropertyEntryBox)
		.AllowedClass(UProceduralPlacementData::StaticClass())
		.OnObjectChanged_UObject(this, &UProceduralDataAssetWidget::OnAssetChanged)
		.ObjectPath_UObject(this, &UProceduralDataAssetWidget::GetCurrentAssetPath)
		;
}

void UProceduralDataAssetWidget::OnAssetChanged(const FAssetData& ChangedAsset)
{
	CurrentAsset = ChangedAsset;
	UProceduralPlacement::Get()->OnDataChanged(CurrentAsset);
}

FString UProceduralDataAssetWidget::GetCurrentAssetPath() const
{
	return CurrentAsset.IsValid() ? CurrentAsset.ObjectPath.ToString() : FString("");
}
