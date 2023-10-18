// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Interface/Interactable.h"
#include "IGOldTree.generated.h"

UCLASS()
class INDIGO_API AIGOldTree : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGOldTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(void) override;
private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;
};
