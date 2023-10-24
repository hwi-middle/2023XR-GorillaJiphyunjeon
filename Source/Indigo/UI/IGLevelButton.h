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

UCLASS()
class INDIGO_API UIGLevelButton : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> LevelButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> ButtonText;

protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION(BlueprintCallable)
	void MoveLevel();
	
};
