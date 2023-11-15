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

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


	UPROPERTY()
	uint32 bIsInitialized : 1;

	UPROPERTY()
	uint32 bHasDamagedPlayer : 1;
	
	UPROPERTY()
	float ElapsedTime;
	
	UPROPERTY()
	float Duration;

	UPROPERTY()
	float Damage;
	
	UPROPERTY()
	float GenerationDelay;
	
	UPROPERTY()
	float DestroyDelay;
	
	UPROPERTY()
	float DamageRadius;

	UPROPERTY()
	FVector OriginPos;

	UPROPERTY()
	FVector TargetPos;

public:
	void Init(const float InDamage, const float InHeight, const float InGenerationDelay, const float InDuration, const float InDestroyDelay, const float InDamageRadius = 150.f);
};
