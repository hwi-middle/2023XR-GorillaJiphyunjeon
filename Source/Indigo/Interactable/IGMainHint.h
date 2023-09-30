// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "IGMainHint.generated.h"

struct FIGScriptDataTable;

UCLASS()
class INDIGO_API AIGMainHint : public AActor, public IInteractable
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

private:
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	FString Script;
	
	FIGScriptDataTable* MainHintScript;	
};
