// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGLevelButton.generated.h"

/**
 * 
 */



class UButton;
class UTextBlock;
class UIGSoundDataAsset;

UCLASS()
class INDIGO_API UIGLevelButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> LevelButton;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> ButtonText;

protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION(BlueprintCallable)
	void MoveLevel();
	UFUNCTION(BlueprintCallable)
	void OnTargetLevelLoaded();
	UFUNCTION(BlueprintCallable)
	void AsyncLevelLoad(const FString LevelDir, const FString& LevelName);
	UFUNCTION(BlueprintCallable)
	void AsyncLevelLoadFinished(const FString LevelName);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIGSoundDataAsset> SoundDataAsset;

	
};
