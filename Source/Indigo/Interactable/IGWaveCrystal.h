// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGCrystalBase.h"
#include "IGWaveCrystal.generated.h"

struct FIGScriptDataTable;

UCLASS()
class INDIGO_API AIGWaveCrystal : public AIGCrystalBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGWaveCrystal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;
	virtual void TakeCrystal() override;

};
