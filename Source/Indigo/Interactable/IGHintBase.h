// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Util/IGScriptDataTable.h"
#include "IGHintBase.generated.h"

struct FIGTextMasterDataTable;

class AIGPlayerCharacter;
class UIGPlayerInventory;

/**
 * 
 */

UENUM()
enum class EHintType : uint8
{
	None = 0,
	Mountain = 1,
	Wave = 2,
	PineTree = 3,
	Blank = 4
};

struct ProvisoText 
{
	FString Name;
	FString Script;
	EHintType HintType;
};

UCLASS()
class INDIGO_API AIGHintBase : public AActor, public IInteractable
{
	GENERATED_BODY()
public:
	AIGHintBase();
	virtual ~AIGHintBase() override;

	virtual void BeginPlay() override;
	
	void InitHintType(const EHintType InHintType);
	
	
	virtual FORCEINLINE ProvisoText* GetHint() const {return HintScript;}
	virtual FORCEINLINE FString GetHintName() const {return (HintScript == nullptr) ? TEXT("") : HintScript->Name;}
	virtual FORCEINLINE FString GetHintScript() const  {return (HintScript == nullptr) ? TEXT("") : HintScript->Script;}

	
protected:
	virtual void Interact() override; 
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY()
	FName Row;

	TArray<FIGTextMasterDataTable*> HintTextTitleArray;
	TArray<FIGTextMasterDataTable*> HintTextScriptArray;
	
protected:	
	TArray<ProvisoText*> MountainHintScriptArray;
	TArray<ProvisoText*> WaveHintScriptArray;
	TArray<ProvisoText*> PineTreeHintScriptArray;
	TArray<ProvisoText*> BlankHintScriptArray;
	
	ProvisoText* HintScript;	
};
