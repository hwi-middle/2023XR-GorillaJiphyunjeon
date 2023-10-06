// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "IGSoundDataAsset.generated.h"

class USoundCue;
/**
 * 
 */
UCLASS()
class INDIGO_API UIGSoundDataAsset : public UDataAsset
{
	GENERATED_BODY()

	//BGM
public:
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "로비 배경음악")
	TObjectPtr<USoundCue> LobbyBGMSoundCue;

	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "튜토리얼 페이즈 배경음악")
	TObjectPtr<USoundCue> TutorialBGMSoundCue;

	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "단서 페이즈 배경음악")
	TObjectPtr<USoundCue> ProvisoBGMSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "전투 페이즈 배경음악 리스트")
	TArray<USoundCue*> BossBattleBGMSoundCueArray;
	
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "엔딩 배경음악")
	TObjectPtr<USoundCue> EndingSoundCue;

	//Player
public:
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 피격음")
	TObjectPtr<USoundCue> PlayerHitSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어가 사망할 때 효과음")
	TObjectPtr<USoundCue> PlayerDeadSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어가 일반 공격할 때 효과음")
	TObjectPtr<USoundCue> PlayerAttackSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 소나무 결정 반격할 때 효과음")
	TObjectPtr<USoundCue>  PlayerPineTreeCounterAttackSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 산 결정 반격할 때 효과음")
	TObjectPtr<USoundCue>  PlayerMountainCounterAttackSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 물결 반격할 때 효과음")
	TObjectPtr<USoundCue>  PlayerWaveCounterAttackSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 소나무 결정 활성화 할 때 효과음")
	TObjectPtr<USoundCue>  PlayerPinTreeCrystalActivitySoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 산 결정 활성화 할 때 효과음")
	TObjectPtr<USoundCue>  PlayerMountainCrystalActivitySoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 물결 결정 활성화 할 때 효과음")
	TObjectPtr<USoundCue>  PlayerWaveCrystalActivitySoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어가 강화공격할 때 효과음")
	TObjectPtr<USoundCue> PlayerEnforcedAttackSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 구르기 효과음")
	TObjectPtr<USoundCue> PlayerRollingSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 발소리 리스트")
	TArray<USoundCue*> PlayerWalkSoundCueArray;	

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 걷기 발소리 간격")
	float WalkSoundRate;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 달리기 발소리 간격")
	float SprintSoundRate;

//Boss
public:
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 피격음")
	TObjectPtr<USoundCue> BossHitSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스가 사망할 때 효과음")
	TObjectPtr<USoundCue> BossDeadSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 근거리 공격 캐스팅 효과음")
	TObjectPtr<USoundCue> BossMeleeAttackCastingSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 근거리 공격 시전 효과음")
	TObjectPtr<USoundCue> BossMeleeAttackSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 근거리 공격 산 솟아날때 효과음")
	TObjectPtr<USoundCue> BossMeleeAttackMountainSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 원거리 공격 캐스팅 효과음")
	TObjectPtr<USoundCue> BossRangedAttackCastingSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 원거리 공격 시전 효과음")
	TObjectPtr<USoundCue> BossRangedAttackSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 장판 공격 캐스팅 효과음")
	TObjectPtr<USoundCue> BossFieldAttackCastingSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 장판 공격 시전 효과음")
	TObjectPtr<USoundCue> BossFieldAttackSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 장판이 반경이 늘어나지면서 나는 효과음")
	TObjectPtr<USoundCue> BossFiledAttackObjectSoundCue;
	
//Wisp(도깨비불)
public:
	UPROPERTY(EditAnywhere, Category = "Wisp", DisplayName = "도깨비불 피격음")
	TObjectPtr<USoundCue> WispHitSoundCue;

	UPROPERTY(EditAnywhere, Category = "Wisp", DisplayName = "도깨비불 사망할 때 효과음")
	TObjectPtr<USoundCue> WispDeadSoundCue;

	UPROPERTY(EditAnywhere, Category = "Wisp", DisplayName = "도깨비불 스폰할 때 효과음")
	TObjectPtr<USoundCue> WispSpawnSoundCue;

	UPROPERTY(EditAnywhere, Category = "Wisp", DisplayName = "도깨비불 힌트 드랍할 때 효과음")
	TObjectPtr<USoundCue> WispDropHintSoundCue;
	
	
//Interact(상호작용)
public:
	UPROPERTY(EditAnywhere, Category = "Interact", DisplayName = "힌트 획득할 때 효과음")
	TObjectPtr<USoundCue> InteractTakeHintSoundCue;

	UPROPERTY(EditAnywhere, Category = "Interact", DisplayName = "소나무 결정 획득할 때 효과음")
	TObjectPtr<USoundCue> InteractTakePineTreeCrystalSoundCue;

	UPROPERTY(EditAnywhere, Category = "Interact", DisplayName = "산 결정 획득할 때 효과음")
	TObjectPtr<USoundCue> InteractTakeMountainCrystalSoundCue;

	UPROPERTY(EditAnywhere, Category = "Interact", DisplayName = "물결 결정 획득할 때 효과음")
	TObjectPtr<USoundCue> InteractTakeWaveCrystalSoundCue;
	
	
};
