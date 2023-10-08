// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMainLobby.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/UI/IGMainLobbyWidget.h"
#include "Kismet/GameplayStatics.h"

AIGMainLobby::AIGMainLobby()
{
	FIGConstructorHelper::FindClassAndInitialize<UIGMainLobbyWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_GorillaJiphyunjeon/UI/MainLobbyUI/MainLobby.MainLobby'"),
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
	
	UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = true;

	UGameplayStatics::GetPlayerController(this, 0)->bEnableMouseOverEvents = true;
	UGameplayStatics::GetPlayerController(this, 0)->bEnableClickEvents = true;
	
	MainLobbyWidget = CreateWidget<UIGMainLobbyWidget>(GetWorld(), MainLobbyWidgetClass);
	if(MainLobbyWidget)
	{
		MainLobbyWidget->AddToViewport();
	}
}
