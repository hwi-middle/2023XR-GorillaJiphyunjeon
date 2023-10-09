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
	UPROPERTY(EditAnywhere, Category = "UI", DisplayName = "UI_클릭")
	TObjectPtr<USoundCue> SystemClick;

	UPROPERTY(EditAnywhere, Category = "UI", DisplayName = "UI_게임시작")
	TObjectPtr<USoundCue> SystemGameStart;

	UPROPERTY(EditAnywhere, Category = "UI", DisplayName = "UI_인게임 창 열람")
	TObjectPtr<USoundCue> SystemOpen;

	//Player
public:
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어_걷기_흙_리스트")
	TArray<USoundCue*> PlayerWalkDirtArray;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어_걷기_돌_리스트")
	TArray<USoundCue*> PlayerWalk_StoneArray;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어_걷기_나무_리스트")
	TArray<USoundCue*> PlayerWalk_WoodArray;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어_달리기_리스트")
	TArray<USoundCue*> PlayerRunArray;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어_구르기_리스트")
	TArray<USoundCue*> PlayerRollArray;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어_일반 공격_리스트")
	TArray<USoundCue*> PlayerAttackArray;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어_붓 휘두르는 소리_리스트")
	TArray<USoundCue*> PlayerSwingArray;

	UPROPERTY(EditAnywhere, Category = "player", DisplayName = "플레이어_게이지 최대")
	TObjectPtr<USoundCue> PlayerGaugeMax;

	UPROPERTY(EditAnywhere, Category = "player", DisplayName = "플레이어_게이지 활성화")
    TObjectPtr<USoundCue> PlayerGaugeOn;

	UPROPERTY(EditAnywhere, Category = "player", DisplayName = "플레이어_게이지 부족")
	TObjectPtr<USoundCue> PlayerGaugeMin;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어_강화 공격_리스트")
	TArray<USoundCue*> PlayerEnforcedAttackArray;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어_공격 적중_리스트")
	TArray<USoundCue*> PlayerAttackHitArray;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어_공격 피격_리스트")
	TArray<USoundCue*> PlayerDamageArray;

	UPROPERTY(EditAnywhere, Category = "player", DisplayName = "플레이어_결정 활성화")
	TObjectPtr<USoundCue> PlayerCrystalOn;

	UPROPERTY(EditAnywhere, Category = "player", DisplayName = "플레이어_결정 해제")
	TObjectPtr<USoundCue> PlayerCrystalOff;
	
	UPROPERTY(EditAnywhere, Category = "player", DisplayName = "플레이어_사망")
	TObjectPtr<USoundCue> PlayerDeath;

	
	//Monster(도깨비불)
public:
	UPROPERTY(EditAnywhere, Category = "Monster", DisplayName = "도깨비불_피격_리스트")
	TArray<USoundCue*> WispDamageArray;

	UPROPERTY(EditAnywhere, Category = "Monster", DisplayName = "도깨비불_사망_리스트")
	TArray<USoundCue*> WispDeathArray;

	
	//Object
public:
	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "결정_획득")
	TObjectPtr<USoundCue> CrystalGet;

	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "장승_파괴_리스트")
	TArray<USoundCue*> JangseungBrakeArray;

	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "장독대_파괴_리스트")
	TArray<USoundCue*> JangdokdaeBrakeArray;

	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "문_열림")
	TObjectPtr<USoundCue> DoorOpen;

	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "포목점_천_리스트")
	TArray<USoundCue*> ClothWindArray;
	
	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "용광로_불꽃")
	TObjectPtr<USoundCue> FireBlaze;

	UPROPERTY(EditAnywhere, Category = "Object", DisplayName = "주점_솥뚜껑")
	TObjectPtr<USoundCue> PotOpen;


//보스
public:
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스_등장")
	TObjectPtr<USoundCue> BossApperance;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스_포효")
	TObjectPtr<USoundCue> BossShouting;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스_이동_리스트")
	TArray<USoundCue*> BossWalkArray;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스_정지")
	TObjectPtr<USoundCue> Boss_Stop;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스_1페이즈_공격_리스트")
	TArray<USoundCue*> Boss1PhaseAttackArray;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스_2페이즈_공격_리스트")
	TArray<USoundCue*> Boss2PhaseAttackArray;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스_3페이즈_공격_리스트")
	TArray<USoundCue*> Boss3PhaseAttackArray;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스_일반 피격_리스트")
	TArray<USoundCue*> BossAttackDamageArray;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스_강화 피격_리스트")
	TArray<USoundCue*> BossEnforcedDamageArray;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스_사망")
	TObjectPtr<USoundCue> BossDeath;
	
//BGM
public:
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음_게임 타이틀")
	TObjectPtr<USoundCue> BGMMain;

	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음_튜토리얼")
	TObjectPtr<USoundCue> BGMTutorial;

	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음_마을")
	TObjectPtr<USoundCue> BGMVillage;

	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음_보스방")
	TObjectPtr<USoundCue> BGMBoss;

	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음_오프닝")
	TObjectPtr<USoundCue> BGMOpening;

	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "배경음_엔딩")
	TObjectPtr<USoundCue> BGMEnding;

//AMB(환경음)
public:
	UPROPERTY(EditAnywhere, Category = "AMB", DisplayName = "환경음_풀")
	TObjectPtr<USoundCue> AMBGrass;

	UPROPERTY(EditAnywhere, Category = "AMB", DisplayName = "환경음_나뭇잎")
	TObjectPtr<USoundCue> AMBLeaf;

	UPROPERTY(EditAnywhere, Category = "AMB", DisplayName = "환경음_바람")
	TObjectPtr<USoundCue> AMBWind;

	UPROPERTY(EditAnywhere, Category = "AMB", DisplayName = "환경음_물")
    TObjectPtr<USoundCue> AMBWater;
    	
    UPROPERTY(EditAnywhere, Category = "AMB", DisplayName = "환경음_새소리")
    TObjectPtr<USoundCue> AMBBird;
	
	
};
