// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGShinmyophilText.h"
#include "Components/TextBlock.h"

UIGShinmyophilText::UIGShinmyophilText(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UIGShinmyophilText::SetText(const FString InText)
{
	ChatterBoxText->SetText(FText::FromString(InText));
}

void UIGShinmyophilText::NativeConstruct()
{
	Super::NativeConstruct();
	ChatterBoxText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ShinmyophilText")));	
}
