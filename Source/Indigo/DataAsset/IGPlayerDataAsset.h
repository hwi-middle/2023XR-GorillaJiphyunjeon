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
	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "일월 게이지 최댓값")
	float MaxSunMoonValue;

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

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "일반 공격 최소 데미지")
	int32 NormalAttackDamageMin;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "일반 공격 최대 데미지")
	int32 NormalAttackDamageMax;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "강화 공격 최소 데미지")
	int32 StrongAttackDamageMin;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "강화 공격 최대 데미지")
	int32 StrongAttackDamageMax;

	// 증감값
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "적중 시 일월 게이지 회복량")
	float SunMoonRecoveryAmountOnAttackHit;
	
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "일반 공격 시 스태미너 소모량")
	float StaminaConsumptionAmountOnNormalAttack;

	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "강화 공격 시 스태미너 소모량")
	float StaminaConsumptionAmountOnStrongAttack;

	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "구르기 시 스태미너 소모량")
	float StaminaConsumptionAmountOnRoll;
	
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "강화공격 시 일월 게이지 소모량")
	float SunMoonConsumptionAmountOnAttack;
	
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "정지 시 초당 스태미너 회복량")
	float StaminaRecoveryAmountPerSecondOnIdle;
	
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "걷기 시 초당 스태미너 회복량")
	float StaminaRecoveryAmountPerSecondOnWalk;
	
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "달리기 시 초당 스태미너 소모량")
	float StaminaConsumptionAmountPerSecondOnRunning;
	
	UPROPERTY(EditAnywhere, Category = "Variance", DisplayName = "강화 상태에서 정지 시 일월 게이지 자동 소모량")
	float SunMoonAutoConsumptionAmount;
	
	// 기타 필요한 정보
	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "일월 게이지 2구간 임계값")
	float SunMoonSection2Threshold;

	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "일월 게이지 3구간 임계값")
	float SunMoonSection3Threshold;

	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "일월 게이지 1구간 데미지 배율")
	float SunMoonSection1DamageScaleFactor;

	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "일월 게이지 2구간 데미지 배율")
	float SunMoonSection2DamageScaleFactor;

	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "일월 게이지 3구간 데미지 배율")
	float SunMoonSection3DamageScaleFactor;
	
	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "탈진 중 일월 게이지 획득 불가 시간")
	float ExhaustionPhase1Duration;

	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "탈진 중 일월 게이즈 획득 감소 시간")
	float ExhaustionPhase2Duration;

	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "강화 상태에서 정지 시 일월 게이지 자동 소모 딜레이")
	float SunMoonAutoConsumptionDelay;

	UPROPERTY(EditAnywhere, Category = "Misc", DisplayName = "죽음 기준 높이")
	float DieZLocation;
};
