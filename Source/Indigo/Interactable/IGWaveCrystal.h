// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Interface/IGCrystalInterface.h"
#include "Indigo/Util/IGScriptDataTable.h"
#include "IGWaveCrystal.generated.h"

struct FIGScriptDataTable;

UCLASS()
class INDIGO_API AIGWaveCrystal : public AActor, public IInteractable, public IIGCrystalInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGWaveCrystal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;
	virtual void TakeCrystal() override;
	
	virtual FORCEINLINE bool IsGetCrystal() const override{return bIsGetCrystal;};
	virtual FORCEINLINE FString GetCrystalName() const override{return WaveCrystalScript->Name;};
	
private:
	TObjectPtr<UStaticMeshComponent> Mesh;
	FIGScriptDataTable* WaveCrystalScript;
	uint8 bIsGetCrystal : 1;
};
