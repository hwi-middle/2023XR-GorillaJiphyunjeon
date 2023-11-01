// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMainLobbyWidget.h"
#include "IGLevelButton.h"
#include "IGExitButton.h"
#include "IGOptionWidget.h"
#include "Components/Button.h"

UIGMainLobbyWidget::UIGMainLobbyWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	
}

void UIGMainLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameStartButton = Cast<UIGLevelButton>(GetWidgetFromName(TEXT("GameStartButton")));
	OptionButton = Cast<UButton>(GetWidgetFromName(TEXT("Option")));
	ExitButton = Cast<UIGExitButton>(GetWidgetFromName(TEXT("Exit")));
	OptionWidget = Cast<UIGOptionWidget>(GetWidgetFromName(TEXT("OptionWidget")));

	OptionWidget->SetVisibility(ESlateVisibility::Hidden);
	OptionButton->OnClicked.AddDynamic(this, &UIGMainLobbyWidget::OpenCloseOptionWidget);
}

void UIGMainLobbyWidget::OpenCloseOptionWidget()
{
	if(OptionWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		OptionWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else if(OptionWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		OptionWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
