// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UIGGameInstance();

	virtual void Init() override;
	
	UPROPERTY()
	uint8 bIsControlTutorialDisplayed : 1;

	UPROPERTY()
	uint8 bIsBossTutorialDisplayed : 1;

	UPROPERTY()
	uint8 bIsBossRoomEnterSequenceDisplayed : 1;
};
