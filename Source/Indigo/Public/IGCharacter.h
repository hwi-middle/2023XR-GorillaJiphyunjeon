// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IGCharacter.generated.h"

//캐릭터 배치전 상태
UENUM()
enum class EPreState : uint8
{
	NONE = 0, // 준비를 실패하거나 아직 불러오기 전 상태
	PreInt,	  // 애셋이 준비 된 상태
	Loading,  // 캐릭터를 레벨로 불러오는 상태
	Ready	  // 준비가 완료되어 배치된 상태
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIGCharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INDIGO_API IIGCharacter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//체력
	virtual uint32  GetHp() const = 0;
	
	virtual void HasDamage(const uint32& InDamageGauge) = 0;

	//공격력
	virtual uint32  GetAttValue() const = 0;

	virtual void SetAttValue(const uint32& InAttDamageValue) = 0;

	//공격 속도
	virtual uint32  GetAttRate() const = 0;

	virtual void SetAttRate(const uint32& InAttRate) = 0;

	//공격 사거리
	virtual uint32  GetAttRange() const = 0;

	virtual void SetAttRange(const uint32& InArrRange) = 0;


	//방어력
	virtual uint32  GetDefValue() const = 0;

	virtual void SetDefValue(const uint32& InDefValue) = 0;

	//스테미나
	virtual uint32 GetStaminaValue() const = 0;

	virtual void SetStaminaValue(const uint32& InActionGauge) = 0;

	//사망 유무
	virtual uint8 IsDead() const = 0;

	//현재PreState 
	virtual EPreState GetPreState() = 0;

};
