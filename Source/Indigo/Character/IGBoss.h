// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGEnemyBase.h"
#include "IGBoss.generated.h"

class UIGIngameHUDWidget;
class UIGBossDataAsset;
class UIGBossGimmickDataAsset;
DECLARE_MULTICAST_DELEGATE(FOnFinishBossCloseAttackDelegate)

class UIGBossAnimInstance;
class UIGPlayerAnimInstance;
/**
 * 
 */

UENUM(BlueprintType)
enum EAttackPattern : uint32
{
	None,
	Close,
	Far,
	Floor,
};

UCLASS()
class INDIGO_API AIGBoss : public AIGEnemyBase
{
	GENERATED_BODY()

public:
	AIGBoss();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void FadeOut();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIGIngameHUDWidget> HudWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UIGIngameHUDWidget> HudWidget;
	
private:
	UPROPERTY()
	TObjectPtr<UIGBossAnimInstance> AnimInstance;

	UPROPERTY()
	float StoppingDistance;

	// 능력치 데이터
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UIGBossDataAsset> BossDataAsset;

	// 기믹 데이터
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UIGBossGimmickDataAsset> GimmickDataAsset;

	// 근거리 패턴
	UPROPERTY(VisibleAnywhere)
	uint32 CloseAttack_SpikeNum;
	
	UPROPERTY(VisibleAnywhere)
	float CloseAttack_HandRadius;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_Damage;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeTimeGap;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeDistanceGap;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeDuration;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeDestroyDelay;

	UPROPERTY(VisibleAnywhere)
	uint32 bIsInRange : 1;

	//보스 첫공격
	UPROPERTY(VisibleAnywhere)
	uint8 bIsFirstAttack : 1;

	//보스 페이즈2 진입
	UPROPERTY(VisibleAnywhere)
	uint8 bIsInPhase2 : 1;

	//보스 첫 원거리 공격 시전
	UPROPERTY(VisibleAnywhere)
	uint8 bIsFirstRangeAttack : 1;

	//보스 페이즈3 진입
	UPROPERTY(VisibleAnywhere)
	uint8 bIsInPhase3 : 1;

	//첫 장판기 시전
	UPROPERTY(VisibleAnywhere)
	uint8 bIsFirstFloorAttack : 1;
	
public:
	FOnFinishBossCloseAttackDelegate OnFinishBossCloseAttack;

public:
	FORCEINLINE float GetStoppingDistance() const { return StoppingDistance; }

	void EnableHUD();
	void DisableHUD();
	void PerformCloseAttack();
	void GenerateCloseAttack();
	void EndCloseAttack();
};
