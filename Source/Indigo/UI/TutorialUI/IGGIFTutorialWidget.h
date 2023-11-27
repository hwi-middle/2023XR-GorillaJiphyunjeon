// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGGIFTutorialWidget.generated.h"

class UMediaSource;
class UCanvasPanel;
class UMediaPlayer;
class UMediaTexture;
class UButton;
class UCanvas;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class INDIGO_API UIGGIFTutorialWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UIGGIFTutorialWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void CloseGIFTutorialWidget();

	UFUNCTION(BlueprintCallable)
	void VisibleGIFTutorialWidget();

	UFUNCTION(BlueprintCallable)
	void SetTitle(const FText InTitle);

	UFUNCTION(BlueprintCallable)
	void SetDescription(const FText InDesctription);

	UFUNCTION(BlueprintCallable)
	void PreSetByFirstHealKit();
	
	UFUNCTION(BlueprintCallable)
	void PreSetByFirstCrystal();

	UFUNCTION(BlueprintCallable)
	void PreSetByFirstBoss();
	
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCanvasPanel> GIFTutorialCanvas;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TutorialTitle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TutorialDescription;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> TutorialGIF;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMediaPlayer> TutorialGIFPlayer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMediaSource> HealTutorialGIFSource;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMediaSource> CrystalTutorialGIFSource;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMediaSource> BossTutorialGIFSource;

	
private:
	UPROPERTY()
	TObjectPtr<APlayerController> Controller;

	

};
