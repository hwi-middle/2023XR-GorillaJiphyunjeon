// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/UI/IGExitButton.h"
#include "Components/Button.h"

UIGExitButton::UIGExitButton(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	
}

void UIGExitButton::GameExit()
{
	FPlatformMisc::RequestExit(true);
}

void UIGExitButton::NativeConstruct()
{
	Super::NativeConstruct();
	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("Exit")));
	ExitButton->OnClicked.AddDynamic(this, &UIGExitButton::GameExit);
}
