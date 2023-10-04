// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/Interface/IGHintInterface.h"
#include "Components/ActorComponent.h"
#include "IGPlayerInventory.generated.h"

class AIGCrystalParent;

UCLASS()
class INDIGO_API UIGPlayerInventory : public UActorComponent
{	
	GENERATED_BODY()

public:
	UIGPlayerInventory();
	virtual ~UIGPlayerInventory() override;
	
	virtual void BeginPlay() override;	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	void AddCrystals(AIGCrystalParent* InCrystal);
	void ShowMyCrystals();

	void AddHints(IIGHintInterface* InHint);

	FORCEINLINE TArray<AIGCrystalParent*> GetArrCrystals(){return ArrCrystals;}
	FORCEINLINE TArray<IIGHintInterface*> GetArrHints(){return ArrHints;}
	
private:
	TArray<AIGCrystalParent*> ArrCrystals;
	TArray<IIGHintInterface*> ArrHints;
	
};
