// Copyright Epic Games, Inc. All Rights Reserved.


#include "IndigoGameModeBase.h"

#include "Character/IGPlayerCharacter.h"
#include "Util/IGConstructorHelper.h"

AIndigoGameModeBase::AIndigoGameModeBase()
{
	FIGConstructorHelper::FindClassAndInitialize<AIGPlayerCharacter>(TEXT("/Game/_GorillaJiphyunjeon/Blueprint/BP_Player.BP_Player_C"), [&](TSubclassOf<AIGPlayerCharacter> CharacterClass)
	{
		DefaultPawnClass = CharacterClass;
	}, EAssertionLevel::Check);
	//DefaultPawnClass = AIGPlayerCharacter::StaticClass();
}
