// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGQuestList.h"
#include "Components/ListView.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "IGQuest.h"

UIGQuestList::UIGQuestList(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	QuestList = Cast<UListView>(GetWidgetFromName(TEXT("ListView")));	
}

void UIGQuestList::InitQuest(UQuest* InQuest)
{
	QuestList->AddItem(InQuest);
}

void UIGQuestList::NativeConstruct()
{
	Super::NativeConstruct();
	QuestList = Cast<UListView>(GetWidgetFromName(TEXT("ListView")));	
}
