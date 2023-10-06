// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Util/IGScriptDataTable.h"
#include "IGHintBase.generated.h"

struct FIGScriptDataTable;

/**
 * 
 */
UCLASS()
class INDIGO_API AIGHintBase : public AActor, public IInteractable
{
	GENERATED_BODY()
public:
	AIGHintBase();
	AIGHintBase(FString InPath);
	virtual ~AIGHintBase() override;

protected:
	virtual void Interact() override; 

	virtual FORCEINLINE FString GetHintName() const {return (HintScript == nullptr) ? TEXT("") : HintScript->Name;}
	virtual FORCEINLINE FString GetHintScript() const  {return (HintScript == nullptr) ? TEXT("") : HintScript->Script;}
	
private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	FIGScriptDataTable* HintScript;

	FString Path;
	FName Row;
	
	UPROPERTY(VisibleAnywhere)
	FString Script;
};
