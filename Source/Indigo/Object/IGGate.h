// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/PhasePlace/IGPhasePlaceBase.h"
#include "IGGate.generated.h"

class AIGBossGatePlace;

UCLASS()
class INDIGO_API AIGGate : public AIGPhasePlaceBase, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void EnterPhasePlace();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION()
	void OpenGate();
	
	FORCEINLINE void SetIsOpen(const bool InValue) {bIsOpen = InValue;}
	FORCEINLINE bool GetIsOpen() const {return bIsOpen;}

	virtual void Interact() override;
	
private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY()
	uint8 bIsOpen : 1;
	UPROPERTY()
	FVector OffSet;
	UPROPERTY()
	float ElapsedTime; 
	UPROPERTY()
	float RotationTime;
	UPROPERTY()
	FRotator TargetRotation;
	UPROPERTY()
	FRotator StartRotation;
	UPROPERTY()
	TObjectPtr<AIGBossGatePlace> BossGatePlace;
	
};
