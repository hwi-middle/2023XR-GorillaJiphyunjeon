// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "IGBossGimmickDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGBossGimmickDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "1페이즈 확률", DisplayName = "1페이즈 평타 확률")
	float Normal_Phase1Probability;

	UPROPERTY(EditAnywhere, Category = "1페이즈 확률", DisplayName = "1페이즈 근거리 공격 확률")
	float CloseAttack_Phase1Probability;

	UPROPERTY(EditAnywhere, Category = "1페이즈 확률", DisplayName = "1페이즈 원거리 공격 확률")
	float FarAttack_Phase1Probability;

	UPROPERTY(EditAnywhere, Category = "1페이즈 확률", DisplayName = "1페이즈 장판 공격 확률")
	float Floor_Phase1Probability;
	
	UPROPERTY(EditAnywhere, Category = "2페이즈 확률", DisplayName = "2페이즈 평타 확률")
	float NormalAttack_Phase2Probability;

	UPROPERTY(EditAnywhere, Category = "2페이즈 확률", DisplayName = "2페이즈 근거리 공격 확률")
	float CloseAttack_Phase2Probability;

	UPROPERTY(EditAnywhere, Category = "2페이즈 확률", DisplayName = "2페이즈 원거리 공격 확률")
	float FarAttack_Phase2Probability;

	UPROPERTY(EditAnywhere, Category = "2페이즈 확률", DisplayName = "2페이즈 장판 공격 확률")
	float FloorAttack_Phase2Probability;

	// 근거리 패턴
	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "근거리 패턴 공격영역 피해량")
	float CloseAttack_Damage;

	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "근거리 패턴 주먹 피해량")
	float CloseAttack_HandDamage;

	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "주먹 충돌판정 반지름")
	float CloseAttack_HandRadius;
	
	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "근거리 패턴 가시 개수")
	uint32 CloseAttack_SpikeNum;

	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "근거리 패턴 가시 생성 시간 간격")
	float CloseAttack_SpikeTimeGap;

	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "근거리 패턴 가시 생성 거리 간격")
	float CloseAttack_SpikeDistanceGap;

	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "근거리 패턴 가시 생성 시간")
	float CloseAttack_SpikeDuration;
	
	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "근거리 패턴 가시 파괴 딜레이")
	float CloseAttack_SpikeDestroyDelay;
	
	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "근거리 패턴 가시 생성 Z축 오프셋")
	float CloseAttack_SpikeGroundOffset;

	// 원거리 패턴
	UPROPERTY(EditAnywhere, Category = "원거리 패턴", DisplayName = "원거리 패턴 피해량")
	float FarAttack_Damage;

	UPROPERTY(EditAnywhere, Category = "원거리 패턴", DisplayName = "원거리 패턴 발사체 속도")
	float FarAttack_ProjectileSpeed;
	
	UPROPERTY(EditAnywhere, Category = "원거리 패턴", DisplayName = "원거리 패턴 수명(초)")
	float FarAttack_ProjectileDuration;

	// 장판 패턴
	UPROPERTY(EditAnywhere, Category = "장판 패턴", DisplayName = "장판 패턴 피해량")
	float FloorAttack_Damage;

	UPROPERTY(EditAnywhere, Category = "장판 패턴", DisplayName = "장판 패턴 투사체 발사 거리(cm)")
	float FloorAttack_ProjectileDistance;
	
	UPROPERTY(EditAnywhere, Category = "장판 패턴", DisplayName = "장판 패턴 투사체 개수")
	float FloorAttack_ProjectileNum;
		
	UPROPERTY(EditAnywhere, Category = "장판 패턴", DisplayName = "장판 패턴 발사체 속도")
	float FloorAttack_ProjectileSpeed;
};
