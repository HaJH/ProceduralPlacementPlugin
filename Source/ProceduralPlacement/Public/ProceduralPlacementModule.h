// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "IAssetTools.h"
#include "IAssetTypeActions.h"

class FToolBarBuilder;
class FMenuBuilder;

class FProceduralPlacementModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

protected:	
	/** Registers ProceduralPlacementData asset tool actions. */
	void RegisterAssetTools();
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
	void UnregisterAssetTools();
private:
	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	void OnMapChanged(UWorld* InWorld, EMapChangeType MapChangeType);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs, class UWidgetBlueprint* WidgetBlueprint);
	TSharedRef<class SWidget> CreateUtilityWidget(class UWidgetBlueprint* WidgetBlueprint);
private:
	UPROPERTY(Transient)
		class UProceduralPlacement* ProceduralPlacement;

	TSharedPtr<class FUICommandList> PluginCommands;

	TWeakPtr<SDockTab> CreatedTab;
	FSoftObjectPath LoadedUI;

	UPROPERTY(Transient)
		class UWidgetBlueprint* LoadedWidgetBlueprint;
	UPROPERTY(Transient)
		TSoftObjectPtr<class UEditorUtilityWidget> CreatedWidget;

	/** The collection of registered asset type actions. */
	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;
};

