// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGTutotialWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class INDIGO_API UIGTutotialWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UIGTutotialWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void CloseTutorialWidget();
	UFUNCTION(BlueprintCallable)
	void VisibleTutorialWidget();
	
protected:
	virtual void NativeConstruct() override;

public:


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> ConfirmButton;

private:
	TObjectPtr<APlayerController> Controller;
};
