// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/UI/IGOptionWidget.h"
#include "IGOptionSlide.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Indigo/Util/IGSaveOption.h"
#include "Kismet/GameplayStatics.h"

UIGOptionWidget::UIGOptionWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

void UIGOptionWidget::CloseOption()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UIGOptionWidget::OpenCredit()
{
	CreditPanel->SetVisibility(ESlateVisibility::Visible);
	OptionPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UIGOptionWidget::OpenSliderOption()
{
	CreditPanel->SetVisibility(ESlateVisibility::Hidden);
	OptionPanel->SetVisibility(ESlateVisibility::Visible);
}

void UIGOptionWidget::SaveOptionData()
{
	TObjectPtr<UIGSaveOption> OptionSaveData = Cast<UIGSaveOption>(UGameplayStatics::CreateSaveGameObject(UIGSaveOption::StaticClass()));
	OptionSaveData->BGMSound = BGM->GetBgmSoundValue();
	OptionSaveData->SFXSound = SFX->GetSFXSoundValue();
	OptionSaveData->MouseSensivity = Mouse->GetMouseSoundValue();
	UGameplayStatics::SaveGameToSlot(OptionSaveData, TEXT("Option"), 0);		
}

void UIGOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//슬라이더 옵션
	BGM = Cast<UIGOptionSlide>(GetWidgetFromName(TEXT("BGM")));
	BGM->SetSliderType(ESliderType::BGM);
	
	SFX = Cast<UIGOptionSlide>(GetWidgetFromName(TEXT("SFX")));
	SFX->SetSliderType(ESliderType::SFX);
	
	Mouse = Cast<UIGOptionSlide>(GetWidgetFromName(TEXT("Mouse")));
	Mouse->SetSliderType(ESliderType::MouseSensitivity);
	
	CreditButton = Cast<UButton>(GetWidgetFromName(TEXT("Credit")));
	CreditButton->OnClicked.AddDynamic(this, &UIGOptionWidget::OpenCredit);
	
	SaveButton = Cast<UButton>(GetWidgetFromName(TEXT("Save")));
	SaveButton->OnClicked.AddDynamic(this, &UIGOptionWidget::SaveOptionData);
	
	SliderOptionButton = Cast<UButton>(GetWidgetFromName(TEXT("SliderWidgetButton")));
	SliderOptionButton->OnClicked.AddDynamic(this, &UIGOptionWidget::OpenSliderOption);

	OptionCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("Close")));
	OptionCloseButton->OnClicked.AddDynamic(this, &UIGOptionWidget::CloseOption);
	
	CreditPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("CreditPan")));
	CreditPanel->SetVisibility(ESlateVisibility::Hidden);
	OptionPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("OptionPan")));

	SetVisibility(ESlateVisibility::Visible);
	OptionPanel->SetVisibility(ESlateVisibility::Visible);
	


}
