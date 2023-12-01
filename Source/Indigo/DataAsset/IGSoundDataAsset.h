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

	//UI
public:
	UPROPERTY(EditAnywhere, Category = "UI", DisplayName = "UI 클릭")
	TObjectPtr<USoundCue> UIClick;

	UPROPERTY(EditAnywhere, Category = "UI", DisplayName = "게임시작")
	TObjectPtr<USoundCue> UIGameStart;

	//Player
public:
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 걷기")
	TObjectPtr<USoundCue> PlayerWalkSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어가 뜀")
	TObjectPtr<USoundCue> PlayerRunSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어가 구르기")
	TObjectPtr<USoundCue> PlayerRollSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "붓 휘두름")
	TObjectPtr<USoundCue>  PlayerSwingSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 피격")
	TObjectPtr<USoundCue>  PlayerGetDamageSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 스테미나 부족")
	TObjectPtr<USoundCue>  PlayerLowStaminaSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 1타 공격")
	TObjectPtr<USoundCue>  PlayerAttackCombo1SoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 2타 공격")
	TObjectPtr<USoundCue>  PlayerAttackCombo2SoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 3타 공격")
	TObjectPtr<USoundCue>  PlayerAttackCombo3SoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 결정 활성화")
	TObjectPtr<USoundCue>  PlayerCrystalActivitySoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 결정 비활성화")
	TObjectPtr<USoundCue>  PlayerCrystalDisableSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 사망")
	TObjectPtr<USoundCue> PlayerDeadSoundCue;
	
//Boss
public:
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 등장")
	TObjectPtr<USoundCue> BossAppearSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 포효")
	TObjectPtr<USoundCue> BossShoutSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 이동")
	TObjectPtr<USoundCue> BossMoveSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 정지")
	TObjectPtr<USoundCue> BossMoveStopSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 한손 할퀴기")
	TObjectPtr<USoundCue> BossAttack1HandSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 양손 할퀴기")
	TObjectPtr<USoundCue> BossAttack2HandSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 1페이즈 - 손으로 기가 모이는 소리")
	TObjectPtr<USoundCue> BossSmashChargeSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 1페이즈 - 땅을 아래로 내려치는 소리")
	TObjectPtr<USoundCue> BossSmashSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 2페이즈 - 손에서 물결 기운 모이는 소리")
	TObjectPtr<USoundCue> BossChargeWaveSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 2페이즈 - 물에너지가 발사되는 소리")
	TObjectPtr<USoundCue> BossShotWaveSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 3페이즈 - 팔을 강하게 휘두르는 소리")
	TObjectPtr<USoundCue> BossSpinSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 3페이즈 - 소나무 기운이 퍼져나가는 소리")
	TObjectPtr<USoundCue> BossShotTreeSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 일반피격")
	TObjectPtr<USoundCue> BossGetDamageSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 강화피격")
	TObjectPtr<USoundCue> BossGetEnforceDamageSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 사망")
	TObjectPtr<USoundCue> BossDeathSoundCue;
	
//Wisp(도깨비불)
public:
	UPROPERTY(EditAnywhere, Category = "Wisp", DisplayName = "도깨비불 피격음")
	TObjectPtr<USoundCue> WispHitSoundCue;

	UPROPERTY(EditAnywhere, Category = "Wisp", DisplayName = "도깨비불 사망할 때 효과음")
	TObjectPtr<USoundCue> WispDeadSoundCue;

	UPROPERTY(EditAnywhere, Category = "Wisp", DisplayName = "도깨비불 폭발할 때 효과음")
	TObjectPtr<USoundCue> WispBombSoundCue;
	
//Interact(상호작용)
public:
	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "결정 획득할 때 효과음")
	TObjectPtr<USoundCue> ObjectGetCrystalSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "문 열림 효과음")
	TObjectPtr<USoundCue> ObjectOpenGateSoundCue;

	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "포목점 천 휘나리는 소리")
	TObjectPtr<USoundCue> ObjectClothWindSoundCue;

	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "용광로 불꽃")
	TObjectPtr<USoundCue> ObjectFireBlazeSoundCue;

//BGM	
public:
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음 게임 타이틀")
	TObjectPtr<USoundCue> BGMMainSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음 마을")
	TObjectPtr<USoundCue> BGMVillageSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음 보스")
	TObjectPtr<USoundCue> BGMBossSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음 오프닝")
	TObjectPtr<USoundCue> BGMOpeningSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음 보스 입장")
	TObjectPtr<USoundCue> BGMInBoss;
	
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음 보스 클리어")
	TObjectPtr<USoundCue> BGMClearBoss;
	
//AMB
public:	
	UPROPERTY(EditAnywhere, Category = "AMB", DisplayName = "환경음 새소리")
	TObjectPtr<USoundCue> AMBBirdSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "AMB", DisplayName = "환경음 바람")
	TObjectPtr<USoundCue> AMBWindSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "AMB", DisplayName = "환경음 물")
	TObjectPtr<USoundCue> AMBWaterSoundCue;
	
	
};
