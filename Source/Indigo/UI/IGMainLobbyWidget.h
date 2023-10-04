// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGMainLobbyWidget.generated.h"

/**
 * 
 */

class UIGLevelButton;

UCLASS()
class INDIGO_API UIGMainLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<UIGLevelButton> GameStartButton;
	
	
};
