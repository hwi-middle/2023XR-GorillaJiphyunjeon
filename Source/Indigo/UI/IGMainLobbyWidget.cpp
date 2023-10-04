// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMainLobbyWidget.h"
#include "IGLevelButton.h"

void UIGMainLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameStartButton = Cast<UIGLevelButton>(GetWidgetFromName(TEXT("GameStartButton")));
	
}
