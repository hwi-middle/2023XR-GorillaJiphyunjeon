// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Util/IGScriptDataTable.h"
#include "GameFramework/Actor.h"
#include "IGHintParent.generated.h"

struct FIGScriptDataTable;

/**
 * 
 */
UCLASS()
class INDIGO_API AIGHintParent : public AActor, public IInteractable
{
	GENERATED_BODY()
public:
	AIGHintParent();
	AIGHintParent(FString InPath);
	virtual ~AIGHintParent() override;

protected:
	virtual void Interact() override; 

	virtual FORCEINLINE FString GetHintName() const {return (HintScript == nullptr) ? TEXT("") : HintScript->Name;}
	virtual FORCEINLINE FString GetHintScript() const  {return (HintScript == nullptr) ? TEXT("") : HintScript->Script;}
	
private:
	TObjectPtr<UStaticMeshComponent> Mesh;
	FIGScriptDataTable* HintScript;

	FString Path;
	FName Row;
	
	UPROPERTY(VisibleAnywhere)
	FString Script;
};
