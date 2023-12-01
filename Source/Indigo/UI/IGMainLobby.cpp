// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMainLobby.h"

#include "Indigo/IGGameInstance.h"
#include "Indigo/Inventory/IGPlayerInventory.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/UI/IGMainLobbyWidget.h"
#include "Kismet/GameplayStatics.h"

AIGMainLobby::AIGMainLobby()
{
	FIGConstructorHelper::FindClassAndInitialize<UIGMainLobbyWidget>(TEXT("/Game/_GorillaJiphyunjeon/UI/MainLobbyUI/MainLobby.MainLobby_C"),
		[&](TSubclassOf<UIGMainLobbyWidget> Class)
		{
			MainLobbyWidgetClass = Class;
		});


}

AIGMainLobby::~AIGMainLobby()
{
	
}

void AIGMainLobby::BeginPlay()
{
	Super::BeginPlay();
	UIGGameInstance* GameInstance = Cast<UIGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->bIsBossRoomEnterSequenceDisplayed = false;
	GameInstance->bIsBossTutorialDisplayed = false;
	GameInstance->bIsControlTutorialDisplayed = false;
	GameInstance->PlayerInventory->InitInventory();
	
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->bShowMouseCursor = true;
	Controller->bEnableMouseOverEvents = true;
	Controller->bEnableClickEvents = true;
	
	MainLobbyWidget = CreateWidget<UIGMainLobbyWidget>(GetWorld(), MainLobbyWidgetClass);
	if(MainLobbyWidget)
	{
		MainLobbyWidget->AddToViewport();
	}
}
