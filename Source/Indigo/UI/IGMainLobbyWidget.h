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

	UFUNCTION(BlueprintCallable)
	void OpenCloseOptionWidget(); 
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIGLevelButton> GameStartButton;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> OptionButton;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIGExitButton> ExitButton;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIGOptionWidget> OptionWidget;
	
	
};
