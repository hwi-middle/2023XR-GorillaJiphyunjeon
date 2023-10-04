// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/Interface/IGHintInterface.h"
#include "Components/ActorComponent.h"
#include "IGPlayerInventory.generated.h"

class AIGCrystalBase;

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
	void AddCrystals(AIGCrystalBase* InCrystal);
	void ShowMyCrystals();

	void AddHints(IIGHintInterface* InHint);

	FORCEINLINE TArray<AIGCrystalBase*> GetArrCrystals(){return ArrCrystals;}
	FORCEINLINE TArray<IIGHintInterface*> GetArrHints(){return ArrHints;}
	
private:
	TArray<AIGCrystalBase*> ArrCrystals;
	TArray<IIGHintInterface*> ArrHints;
	
};
