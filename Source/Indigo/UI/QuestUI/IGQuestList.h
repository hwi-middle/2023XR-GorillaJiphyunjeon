// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGQuestList.generated.h"

class UListView;
class UIGQuest;
class UQuest;

UCLASS()
class INDIGO_API UIGQuestList : public UUserWidget
{
	GENERATED_BODY()
public:
	UIGQuestList(const FObjectInitializer& ObjectInitializer);
	void InitQuest(UQuest* InQuest);
	
protected:
	virtual void NativeConstruct() override;

	
	
private:
	UPROPERTY()
	TObjectPtr<UListView> QuestList;
	
};
