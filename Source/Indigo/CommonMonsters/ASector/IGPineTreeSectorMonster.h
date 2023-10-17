// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/CommonMonsters/IGHintMonsterBase.h"
#include "IGPineTreeSectorMonster.generated.h"

UCLASS()
class INDIGO_API AIGPineTreeSectorMonster : public AIGHintMonsterBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGPineTreeSectorMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
