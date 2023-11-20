// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGShinmyophil.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Indigo/Util/IGScriptMasterDataTable.h"
#include "Indigo/Util/IGTextMasterDataTable.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UIGShinmyophil::UIGShinmyophil()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	IdleTime = 0.0f;
	ScriptDelayTime = 2.0f;

	CurrentPhase = EPhaseState::None;
	bIsMoveTutorial = false;
	bIsHpUnder3 = false;
}

// Called when the game starts
void UIGShinmyophil::BeginPlay()
{
	Super::BeginPlay();

	FIGDataTableParser::LoadAndInitializeDataTable(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/ScriptMasterDataTable/Script_Master.Script_Master'"),
		[&](const UDataTable* ScriptDataTable)
		{
			TArray<FIGScriptMasterDataTable*> Scripts;
			ScriptDataTable->GetAllRows(TEXT(""), Scripts);
			
			for (int32 i = 0; i < Scripts.Num(); i++)
			{
				TArray<FString> ScriptCodeArray;
				Scripts[i]->ScriptCode.ParseIntoArray(ScriptCodeArray, TEXT("_"), true);//0 string이라 제외, 1 main, 2 sub, 3 detail 
			
				if (FCString::Atof(*ScriptCodeArray[1]) == 0)
				{
					TutorialScriptsArray.AddUnique(Scripts[i]);
				}
				else if (FCString::Atof(*ScriptCodeArray[1]) == 1)
				{
					ProvisoScriptsArray.AddUnique(Scripts[i]);
				}
				else if (FCString::Atof(*ScriptCodeArray[1]) == 2)
				{
					BattleScriptsArray.AddUnique(Scripts[i]);
				}
			}
		});

	FIGDataTableParser::LoadAndInitializeDataTable(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/ScriptMasterDataTable/Script_Master_Refix.Script_Master_Refix'"),
	[&](const UDataTable* ScriptDataTable)
	{
		TArray<FIGScriptMasterDataTable*> Scripts;
		ScriptDataTable->GetAllRows(TEXT(""), Scripts);
			
		for (int32 i = 0; i < Scripts.Num(); i++)
		{
			TArray<FString> ScriptCodeArray;
			Scripts[i]->ScriptCode.ParseIntoArray(ScriptCodeArray, TEXT("_"), true);//0 string이라 제외, 1 main, 2 sub, 3 detail 
	
			if (FCString::Atof(*ScriptCodeArray[1]) == 1)
			{
				ProvisoScriptsReFixArray.Add(Scripts[i]);
			}
			else if (FCString::Atof(*ScriptCodeArray[1]) == 2)
			{
				BattleScriptsReFixArray.Add(Scripts[i]);
			}
		}
	});


	FIGDataTableParser::LoadAndInitializeDataTable(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/TextMasterDataTable/Text_Master.Text_Master'"),
		[&](const UDataTable* TextDataTable)
		{
			TArray<FIGTextMasterDataTable*> ScriptArray;
			TextDataTable->GetAllRows(TEXT(""), ScriptArray);

			for (int32 i = 0; i < ScriptArray.Num(); i++)
			{
				TArray<FString> TextCodeArray;
				ScriptArray[i]->TextCode.ParseIntoArray(TextCodeArray, TEXT("_"), true);//0 string이라 제외, 1 main, 2 sub, 3 detail 

				if (FCString::Atof(*TextCodeArray[1]) == 1 && FCString::Atof(*TextCodeArray[2]) == 3)
				{
					QuestSummaryArray.AddUnique(ScriptArray[i]);
				}
				if (FCString::Atof(*TextCodeArray[1]) == 2 && FCString::Atof(*TextCodeArray[2]) == 3)
				{
					QuestTitleArray.AddUnique(ScriptArray[i]);
				}
			}

			int Count = 0;
			for (int32 i = 0; i < QuestTitleArray.Num(); i++)
			{
				UQuest* QuestTemp = NewObject<UQuest>();
				QuestTemp->QuestTitle = QuestTitleArray[i]->Text;
				for (int32 j = 0; j < 2; j++)
				{
					QuestTemp->QuestSummaryArray.Add(QuestSummaryArray[Count]->Text);
					Count++;
				}

				QuestArray.AddUnique(QuestTemp);

			}
		});

}

void UIGShinmyophil::OnTutorialPhase()
{
	CurrentPhase = EPhaseState::TutorialPhase;
	TutorialPhaseStart();
}

void UIGShinmyophil::OnProvisoPhase()
{
	CurrentPhase = EPhaseState::ProvisoPhase;
	ProvisoStartProvisoPhase();
}

void UIGShinmyophil::OnBattlePhase()
{
	CurrentPhase = EPhaseState::BattlePhase;
	BattleStartBattlePhase();
}

