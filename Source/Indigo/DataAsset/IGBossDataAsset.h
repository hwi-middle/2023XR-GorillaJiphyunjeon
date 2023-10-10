// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "IGBossDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGBossDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "추격 정지 거리")
	float StoppingDistance;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "최대 체력")
	float MaxHp;
};
