// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Interface/IGHintInterface.h"
#include "Indigo/Util/IGScriptDataTable.h"
#include "IGBlankHint.generated.h"

struct FIGScriptDataTable;

UCLASS()
class INDIGO_API AIGBlankHint : public AActor, public IInteractable, public IIGHintInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGBlankHint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override; 

	virtual FORCEINLINE FString GetHintName() const override{return (BlankHintScript == nullptr) ? TEXT("") : BlankHintScript->Name;}
	virtual FORCEINLINE FString GetHintScript() const override {return (BlankHintScript == nullptr) ? TEXT("") : BlankHintScript->Script;}
	
private:
	TObjectPtr<UStaticMeshComponent> Mesh;
	FIGScriptDataTable* BlankHintScript;
	
};
