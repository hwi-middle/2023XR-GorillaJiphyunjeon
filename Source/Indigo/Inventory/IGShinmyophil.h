// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IGShinmyophil.generated.h"

struct FIGScriptMasterDataTable;

UENUM()
enum class PhaseState : uint8
{
	None = 0,
	TutorialPhase,
	ProvisoPhase,
	BattlePhase,
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INDIGO_API UIGShinmyophil : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIGShinmyophil();

	void OnTutorialPhase();
	void OnProvisoPhase();
	void OnBattlePhase();

	void PrintRelayScript(const TArray<FIGScriptMasterDataTable*> InScriptArray, const int32 InSubNum)const;

	//튜토리얼 페이즈
	//튜토리얼 페이즈 시작
	void TutorialPhaseStart();
	//플레이어 조작을 이용해 이동할 경우
	void TutorialPlayerMove();
	//플레이어가 코너를 넘어갔을 때
	void TutorialPlayerOvertheCorner();
	//앞의틈과 상호작용했을 경우
	void TutorialPlayerCrackInteract();
	//구르기를 통해 틈을 넘어갔을 경우
	void TutorialRollCrack();
	//장승 근처에 다가갔을 경우
	void TutorialCloseToJangseung();
	//장승에게 일반 공격 3번 타격 성공시
	void TutorialAttackToJangseung3Times();
	//장승에게 강화 공격 1번 타격 성공 시(=장승 파괴)
	void TutorialEnforceAttackToJangseung();
	//마을 문이 열렸을 경우
	void TutorialOpenGate();
	//마을 문과 상호작용했을 경우
	void TutorialInteractToGate();

	//단서페이즈
	//단서 페이즈 시작 시
	void ProvisoStartProvisoPhase();
	//첫 단서 획득 시
	void ProvisoGetFirstProviso();
	//첫 단서 열람 시
	void ProvisoReadFirstProviso();
	//도깨비불 조우 시
	void ProvisoFirstMeetingWist();
	//첫 힌트 획득 시
	void ProvisoGetFirstHint();
	//첫 힌트 열람 시
	void ProvisoReadFirstHint();
	//첫 꽝 힌트 획득 시
	void ProvisoGetFirstBlancHint();
	//같은 단서에 대한 힌트를 2개 모았을 경우
	void ProvisoGet2HintToSameProviso();
	//힌트를 6개 모두 모았을 경우
	void ProvisoGetHint6All();
	//단서가 근처에 있을 경우
	void ProvisoCloseToProviso();
	//단서를 모두 획득했을 경우
	void ProvisoGetAllProviso();
	//플레이어가 1분 이상 가만히 있을 경우
	void ProvisoPlayerStay1Minute();
	//단서를 다 찾지 못하고 3분이 지났을 경우
	void ProvisoNotFindAllProvisoAndSkip3Minute();
	//단서를 다 찾지 못하고 마을 중앙의 신목으로 다가갔을 경우
	void ProvisoNotFindAllProvisoAndCloseToOldTree();
	//단서를 다 찾지 못하고 마을 중앙의 신목과 상호작용했을 경우
	void ProvisoNotFindAllProvisoAndInteractToOldTree();
	//보스 문이 열린 이후 보스 문 근처로 다가갔을 경우
	void ProvisoOpenGateAndCloseToGate();
	//보스 문이 열린 이후 보스 문과 상호작용했을 경우
	void ProvisoOpenGateAndInteractToGate();
	//보스 문이 열리기 전 보스 문과 상호작용했을 경우
	void ProvisoBeforeOpenGateAndInteractToGate();
	
	//전투 페이즈
	//전투 페이즈 시작 시
	void BattleStartBattlePhase();
	//보스가 첫 공격 시전 시
	void BattleBossFirstAttack();
	//첫 결정 활성화 성공 시
	void BattleFirstActiveCrystal();
	//보스 2페이즈 돌입 시
	void BattleBoss2Phase();
	//보스가 첫 원거리 공격 시전 시
	void BattleBossFirstRangeAttack();
	//보스 3페이즈 돌입 시
	void BattleBoss3Phase();
	//보스가 첫 장판기 시전 시
	void BattleBossFistFloorAttack();
	//보스 사망시
	void BattleBossDead();
	//플레이어 체력이 3 이하인 경우
	void BattlePlayerHealthUnder3();
	
	FORCEINLINE PhaseState GetCurrentPhaseState() const {return CurrentPhase;}


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UDataTable* DataTable;
	
	TArray<FIGScriptMasterDataTable*> TutorialScriptsArray;
	TArray<FIGScriptMasterDataTable*> ProvisoScriptsArray;
	TArray<FIGScriptMasterDataTable*> BattleScriptsArray;
	
	PhaseState CurrentPhase;

	uint8 bIsMoveTutorial : 1;
		
};
