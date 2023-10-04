// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGHintBase.h"
#include "IGBlankHint.generated.h"

struct FIGScriptDataTable;

UCLASS()
class INDIGO_API AIGBlankHint : public AIGHintBase
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AIGBlankHint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override; 

};
