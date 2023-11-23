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
class UIGSoundDataAsset;
class UCanvasPanel;

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

	UFUNCTION(BlueprintCallable)
	void OpenGrayBoxTestLevel();

	UFUNCTION(BlueprintCallable)
	void OpenBossTestLevel();

	UFUNCTION(BlueprintCallable)
	void OpenWispTestLevel();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIGLevelButton> GameStartButton;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> OptionButton;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIGExitButton> ExitButton;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIGOptionWidget> OptionWidget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCanvasPanel> Loading;

	// 테스트용
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> TEST_GrayBoxButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> TEST_BossButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> TEST_WispButton;
	
private:
	// 사운드
	UPROPERTY()
	TObjectPtr<UIGSoundDataAsset> SoundDataAsset;
	
	UFUNCTION()
	void ShowLoading();
};
