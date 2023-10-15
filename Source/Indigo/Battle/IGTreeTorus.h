// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGTreeTorus.generated.h"

class UStaticMeshComponent;

UCLASS()
class INDIGO_API AIGTreeTorus : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIGTreeTorus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init(float InScaleFactor, float InDuration);

private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY()
	float ScaleFactorPerSecond;

	UPROPERTY()
	float Duration;

	UPROPERTY()
	float ElapsedTime;

	UPROPERTY()
	uint32 bIsInitialized : 1;

	UPROPERTY()
	uint32 bHasDamagedPlayer : 1;

	UPROPERTY()
	uint32 bHasIgnored : 1;

	UPROPERTY()
	float CurrentScale;
};
