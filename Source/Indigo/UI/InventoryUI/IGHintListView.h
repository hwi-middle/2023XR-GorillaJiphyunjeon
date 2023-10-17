// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGHintListView.generated.h"

class UListView;
struct FIGTextMasterDataTable;

UCLASS()
class INDIGO_API UIGHintListView : public UUserWidget
{
	GENERATED_BODY()
public:
	UIGHintListView(const FObjectInitializer& ObjectInitializer);
	void AddHint();
	
protected:
	virtual void NativeConstruct() override;	
	
private:
	UPROPERTY()
	TObjectPtr<UListView> HintList;

	
};
