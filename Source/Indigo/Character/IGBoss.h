// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGEnemyBase.h"
#include "Indigo/Interface/Interactable.h"
#include "IGBoss.generated.h"

class UIGIngameHUDWidget;
class UIGBossDataAsset;
class UIGBossGimmickDataAsset;
class UBoxComponent;
class UIGSoundDataAsset;
DECLARE_MULTICAST_DELEGATE(FOnFinishBossAttackDelegate)

class UIGBossAnimInstance;
class UIGPlayerAnimInstance;

class ULevelSequence;
class ALevelSequenceActor;
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
	NormalWeak,
	NormalStrong,
};

UCLASS()
class INDIGO_API AIGBoss : public AIGEnemyBase, public IInteractable
{
	GENERATED_BODY()

public:
	AIGBoss();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void FadeOut();

	virtual void Interact() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIGIngameHUDWidget> HudWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UIGIngameHUDWidget> HudWidget;

private:
	ALevelSequenceActor* OutActor;

	UPROPERTY(EditAnywhere)
	ULevelSequence* LevelSequenceOnDied;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> EyeMesh;
	
	UPROPERTY()
	TObjectPtr<UIGBossAnimInstance> AnimInstance;

	UPROPERTY()
	float StoppingDistance;

	UPROPERTY()
	TObjectPtr<AActor> PlayerActor;

	// 능력치 데이터
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UIGBossDataAsset> BossDataAsset;

	// 기믹 데이터
	UPROPERTY()
	TEnumAsByte<EAttackPattern> CurrentGimmick;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UIGBossGimmickDataAsset> GimmickDataAsset;

	// 확률
	UPROPERTY(VisibleAnywhere)
	float Normal_Phase1Probability;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_Phase1Probability;

	UPROPERTY(VisibleAnywhere)
	float FarAttack_Phase1Probability;

	UPROPERTY(VisibleAnywhere)
	float FloorAttack_Phase1Probability;
	
	UPROPERTY(VisibleAnywhere)
	float Normal_Phase2Probability;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_Phase2Probability;

	UPROPERTY(VisibleAnywhere)
	float FarAttack_Phase2Probability;

	UPROPERTY(VisibleAnywhere)
	float FloorAttack_Phase2Probability;
	
	// 평타
	UPROPERTY(VisibleAnywhere)
	float NormalWeak_Damage;

	UPROPERTY(VisibleAnywhere)
	float NormalStrong_Damage;
	
	// 근거리 패턴
	UPROPERTY(VisibleAnywhere)
	uint32 CloseAttack_SpikeNum;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_HandRadius;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_Damage;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_HandDamage;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeTimeGap;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeDistanceGap;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeDuration;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeDestroyDelay;
	
	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeGroundOffset;

	// 원거리 패턴
	UPROPERTY(VisibleAnywhere)
	float FarAttack_Damage;

	UPROPERTY(VisibleAnywhere)
	float FarAttack_ProjectileSpeed;
	
	UPROPERTY(VisibleAnywhere)
	float FarAttack_ProjectileDuration;

	// 장판 패턴
	UPROPERTY(VisibleAnywhere)
	float FloorAttack_Damage;

	UPROPERTY(VisibleAnywhere)
	float FloorAttack_ProjectileDistance;
	
	UPROPERTY(VisibleAnywhere)
	float FloorAttack_ProjectileNum;
		
	UPROPERTY(VisibleAnywhere)
	float FloorAttack_ProjectileSpeed;

	// 
	UPROPERTY(VisibleAnywhere)
	uint32 bIsInRange : 1;

	//보스 첫공격
	UPROPERTY(VisibleAnywhere)
	uint8 bIsFirstAttack : 1;

	//보스 첫 원거리 공격 시전
	UPROPERTY(VisibleAnywhere)
	uint8 bIsFirstRangeAttack : 1;

	//첫 장판기 시전
	UPROPERTY(VisibleAnywhere)
	uint8 bIsFirstFloorAttack : 1;
	
	//죽었을 때 상호작용
	UPROPERTY(VisibleAnywhere)
	uint8 bIsFirstDeadInteract : 1;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> InteractCollider;
	
	// 사운드
	UPROPERTY()
	TObjectPtr<UIGSoundDataAsset> SoundDataAsset;

	
public:
	FOnFinishBossAttackDelegate OnFinishBossAttack;

public:
	FORCEINLINE float GetStoppingDistance() const { return StoppingDistance; }
	FORCEINLINE EAttackPattern GetCurrentGimmick() const { return CurrentGimmick; }


	EAttackPattern GetRandomAttackPatternByProbability();
	void EnableHUD();
	void DisableHUD();
	void PerformNormalWeakAttack();
	void PerformNormalStrongAttack();
	void PerformCloseAttack();
	void PerformFloorAttack();
	void PerformFarAttack();
	void GenerateNormalWeakAttack();
	void GenerateNormalStrongAttack();
	void GenerateCloseAttack();
	void GenerateFloorAttack();
	void GenerateFarAttack();
	void EndAttack();

};
