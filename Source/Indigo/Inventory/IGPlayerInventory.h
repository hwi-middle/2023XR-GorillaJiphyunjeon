// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/Interface/IGCrystalInterface.h"
#include "Indigo/Interface/IGHintInterface.h"
#include "Components/ActorComponent.h"
#include "IGPlayerInventory.generated.h"

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
	void AddCrystals(IIGCrystalInterface* InCrystal);
	void ShowMyCrystals();

	void AddHints(IIGHintInterface* InHint);

	FORCEINLINE TArray<IIGCrystalInterface*> GetArrCrystals(){return ArrCrystals;}
	FORCEINLINE TArray<IIGHintInterface*> GetArrHints(){return ArrHints;}
	
private:
	TArray<IIGCrystalInterface*> ArrCrystals;
	TArray<IIGHintInterface*> ArrHints;
	
};
