// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "IGPlayerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGPlayerDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	// 플레이어 능력치
	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "체력 최댓값")
	float MaxHp;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "스태미너 최댓값")
	float MaxStamina;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "걷기 속도")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "달리기 속도")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "구르기 속도")
	float RollSpeed;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "1타 데미지")
	int32 FirstAttackDamage;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "2타 데미지 데미지")
	int32 SecondAttackDamage;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "3타 데미지")
	int32 ThirdAttackDamage;

	// 증감값
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "1타 스태미너 소모량")
	float StaminaConsumptionAmountOnFirstAttack;

	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "2타 스태미너 소모량")
	float StaminaConsumptionAmountOnSecondAttack;
	
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "2타 스태미너 소모량")
	float StaminaConsumptionAmountOnThirdAttack;

	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "구르기 시 스태미너 소모량")
	float StaminaConsumptionAmountOnRoll;;
	
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "정지 시 초당 스태미너 회복량")
	float StaminaRecoveryAmountPerSecondOnIdle;
	
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "걷기 시 초당 스태미너 회복량")
	float StaminaRecoveryAmountPerSecondOnWalk;
	
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "달리기 시 초당 스태미너 소모량")
	float StaminaConsumptionAmountPerSecondOnRunning;
	
	// 기타 필요한 정보
	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "탈진 중 일월 게이지 획득 불가 시간")
	float ExhaustionPhase1Duration;

	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "탈진 중 일월 게이즈 획득 감소 시간")
	float ExhaustionPhase2Duration;

	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "죽음 기준 높이")
	float DieZLocation;

	//마우스 감도
	UPROPERTY(EditAnywhere, Category = "Mouse", DisplayName = "마우스 X감도")
	float MouseYawScale;

	UPROPERTY(EditAnywhere, Category = "Mouse", DisplayName = "마우스 Y감도")
	float MousePitchScale;	
};
