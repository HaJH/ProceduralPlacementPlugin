// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProceduralPlacementCommands.h"

#define LOCTEXT_NAMESPACE "FProceduralPlacementModule"

void FProceduralPlacementCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ProceduralPlacement", "ProceduralPlacement", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
