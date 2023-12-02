// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "IGSaveOption.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGSaveOption : public USaveGame
{
	GENERATED_BODY()
public:
	UIGSaveOption(): SFXSound(0), BGMSound(0), MouseSensivity(0)
	{
	}

public:
	UPROPERTY()
	float SFXSound;
	
	UPROPERTY()
	float BGMSound;

	UPROPERTY()
	float MouseSensivity;
};
