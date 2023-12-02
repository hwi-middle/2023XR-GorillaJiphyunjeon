// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGTutotialWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

UIGTutotialWidget::UIGTutotialWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}
void UIGTutotialWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Controller = UGameplayStatics::GetPlayerController(GWorld, 0);
	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("Confirm")));
	ConfirmButton->OnClicked.AddDynamic(this, &UIGTutotialWidget::CloseTutorialWidget);
	CloseTutorialWidget();
}

void UIGTutotialWidget::CloseTutorialWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	Controller->bShowMouseCursor = false;
	Controller->bEnableMouseOverEvents = false;
	Controller->bEnableClickEvents = false;	
	Controller->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::SetGamePaused(GWorld, false);
}

void UIGTutotialWidget::VisibleTutorialWidget()
{
	SetVisibility(ESlateVisibility::Visible);
	Controller->bShowMouseCursor = true;
	Controller->bEnableMouseOverEvents = true;
	Controller->bEnableClickEvents = true;
	Controller->SetInputMode(FInputModeGameAndUI());
	UGameplayStatics::SetGamePaused(GWorld, true);
}


