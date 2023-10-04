// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGLevelButton.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGLevelButton : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* LevelButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* ButtonText;

protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION(BlueprintCallable)
	void MoveLevel();
	
};
