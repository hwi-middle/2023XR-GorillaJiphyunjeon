// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGLevelButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UIGLevelButton::NativeConstruct()
{
	Super::NativeConstruct();

	LevelButton = Cast<UButton>(GetWidgetFromName(TEXT("LevelMoveButton")));
	
	ButtonText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ButtonName")));

	LevelButton->OnClicked.AddDynamic(this, & UIGLevelButton::MoveLevel);
	
}

void UIGLevelButton::MoveLevel()
{
	UGameplayStatics::OpenLevel(this, TEXT("Test"));
}
