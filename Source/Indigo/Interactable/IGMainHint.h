// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Interface/IGHintInterface.h"
#include "Indigo/Util/IGScriptDataTable.h"
#include "IGMainHint.generated.h"

struct FIGScriptDataTable;

UCLASS()
class INDIGO_API AIGMainHint : public AActor, public IInteractable, public IIGHintInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGMainHint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;

	virtual FORCEINLINE FString GetHintName() const override{return (MainHintScript == nullptr) ? TEXT("") : MainHintScript->Name;}
	virtual FORCEINLINE FString GetHintScript() const override {return (MainHintScript == nullptr) ? TEXT("") : MainHintScript->Script;}
	
private:
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	FString Script;
	
	FIGScriptDataTable* MainHintScript;	
};
