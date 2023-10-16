// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "IGQuest.generated.h"

class UTextBlock;
class UQuest;

UCLASS()
class INDIGO_API UIGQuest : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	UIGQuest(const FObjectInitializer& ObjectInitializer);
	void InitQuest(UQuest* InQuest);
	
protected:
	virtual void NativeConstruct() override;
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
private:
	UPROPERTY()
	TObjectPtr<class UTextBlock> QuestTitleText;
	
	UPROPERTY()
	TObjectPtr<class UTextBlock> QuestSummaryText1;
	
	UPROPERTY()
	TObjectPtr<class UTextBlock> QuestSummaryText2;
};
