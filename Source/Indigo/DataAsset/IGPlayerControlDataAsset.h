// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Engine/DataAsset.h"
#include "IGPlayerControlDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGPlayerControlDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "InputMappingContext", DisplayName = "기본 IMC")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "InputAction", DisplayName = "이동")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "InputAction", DisplayName = "시선 처리")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "InputAction", DisplayName = "달리기")
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, Category = "InputAction", DisplayName = "상호작용")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, Category = "InputAction", DisplayName = "구르기")
	TObjectPtr<UInputAction> RollAction;

	UPROPERTY(EditAnywhere, Category = "InputAction", DisplayName = "공격")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, Category = "InputAction", DisplayName = "1번 결정 활성화")
	TObjectPtr<UInputAction> Crystal1Action;

	UPROPERTY(EditAnywhere, Category = "InputAction", DisplayName = "2번 결정 활성화")
	TObjectPtr<UInputAction> Crystal2Action;

	UPROPERTY(EditAnywhere, Category = "InputAction", DisplayName = "3번 결정 활성화")
	TObjectPtr<UInputAction> Crystal3Action;
	
	UPROPERTY(EditAnywhere, Category = "InputAction", DisplayName = "튜토리얼 창 띄우기")
	TObjectPtr<UInputAction> ShowTutorialWidget;
};
