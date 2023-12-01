// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGGameInstance.h"

#include "Inventory/IGPlayerInventory.h"

UIGGameInstance::UIGGameInstance()
{
	bIsControlTutorialDisplayed = false;
	bIsBossTutorialDisplayed = false;
	bIsBossRoomEnterSequenceDisplayed = false;
	PlayerInventory = CreateDefaultSubobject<UIGPlayerInventory>(TEXT("Inventory"));
}

void UIGGameInstance::Init()
{
	Super::Init();
}
