// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProceduralPlacementModule.h"
#include "ProceduralPlacementStyle.h"
#include "ProceduralPlacementCommands.h"
#include "ProceduralPlacementData.h"
#include "ProceduralPlacement.h"

#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "WidgetBlueprint.h"
#include "EditorUtilityWidget.h"
#include "AssetToolsModule.h"
#include "AssetTools/ProceduralPlacementAssetActions.h"

static const FName ProceduralPlacementName("ProceduralPlacement");

#define LOCTEXT_NAMESPACE "FProceduralPlacementModule"

void FProceduralPlacementModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FProceduralPlacementStyle::Initialize();
	FProceduralPlacementStyle::ReloadTextures();

	FProceduralPlacementCommands::Register();

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAdvancedAssetCategory(ProceduralPlacementName, LOCTEXT("ProceduralPlacementCategoryText", "Procedural Placement"));
	RegisterAssetTools();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FProceduralPlacementCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FProceduralPlacementModule::PluginButtonClicked),
		FCanExecuteAction());

	CreatedWidget = nullptr;
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.OnMapChanged().AddRaw(this, &FProceduralPlacementModule::OnMapChanged);

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FProceduralPlacementModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FProceduralPlacementModule::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	LoadedUI = FSoftObjectPath("/ProceduralPlacement/ProceduralPlacementWidget.ProceduralPlacementWidget");
	UObject* Obj = LoadedUI.TryLoad();
	LoadedWidgetBlueprint = Cast<UWidgetBlueprint>(Obj);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ProceduralPlacementName, FOnSpawnTab::CreateRaw(this, &FProceduralPlacementModule::OnSpawnPluginTab, LoadedWidgetBlueprint))
		.SetDisplayName(LOCTEXT("FProceduralPlacementTabTitle", "ProceduralPlacement"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	//Make ProceduralPlacement Object
	ProceduralPlacement = NewObject<UProceduralPlacement>();
	UProceduralPlacement::SetInstance(ProceduralPlacement);
}

void FProceduralPlacementModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FProceduralPlacementStyle::Shutdown();

	FProceduralPlacementCommands::Unregister();

	if (CreatedTab.IsValid())
	{
		CreatedTab.Pin()->RequestCloseTab();
	}

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ProceduralPlacementName);

	UnregisterAssetTools();
}

TSharedRef<SDockTab> FProceduralPlacementModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs, UWidgetBlueprint* WidgetBlueprint)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab);
	TSharedRef<SWidget> TabWidget = CreateUtilityWidget(WidgetBlueprint);
	SpawnedTab->SetContent(TabWidget);
	CreatedTab = SpawnedTab;

	return SpawnedTab;
}

void FProceduralPlacementModule::PluginButtonClicked()
{
	if (CreatedTab.IsValid())
	{
		CreatedTab.Pin()->RequestCloseTab();
	}
	else
	{
		FGlobalTabmanager::Get()->TryInvokeTab(ProceduralPlacementName);
	}
}

TSharedRef<SWidget> FProceduralPlacementModule::CreateUtilityWidget(UWidgetBlueprint* WidgetBlueprint)
{
	UClass* BlueprintClass = WidgetBlueprint->GeneratedClass;
	UWorld* World = GEditor->GetEditorWorldContext().World();
	check(World);
	CreatedWidget = CreateWidget<UEditorUtilityWidget>(World, BlueprintClass);
	TSharedRef<SWidget> TabWidget = SNullWidget::NullWidget;
	if (CreatedWidget)
	{
		TSharedRef<SWidget> CreatedSlateWidget = CreatedWidget->TakeWidget();
		TabWidget = SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			[
				CreatedSlateWidget
			]
		;
	}
	return TabWidget;
}

void FProceduralPlacementModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FProceduralPlacementCommands::Get().OpenPluginWindow);
}

void FProceduralPlacementModule::OnMapChanged(UWorld* InWorld, EMapChangeType MapChangeType)
{
	if (MapChangeType == EMapChangeType::TearDownWorld)
	{
		if (CreatedTab.IsValid())
		{
			CreatedTab.Pin()->SetContent(SNullWidget::NullWidget);
		}
		if (CreatedWidget.Get())
		{
			//	Refer BlutilityModule OnMap Changed
			CreatedWidget->Rename(*CreatedWidget->GetName(), GetTransientPackage());
			CreatedWidget = nullptr;
		}
	}
	else if (MapChangeType != EMapChangeType::SaveMap)
	{
		// Recreate the widget if we are loading a map or opening a new map
		if (CreatedTab.IsValid())
		{
			TSharedRef<SWidget> TabWidget = CreateUtilityWidget(LoadedWidgetBlueprint);
			CreatedTab.Pin()->SetContent(TabWidget);
		}
	}
}

void FProceduralPlacementModule::RegisterAssetTools()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	RegisterAssetTypeAction(AssetTools, MakeShareable(new FProceduralPlacementAssetActions()));
}

void FProceduralPlacementModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	RegisteredAssetTypeActions.Add(Action);
}

void FProceduralPlacementModule::UnregisterAssetTools()
{
	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();

		for (auto Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}
}

void FProceduralPlacementModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FProceduralPlacementCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FProceduralPlacementModule, ProceduralPlacement)