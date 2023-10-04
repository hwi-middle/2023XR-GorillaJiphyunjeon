// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Util/IGScriptDataTable.h"
#include "IGCrystalParent.generated.h"

struct FIGScriptDataTable;

UCLASS()
class INDIGO_API AIGCrystalParent : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGCrystalParent();
	AIGCrystalParent(FString InPath, FName InName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
	virtual void TakeCrystal();
	
	virtual FORCEINLINE bool IsGetCrystal() const {return bIsGetCrystal;}
	virtual FORCEINLINE FString GetCrystalName() const {return MountainCrystalScript->Name;};
private:
	TObjectPtr<UStaticMeshComponent> Mesh;
	FIGScriptDataTable* MountainCrystalScript;
	uint8 bIsGetCrystal : 1;

};
