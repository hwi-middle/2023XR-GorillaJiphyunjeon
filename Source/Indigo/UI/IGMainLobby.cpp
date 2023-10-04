// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMainLobby.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/UI/IGMainLobbyWidget.h"

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
	AActor::BeginPlay();
	MainLobbyWidget = CreateWidget<UIGMainLobbyWidget>(GetWorld(), MainLobbyWidgetClass);
	if(MainLobbyWidget)
	{
		MainLobbyWidget->AddToViewport();
	}
}
