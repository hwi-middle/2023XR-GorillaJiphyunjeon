// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGCharacterDataParser.h"
#include "IGCharacterDataTable.h"
#include "../Interface/IGCharacterStatus.h"
#include "IGConstructorHelper.h"




// Sets default values for this component's properties
UIGDataParser::UIGDataParser()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CharacterDataTablePath = TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/CharaterDatabase.CharaterDatabase'");
	
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

void UIGDataParser::InitDataTable(FString InRowName, IIGCharacterStatus* InStatus)
{
	RowName = InRowName;
	CharacterInterface = InStatus;
	
	FIGConstructorHelper::FindObjectAndInitialize<UDataTable>
	(
		*CharacterDataTablePath,[&](const UDataTable* CharacterDataTable)
		{
				IGCharacterDataTable = CharacterDataTable->FindRow<FIGCharacterDataTable>
				(
					FName(RowName),
					FString("")
				);
		},		EAssertionLevel::Check
	);
}

void UIGDataParser::SetCharacterStatusData()
{
	if (IGCharacterDataTable != nullptr)
	{		
		CharacterInterface->SetHp(IGCharacterDataTable->HPValue);
		CharacterInterface->SetAttackRange(IGCharacterDataTable->AttackRange);
		CharacterInterface->SetAttackRate(IGCharacterDataTable->AttackRate);
		CharacterInterface->SetAttackValue(IGCharacterDataTable->AttackValue);
		CharacterInterface->SetDefenseValue(IGCharacterDataTable->DefenseValue);
		CharacterInterface->SetStaminaValue(IGCharacterDataTable->StaminaValue);
	}
}


void UIGDataParser::PrintCharacterDataTable()
{
	if (IGCharacterDataTable != nullptr)
	{		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("HP: %d"), IGCharacterDataTable->HPValue));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("AttackRange: %d"), IGCharacterDataTable->AttackRange));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("AttackRate: %d"), IGCharacterDataTable->AttackValue));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("DefenceValue: %d"), IGCharacterDataTable->DefenseValue));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Stamina: %d"), IGCharacterDataTable->StaminaValue));	
	}
}
void UIGDataParser::DynamicLoadCharacterDataTable()
{
	UDataTable* Temp = LoadObject<UDataTable>(nullptr, *CharacterDataTablePath, nullptr, LOAD_None, nullptr);
	IGCharacterDataTable = Temp->FindRow<FIGCharacterDataTable>(FName("Player"), TEXT(""));
}

