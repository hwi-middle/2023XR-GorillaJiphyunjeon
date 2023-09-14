// Copyright Epic Games, Inc. All Rights Reserved.


#include "IndigoGameModeBase.h"

#include "Character/IGPlayerCharacter.h"
#include "Util/IGConstructorHelper.h"

AIndigoGameModeBase::AIndigoGameModeBase()
{
	DefaultPawnClass = AIGPlayerCharacter::StaticClass();
}
