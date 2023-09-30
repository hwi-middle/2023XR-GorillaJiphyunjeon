// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGProjectile.generated.h"

UCLASS()
class INDIGO_API AIGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY()
	float Damage;

	UPROPERTY()
	FVector OriginalPosition;
	
	UPROPERTY()
	FVector TargetPosition;

	UPROPERTY()
	float Duration;

	UPROPERTY()
	float ElapsedTime;
	
public:
	void Init(float InDamage, FVector InTargetDirection, float MaxDistance, float InSpeed);
};
