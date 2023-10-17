// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/CommonMonsters/IGHintMonsterBase.h"
#include "IGMountainSectorMonster.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API AIGMountainSectorMonster : public AIGHintMonsterBase
{
	GENERATED_BODY()
public:
	AIGMountainSectorMonster();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
