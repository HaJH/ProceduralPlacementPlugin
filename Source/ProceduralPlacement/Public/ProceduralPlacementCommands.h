// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ProceduralPlacementStyle.h"

class FProceduralPlacementCommands : public TCommands<FProceduralPlacementCommands>
{
public:

	FProceduralPlacementCommands()
		: TCommands<FProceduralPlacementCommands>(TEXT("ProceduralPlacement"), NSLOCTEXT("Contexts", "ProceduralPlacement", "ProceduralPlacement Plugin"), NAME_None, FProceduralPlacementStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};