// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Util/IGScriptDataTable.h"
#include "IGCrystalBase.generated.h"

struct FIGScriptDataTable;

UENUM()
enum class ECrystal : uint32
{
	Tree,
	Wave,
	Mountain,
};

UCLASS()
class INDIGO_API AIGCrystalBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIGCrystalBase();
	AIGCrystalBase(FString InPath, FName InName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
	virtual void Take();

	virtual FORCEINLINE bool IsTaken() const { return bIsTaken; }
	virtual FORCEINLINE FString GetCrystalName() const { return CrystalScript->Name; }
	virtual FORCEINLINE ECrystal GetCrystalType() const { return CrystalType; }

private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;

	FIGScriptDataTable* CrystalScript;

	UPROPERTY()
	uint8 bIsTaken : 1;

	UPROPERTY()
	ECrystal CrystalType;
};
