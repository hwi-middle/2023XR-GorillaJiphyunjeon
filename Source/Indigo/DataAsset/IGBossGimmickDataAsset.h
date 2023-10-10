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
	UPROPERTY(EditAnywhere, Category = "근거리 패턴", DisplayName = "주먹 충돌판정 반지름")
	float CloseAttack_HandRadius;

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
};
