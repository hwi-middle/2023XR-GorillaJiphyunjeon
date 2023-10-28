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
	float Normal_Phase2Probability;

	UPROPERTY(EditAnywhere, Category = "2페이즈 확률", DisplayName = "2페이즈 근거리 공격 확률")
	float CloseAttack_Phase2Probability;

	UPROPERTY(EditAnywhere, Category = "2페이즈 확률", DisplayName = "2페이즈 원거리 공격 확률")
	float FarAttack_Phase2Probability;

	UPROPERTY(EditAnywhere, Category = "2페이즈 확률", DisplayName = "2페이즈 장판 공격 확률")
	float Floor_Phase2Probability;
	
	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "주먹 충돌판정 반지름")
	float CloseAttack_HandRadius;
	
	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "근거리 패턴 가시 개수")
	uint32 CloseAttack_SpikeNum;

	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "근거리 패턴 피해량")
	float CloseAttack_Damage;

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
};
