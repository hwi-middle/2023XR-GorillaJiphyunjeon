// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGMountainSpike.generated.h"

UCLASS()
class INDIGO_API AIGMountainSpike : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGMountainSpike();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY()
	uint32 bIsInitialized : 1;

	UPROPERTY()
	float ElapsedTime;
	
	UPROPERTY()
	float Duration;

	UPROPERTY()
	float GenerationDelay;
	
	UPROPERTY()
	float DestroyDelay;

	UPROPERTY()
	FVector OriginPos;

	UPROPERTY()
	FVector TargetPos;

public:
	void Init(const float InHeight, const float InGenerationDelay, const float InDuration, const float InDestroyDelay);
};
