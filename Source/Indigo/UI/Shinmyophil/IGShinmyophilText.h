// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGShinmyophilText.generated.h"

class UTextBlock;

UCLASS()
class INDIGO_API UIGShinmyophilText : public UUserWidget
{
	GENERATED_BODY()

public:
	UIGShinmyophilText(const FObjectInitializer& ObjectInitializer);
	void SetText(const FString InText);
	
protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY()
	TObjectPtr<UTextBlock> ChatterBoxText;
	
};
