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
	Controller->bShowMouseCursor = true;
	Controller->bEnableMouseOverEvents = true;
	Controller->bEnableClickEvents = true;
	
	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("Confirm")));
	ConfirmButton->OnClicked.AddDynamic(this, &UIGTutotialWidget::CloseTutorialWidget);
	SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GWorld, true);
}

void UIGTutotialWidget::CloseTutorialWidget()
{
	Controller->bShowMouseCursor = false;
	Controller->bEnableMouseOverEvents = false;
	Controller->bEnableClickEvents = false;

	UGameplayStatics::SetGamePaused(GWorld, false);
	SetVisibility(ESlateVisibility::Hidden);
}

void UIGTutotialWidget::VisibleTutorialWidget()
{
	Controller->bShowMouseCursor = true;
	Controller->bEnableMouseOverEvents = true;
	Controller->bEnableClickEvents = true;
	UGameplayStatics::SetGamePaused(GWorld, true);
	SetVisibility(ESlateVisibility::Visible);
}


