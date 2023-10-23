// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGProjectileBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHitProjectile)

UENUM()
enum EProjectileSpawnType
{
	SpawnedByPlayer,
	SpawnedByEnemy,
};

UCLASS()
class INDIGO_API AIGProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY()
	TEnumAsByte<EProjectileSpawnType> SpawnType;
	
	UPROPERTY()
	float Damage;

	UPROPERTY()
	float Duration;

	UPROPERTY()
	float ElapsedTime;
	
public:
	FOnHitProjectile OnHitProjectile;
};
