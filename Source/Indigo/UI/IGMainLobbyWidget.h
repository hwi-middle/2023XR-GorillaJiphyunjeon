// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGMainLobbyWidget.generated.h"

/**
 * 
 */

class UIGLevelButton;
class UIGExitButton;
class UIGOptionWidget;
class UButton;

UCLASS()
class INDIGO_API UIGMainLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UIGMainLobbyWidget(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeConstruct() override;

	void OpenCloseOptionWidget(); 
	
protected:
	UPROPERTY()
	TObjectPtr<UIGLevelButton> GameStartButton;
	
	UPROPERTY()
	TObjectPtr<UButton> OptionButton;
	
	UPROPERTY()
	TObjectPtr<UIGExitButton> ExitButton;
	
	UPROPERTY()
	TObjectPtr<UIGOptionWidget> OptionWidget;
	
	
};
