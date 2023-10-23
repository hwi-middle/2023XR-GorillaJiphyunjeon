// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGProjectile.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHitProjectile)

UENUM()
enum EProjectileType
{
	SpawnedByPlayer,
	SpawnedByEnemy
};

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
	TEnumAsByte<EProjectileType> ProjectileType;
	
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
	 FOnHitProjectile OnHitProjectile;
	void Init(float InDamage, const FVector& InTargetDirection, float MaxDistance, float InSpeed, EProjectileType InType);
};
