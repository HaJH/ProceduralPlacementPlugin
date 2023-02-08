// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ProceduralPlacementAssetActions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ProceduralPlacementData.h"
#include "Styling/SlateStyle.h"

//#include "TextAssetEditorToolkit.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"


///* FProceduralPlacementAssetActions constructors
// *****************************************************************************/
//
//FProceduralPlacementAssetActions::FProceduralPlacementAssetActions(const TSharedRef<ISlateStyle>& InStyle)
//	: Style(InStyle)
//{ }


/* FAssetTypeActions_Base overrides
 *****************************************************************************/

bool FProceduralPlacementAssetActions::CanFilter()
{
	return true;
}


void FProceduralPlacementAssetActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);
}

uint32 FProceduralPlacementAssetActions::GetCategories()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.FindAdvancedAssetCategory(FName("ProceduralPlacement"));
}

FText FProceduralPlacementAssetActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ProceduralPlacement", "ProceduralPlacement Data");
}


UClass* FProceduralPlacementAssetActions::GetSupportedClass() const
{
	return UProceduralPlacementData::StaticClass();
}

void FProceduralPlacementAssetActions::OpenAssetEditor(const TArray<::UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
}


FColor FProceduralPlacementAssetActions::GetTypeColor() const
{
	return FColor::Orange;
}


bool FProceduralPlacementAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}


//void FProceduralPlacementAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
//{
//	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
//		? EToolkitMode::WorldCentric
//		: EToolkitMode::Standalone;
//
//	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
//	{
//		auto TextAsset = Cast<UTextAsset>(*ObjIt);
//
//		if (TextAsset != nullptr)
//		{
//			TSharedRef<FTextAssetEditorToolkit> EditorToolkit = MakeShareable(new FTextAssetEditorToolkit(Style));
//			EditorToolkit->Initialize(TextAsset, Mode, EditWithinLevelEditor);
//		}
//	}
//}


#undef LOCTEXT_NAMESPACE
