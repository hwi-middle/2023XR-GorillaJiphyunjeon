// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGQuest.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "Components/TextBlock.h"


UIGQuest::UIGQuest(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UIGQuest::InitQuest(UQuest* InQuest)
{
	QuestTitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Quest_Title_Text")));	
	QuestSummaryText1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("Quest_Summary_Text_1")));
	QuestSummaryText2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("Quest_Summary_Text_2")));
	
	 if(InQuest == nullptr)
	 {
	 	return;
	 }
	if(QuestTitleText == nullptr)
	{
		return;
	}
	QuestTitleText->SetText(FText::FromString(InQuest->QuestTitle));	
	QuestSummaryText1->SetText(FText::FromString(InQuest->QuestSummaryArray[0]));	
	QuestSummaryText2->SetText(FText::FromString(InQuest->QuestSummaryArray[1]));	
}

void UIGQuest::NativeConstruct()
{
	Super::NativeConstruct();

	QuestTitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Quest_Title_Text")));	
	QuestSummaryText1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("Quest_Summary_Text_1")));
	QuestSummaryText2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("Quest_Summary_Text_2")));
	
	
}

void UIGQuest::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	UQuest* GetQuest = Cast<UQuest>(ListItemObject);
		if(GetQuest == nullptr)
	{
		return;
	}
	QuestTitleText->SetText(FText::FromString(GetQuest->QuestTitle));	
	QuestSummaryText1->SetText(FText::FromString(GetQuest->QuestSummaryArray[0]));	
	QuestSummaryText2->SetText(FText::FromString(GetQuest->QuestSummaryArray[1]));	
	
}
