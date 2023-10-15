// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/Interface/IGHintInterface.h"
#include "Components/ActorComponent.h"
#include "IGPlayerInventory.generated.h"

class AIGCrystalBase;
class AIGHintBase;

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
	void AddCrystal(AIGCrystalBase* InCrystal);
	void ShowOwnedCrystals();

	void AddHint(AIGHintBase* InHint);

	FORCEINLINE TArray<AIGCrystalBase*> GetCrystalArray() { return CrystalArray; }
	FORCEINLINE TArray<AIGHintBase*> GetHintArray() { return HintArray; }

private:
	TArray<AIGCrystalBase*> CrystalArray;
	TArray<AIGHintBase*> HintArray;
	uint8 bIsGetFirstCrystal : 1;
	uint8 bIsGetFirstHint : 1;
	uint8 bIsGetFirstBlancHint : 1;
	uint8 bIsGet2HintBySameProviso : 1;

	float CantFindProvisoTime;
	
};
