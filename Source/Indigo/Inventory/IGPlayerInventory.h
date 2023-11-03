// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/Interface/IGHintInterface.h"
#include "Components/ActorComponent.h"
#include "IGPlayerInventory.generated.h"

class AIGCrystalBase;
class AIGMountainCrystal;
class AIGWaveCrystal;
class AIGTreeCrystal;
class AIGHintBase;
enum class EHintType : uint8;
enum class ECrystal : uint32;

struct ProvisoText;

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
	void AddCrystal(ECrystal InCrystalType);

	void AddHint(ProvisoText* InHint);

	FORCEINLINE TArray<AIGMountainCrystal*> GetMountainCrystalArray() { return MountainCrystalArray; }
	FORCEINLINE TArray<AIGWaveCrystal*> GetWaveCrystalArray() { return WaveCrystalArray; }
	FORCEINLINE TArray<AIGTreeCrystal*> GetTreeCrystalArray() { return TreeCrystalArray; }
	FORCEINLINE TArray<ProvisoText*> GetHintArray() { return HintArray; }

private:
	UPROPERTY()
	TArray<AIGMountainCrystal*> MountainCrystalArray;
	
	UPROPERTY()
	TArray<AIGWaveCrystal*> WaveCrystalArray;
	
	UPROPERTY()
	TArray<AIGTreeCrystal*> TreeCrystalArray;

	
	TArray<ProvisoText*> HintArray;
	
	UPROPERTY()
	uint8 bIsGetFirstCrystalFrag : 1;
	UPROPERTY()
	uint8 bIsGetFirstHint : 1;
	UPROPERTY()
	uint8 bIsGetFirstBlankHint : 1;
	UPROPERTY()
	uint8 bIsGet2HintBySameProviso : 1;
	UPROPERTY()
	uint8 bIsGetFirstCrystal : 1;
	
	UPROPERTY()
	float CantFindProvisoTime;	
};
