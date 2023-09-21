// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGDataParser.h"
#include "IGCharacterDataTable.h"
#include "../Interface/IGCharacterStatus.h"
#include "IGConstructorHelper.h"




// Sets default values for this component's properties
UIGDataParser::UIGDataParser()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UIGDataParser::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	SetCharacterStatusData();
}


// Called every frame
void UIGDataParser::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	#if WITH_EDITOR	
	SetCharacterStatusData();
	#endif
	
	// ...
	
}

void UIGDataParser::InitDataTable(FString InRowName, IIGCharacterStatus* OutStatus)
{
	RowName = InRowName;
	CharacterInterface = OutStatus;
	
	FIGConstructorHelper::FindObjectAndInitialize<UDataTable>
	(
		*CharacterDataTablePath,[&](const UDataTable* CharacterDataTable)
		{
				IGCharacterDataTable = CharacterDataTable->FindRow<FIGCharacterDataTable>
				(
					FName(RowName),
					FString("")
				);
			UE_LOG(LogTemp, Log, TEXT("생성및 초기화 시 주솟값: %p"), IGCharacterDataTable);
		},		EAssertionLevel::Check
	);
}

void UIGDataParser::SetCharacterStatusData()
{
	if(IGCharacterDataTable != nullptr)
	{		
		CharacterInterface->SetHp(IGCharacterDataTable->HPValue);
		CharacterInterface->SetAttackRange(IGCharacterDataTable->AttackRange);
		CharacterInterface->SetAttackRate(IGCharacterDataTable->AttackRate);
		CharacterInterface->SetAttackValue(IGCharacterDataTable->AttackValue);
		CharacterInterface->SetDefenseValue(IGCharacterDataTable->DefenceValue);
		CharacterInterface->SetStaminaValue(IGCharacterDataTable->StaminaValue);
	}
}


void UIGDataParser::PrintCharacterDataTable()
{
	if(IGCharacterDataTable != nullptr)
	{		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("HP: %d"), IGCharacterDataTable->HPValue));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("AttackRange: %d"), IGCharacterDataTable->AttackRange));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("AttackRate: %d"), IGCharacterDataTable->AttackValue));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("DefenceValue: %d"), IGCharacterDataTable->DefenceValue));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Stamina: %d"), IGCharacterDataTable->StaminaValue));	
	}
}
void UIGDataParser::DynamicLoadCharacterDataTable()
{
	UDataTable* temp = LoadObject<UDataTable>(nullptr, *CharacterDataTablePath, NULL, LOAD_None, NULL);
	FIGCharacterDataTable* dest = temp->FindRow<FIGCharacterDataTable>(FName("Player"), TEXT(""));
	UE_LOG(LogTemp, Log, TEXT("동적 오브젝트 로드시 주솟값: %p"), dest);
}