void UIGShinmyophil::PrintRelayScript(const TArray<FIGScriptMasterDataTable*> InScriptArray, const int32 InSubNum)
{
	AIGPlayerCharacter* IGPlayerCharacter = Cast<AIGPlayerCharacter>(GetOwner());
	for(int32 Index = 0; Index < InScriptArray.Num(); Index++)
	{
		TArray<FString> TextCodeArray;
		InScriptArray[Index]->ScriptCode.ParseIntoArray(TextCodeArray, TEXT("_"), false);//0 string이라 제외, 1 main, 2 sub, 3 detail 
			
		if(FCString::Atof(*TextCodeArray[2]) == InSubNum)
		{
			FTimerHandle TimerHandle;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([=, &TimerHandle]()
			{			
					ScriptLogArray.Add(InScriptArray[Index]->ScriptText);
					IGPlayerCharacter->UpdateShinmyophilScript(InScriptArray[Index]->ScriptText);
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			}), ScriptDelayTime, false);
			ScriptDelayTime += 2.0f;			
			
		}
		else if(FCString::Atof(*TextCodeArray[2])  > InSubNum)
		{
			return;
		}
	}
}


void UIGShinmyophil::TutorialPhaseStart()
{
	//PrintRelayScript(TutorialScriptsArray, 1);
}

void UIGShinmyophil::TutorialPlayerMove()
{
	//PrintRelayScript(TutorialScriptsArray, 2);
	//bIsMoveTutorial = true;
}

void UIGShinmyophil::TutorialPlayerOvertheCorner()
{
	//PrintRelayScript(TutorialScriptsArray, 3);
}

void UIGShinmyophil::TutorialPlayerCrackInteract()
{
	//PrintRelayScript(TutorialScriptsArray, 4);
}

void UIGShinmyophil::TutorialRollCrack()
{
	//PrintRelayScript(TutorialScriptsArray, 5);
}

void UIGShinmyophil::TutorialCloseToJangseung()
{
	//PrintRelayScript(TutorialScriptsArray, 6);
}

void UIGShinmyophil::TutorialAttackToJangseung3Times()
{
	//PrintRelayScript(TutorialScriptsArray, 7);
}

void UIGShinmyophil::TutorialEnforceAttackToJangseung()
{
	//PrintRelayScript(TutorialScriptsArray, 8);
}

void UIGShinmyophil::TutorialOpenGate()
{
	//PrintRelayScript(TutorialScriptsArray, 9);
}

void UIGShinmyophil::TutorialInteractToGate()
{
	//PrintRelayScript(TutorialScriptsArray, 10);
}

void UIGShinmyophil::ProvisoStartProvisoPhase()
{
	PrintRelayScript(ProvisoScriptsReFixArray, 1);
}

void UIGShinmyophil::ProvisoGetFirstProviso()
{
	//PrintRelayScript(ProvisoScriptsArray, 2);
}

void UIGShinmyophil::ProvisoReadFirstProviso()
{
	//PrintRelayScript(ProvisoScriptsArray, 3);
}

void UIGShinmyophil::ProvisoFirstMeetingWist()
{
	//PrintRelayScript(ProvisoScriptsArray, 4);
}

void UIGShinmyophil::ProvisoGetFirstHint()
{
	//PrintRelayScript(ProvisoScriptsArray, 5);
}

void UIGShinmyophil::ProvisoReadFirstHint()
{
	//PrintRelayScript(ProvisoScriptsArray, 6);
}

void UIGShinmyophil::ProvisoGetFirstBlankHint()
{
	//PrintRelayScript(ProvisoScriptsArray, 7);
}

void UIGShinmyophil::ProvisoGet2HintToSameProviso()
{
	//PrintRelayScript(ProvisoScriptsArray, 8);
}

void UIGShinmyophil::ProvisoGetHint6All()
{
	//PrintRelayScript(ProvisoScriptsArray, 9);
}

void UIGShinmyophil::ProvisoCloseToProviso()
{
	//PrintRelayScript(ProvisoScriptsArray, 10);
}

void UIGShinmyophil::ProvisoGetAllProviso()
{
	//PrintRelayScript(ProvisoScriptsArray, 11);
}

void UIGShinmyophil::ProvisoPlayerStay1Minute()
{
	//PrintRelayScript(ProvisoScriptsArray, 12);
}

void UIGShinmyophil::ProvisoNotFindAllProvisoAndSkip3Minute()
{
	//PrintRelayScript(ProvisoScriptsArray, 13);
}

void UIGShinmyophil::ProvisoNotFindAllProvisoAndCloseToOldTree()
{
//	PrintRelayScript(ProvisoScriptsArray, 14);
}

void UIGShinmyophil::ProvisoNotFindAllProvisoAndInteractToOldTree()
{
//	PrintRelayScript(ProvisoScriptsArray, 15);
}

void UIGShinmyophil::ProvisoOpenGateAndCloseToGate()
{
	//PrintRelayScript(ProvisoScriptsArray, 16);
}

void UIGShinmyophil::ProvisoOpenGateAndInteractToGate()
{
	//PrintRelayScript(ProvisoScriptsArray, 17);
}

void UIGShinmyophil::ProvisoBeforeOpenGateAndInteractToGate()
{
	//PrintRelayScript(ProvisoScriptsArray, 18);
}

void UIGShinmyophil::ProvisoRemakeFirstGetCrystalFrag()
{
	PrintRelayScript(ProvisoScriptsReFixArray, 3);
}

