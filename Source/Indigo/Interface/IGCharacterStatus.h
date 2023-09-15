// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IGCharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIGCharacterStatus : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INDIGO_API IIGCharacterStatus
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//체력
	virtual uint32 GetHp() const = 0;
	virtual void HasDamage(const uint32 InValue) = 0;

	//공격력
	virtual uint32 GetAttackValue() const = 0;
	virtual void SetAttackValue(const uint32 InValue) = 0;

	//공격 속도
	virtual uint32 GetAttackRate() const = 0;
	virtual void SetAttackRate(const uint32 InValue) = 0;

	//공격 사거리
	virtual uint32 GetAttackRange() const = 0;
	virtual void SetAttackRange(const uint32 InValue) = 0;

	//방어력
	virtual uint32 GetDefenceValue() const = 0;
	virtual void SetDefenseValue(const uint32 InValue) = 0;

	//스테미나
	virtual uint32 GetStaminaValue() const = 0;
	virtual void SetStaminaValue(const uint32 InValue) = 0;

	//사망 여부
	virtual bool IsDead() const = 0;
};
