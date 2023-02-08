// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ProceduralPlacementAssetFactoryNew.h"

#include "ProceduralPlacementData.h"


/* UProceduralPlacementAssetFactoryNew structors
 *****************************************************************************/

UProceduralPlacementAssetFactoryNew::UProceduralPlacementAssetFactoryNew(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UProceduralPlacementData::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}


/* UFactory overrides
 *****************************************************************************/

UObject* UProceduralPlacementAssetFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UProceduralPlacementData>(InParent, InClass, InName, Flags);
}


bool UProceduralPlacementAssetFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}
