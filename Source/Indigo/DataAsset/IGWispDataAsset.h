// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "IGWispDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGWispDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	//일반몬스터 데이터
	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "MaxHP")
	float MaxHp;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "Bomb Damage")
	float BombDamage;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "Dash Damage")
	float DashDamage;

	UPROPERTY(EditAnywhere, Category = "Status", DisplayName = "Speed")
	float Speed;
	
	//드랍 확률
	UPROPERTY(EditAnywhere, Category = "ItemPercent", DisplayName = "Crystal Percent")	
	float CrystalPercent;

	UPROPERTY(EditAnywhere, Category = "ItemPercent", DisplayName = "HealkitPercent")
	float HealkitPercent;

};
