// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGGate.generated.h"

UCLASS()
class INDIGO_API AIGGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OpenGate();

	FORCEINLINE void SetIsOpen(const bool InValue) {bIsOpen = InValue;}


	FORCEINLINE bool GetIsOpen() const {return bIsOpen;}
	
private:
	TObjectPtr<UStaticMeshComponent> Mesh;
	uint8 bIsOpen : 1;
	FVector OffSet;
	float PerSecond; 
	
};
