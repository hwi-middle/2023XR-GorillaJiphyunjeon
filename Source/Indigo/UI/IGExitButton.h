// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGExitButton.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class INDIGO_API UIGExitButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UIGExitButton(const FObjectInitializer& ObjectInitializer);
	void GameExit();
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ExitButton;
};
