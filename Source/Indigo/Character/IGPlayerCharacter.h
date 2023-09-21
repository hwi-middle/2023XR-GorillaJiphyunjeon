// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Indigo/Interface/IGCharacterStatus.h"
#include "IGPlayerCharacter.generated.h"

class UIGDataParser;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class INDIGO_API AIGPlayerCharacter : public ACharacter, public IIGCharacterStatus
{


private:
    GENERATED_BODY()

public:
    AIGPlayerCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    //인터페이스 함수
    virtual FORCEINLINE uint32 GetHp() const override {return this->Hp;}
    virtual FORCEINLINE void SetHp(const uint32 InValue) override{this->Hp = InValue;}
    virtual FORCEINLINE uint32 GetAttackValue() const override {return AttackValue;}
    virtual FORCEINLINE void SetAttackValue(const uint32 InValue) override {this->AttackValue = InValue;}
    virtual FORCEINLINE uint32 GetAttackRate() const override {return this->AttackRate;}
    virtual FORCEINLINE void SetAttackRate(const uint32 InValue) override {this->AttackRate = InValue;}
    virtual FORCEINLINE uint32 GetAttackRange() const override {return this->AttackRange;}
    virtual FORCEINLINE void SetAttackRange(const uint32 InValue) override {this->AttackRange = InValue;}
    virtual FORCEINLINE uint32 GetDefenceValue() const override {return this->DefenceValue;}
    virtual FORCEINLINE void SetDefenseValue(const uint32 InValue) override {this->DefenceValue = InValue;}
    virtual FORCEINLINE uint32 GetStaminaValue() const override {return this->StaminaValue;}
    virtual FORCEINLINE void SetStaminaValue(const uint32 InValue) override {this->StaminaValue = InValue;}
    virtual FORCEINLINE bool IsDead() const override {return bIsDead;} 
    
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraSpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* RunAction;

protected:
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void SetIsRunning(const FInputActionValue& Value);

public:
    FORCEINLINE USpringArmComponent* GetCameraSpringArm() const { return CameraSpringArm; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
    //멤버 변수
    UPROPERTY(VisibleAnywhere)
    uint32 Hp;
    UPROPERTY(VisibleAnywhere)
    uint32 AttackValue;
    UPROPERTY(VisibleAnywhere)
    uint32 AttackRate;
    UPROPERTY(VisibleAnywhere)
    uint32 AttackRange;
    UPROPERTY(VisibleAnywhere)
    uint32 DefenceValue;
    UPROPERTY(VisibleAnywhere)
    uint32 StaminaValue;
    UPROPERTY(VisibleAnywhere)
    uint8 bIsDead : 1;

    UIGDataParser* CharacterDataParser;
    
};