void UIGShinmyophil::ProvisoRemakeGetAllCrystalAndGetCompleteCrystal()
{
	PrintRelayScript(ProvisoScriptsReFixArray, 4);
}

void UIGShinmyophil::ProvisoRemakeGetAllCrystal()
{
	PrintRelayScript(ProvisoScriptsReFixArray, 5);
}

void UIGShinmyophil::ProvisoRemakeCantFindCrystalAnd3Minute()
{
	PrintRelayScript(ProvisoScriptsReFixArray, 6);
}

void UIGShinmyophil::ProvisoRemakeCantFindCrystalAndCloseToOldTree()
{
	PrintRelayScript(ProvisoScriptsReFixArray, 7);
}

void UIGShinmyophil::ProvisoRemakeNoFindCrystalAndInteractToOldTree()
{
	PrintRelayScript(ProvisoScriptsReFixArray, 8);
}

void UIGShinmyophil::ProvisoRemakeOpenGateAndCloseToGate()
{
	PrintRelayScript(ProvisoScriptsReFixArray, 9);
}

void UIGShinmyophil::ProvisoRemakeOpenGateAndInteractToGate()
{
	PrintRelayScript(ProvisoScriptsReFixArray, 10);
}

void UIGShinmyophil::ProvisoRemakeBeforeOpenGateAndInteractToGate()
{
	PrintRelayScript(ProvisoScriptsReFixArray, 11);
}

void UIGShinmyophil::BattleStartBattlePhase()
{
	PrintRelayScript(BattleScriptsReFixArray, 1);
}

void UIGShinmyophil::BattleBossFirstAttack()
{
	//PrintRelayScript(BattleScriptsArray, 2);
}

void UIGShinmyophil::BattleFirstActiveCrystal()
{
	//PrintRelayScript(BattleScriptsArray, 3);
}

void UIGShinmyophil::BattleBoss2Phase()
{
	//PrintRelayScript(BattleScriptsArray, 4);
}

void UIGShinmyophil::BattleBossFirstRangeAttack()
{
	//PrintRelayScript(BattleScriptsArray, 5);
}

void UIGShinmyophil::BattleBoss3Phase()
{
	//PrintRelayScript(BattleScriptsArray, 6);
}

void UIGShinmyophil::BattleBossFistFloorAttack()
{
	//PrintRelayScript(BattleScriptsArray, 7);
}

void UIGShinmyophil::BattleBossDead()
{
	//PrintRelayScript(BattleScriptsArray, 8);
}

void UIGShinmyophil::BattlePlayerHealthUnder3()
{
	//PrintRelayScript(BattleScriptsArray, 9);
}

void UIGShinmyophil::BattleRemakeBossFirstAttack()
{
	PrintRelayScript(BattleScriptsReFixArray, 2);
}

void UIGShinmyophil::BattleRemakeFirstActiveSuccess()
{
	PrintRelayScript(BattleScriptsReFixArray, 3);
}

void UIGShinmyophil::BattleRemakeBossDie()
{
	PrintRelayScript(BattleScriptsReFixArray, 4);
}

void UIGShinmyophil::BattleRemakeInteractBossDeadBody()
{
	PrintRelayScript(BattleScriptsReFixArray, 5);
}

void UIGShinmyophil::BattleRemakePlayerHpUnder3()
{
	PrintRelayScript(BattleScriptsReFixArray, 6);
}

// Called every frame
void UIGShinmyophil::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	ScriptDelayTime = FMath::Clamp(ScriptDelayTime -= DeltaTime, 0.5, FLT_MAX);	
	
	AIGPlayerCharacter* IGPlayerCharacter = Cast<AIGPlayerCharacter>(GetOwner());
	
	if(IGPlayerCharacter == nullptr)
	{
		return;
	}	

	//튜토리얼 페이즈
	if(CurrentPhase == EPhaseState::TutorialPhase)
	{	
		//이동 했을 때
		if(EnumHasAnyFlags(IGPlayerCharacter->GetCurrentState(), EPlayerState::Walking) == true && bIsMoveTutorial == false)
		{
			TutorialPlayerMove();
		}
		
	}

	//배틀 페이즈
	if(CurrentPhase == EPhaseState::BattlePhase)
	{
		//체력 3이하일때
		if(IGPlayerCharacter->GetHp() <= 3 && bIsHpUnder3 == false)
		{
			BattleRemakePlayerHpUnder3();
			bIsHpUnder3 = true;
		}
		else if(IGPlayerCharacter->GetHp() > 3 && bIsHpUnder3 == true)
		{
			//혹시 회복될떄
			bIsHpUnder3 = false;
		}
	}
	
	//조작없이 1분동안 가만히 있을 때
	if(EnumHasAnyFlags(IGPlayerCharacter->GetCurrentState(), EPlayerState::Idling) == true)
	{
		IdleTime += DeltaTime;
		if(IdleTime > 60.0f)
		{
			ProvisoPlayerStay1Minute();
			IdleTime = 0.0f;
		}
	}
	else
	{
		IdleTime = 0.0f;
	}
	
}

