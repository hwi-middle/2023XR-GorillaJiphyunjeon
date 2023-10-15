// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Util/IGScriptDataTable.h"
#include "IGHintBase.generated.h"

struct FIGTextMasterDataTable;

/**
 * 
 */

UENUM()
enum class EHintType
{
	None = 0,
	Mountain,
	Wave,
	PineTree,
	Blanc
};

struct ProvisoText
{
	FString Name;
	FString Script;
};

UCLASS()
class INDIGO_API AIGHintBase : public AActor, public IInteractable
{
	GENERATED_BODY()
public:
	AIGHintBase();
	virtual ~AIGHintBase() override;
	
	virtual FORCEINLINE EHintType GetCurrnetHintType() const  {return CurrentHintType;}

	void InitHintType(const EHintType InHintType);
protected:
	virtual void Interact() override; 

	virtual FORCEINLINE FString GetHintName() const {return (HintScript == nullptr) ? TEXT("") : HintScript->Name;}
	virtual FORCEINLINE FString GetHintScript() const  {return (HintScript == nullptr) ? TEXT("") : HintScript->Script;}
	
private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;

	FString Path;
	FName Row;

	TArray<FIGTextMasterDataTable*> HintTextTitleArray;
	TArray<FIGTextMasterDataTable*> HintTextScriptArray;
	TArray<FIGTextMasterDataTable*> HintTextSummaryArray;
	
protected:	
	TArray<ProvisoText*> HintScriptArray;
	ProvisoText* HintScript;
	EHintType CurrentHintType;
	
};
