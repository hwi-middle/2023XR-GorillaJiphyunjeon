// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Indigo/Animation/IGPlayerAnimInstance.h"
#include "Indigo/Battle/IGProjectile.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Inventory/IGPlayerInventory.h"
#include "Indigo/UI/IGIngameHUDWidget.h"
#include "Indigo/Util/IGCharacterDataTable.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"

#include "Indigo/Inventory/IGPlayerInventory.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "Indigo/Util/IGSoundDataAsset.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

AIGPlayerCharacter::AIGPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 400.0f;
	CameraSpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	CharacterDataTable = nullptr;
	CharacterDataTable = FIGDataTableParser::LoadAndGetDataTableStruct<FIGCharacterDataTable>(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/CharaterDatabase.CharaterDatabase'"), TEXT("Player"));

	Hp = CharacterDataTable->HPValue;
	AttackValue = CharacterDataTable->AttackValue;
	AttackRange = CharacterDataTable->AttackRange;
	AttackRate = CharacterDataTable->AttackRate;
	DefenceValue = CharacterDataTable->DefenseValue;
	StaminaValue = CharacterDataTable->StaminaValue;

	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Main/Mesh/SK_Main.SK_Main'"), [&](USkeletalMesh* SkeletalMesh)
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh);
		// Temporal
		GetMesh()->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	}, EAssertionLevel::Check);

	PlayerInventory = CreateDefaultSubobject<UIGPlayerInventory>(TEXT("Inventory"));

	DefaultMappingContext = FIGConstructorHelper::FindAndGetObject<UInputMappingContext>(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/_GorillaJiphyunjeon/Input/IMC_Default.IMC_Default'"));
	MoveAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Move.IA_Move'"));
	LookAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Look.IA_Look'"));
	RunAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Run.IA_Run'"));
	InteractAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Interact.IA_Interact'"));
	RollAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Roll.IA_Roll'"));
	AttackAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Attack.IA_Attack'"));
	ToggleSunMoonAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_ToggleSunMoon.IA_ToggleSunMoon'"));
	Crystal1Action = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Crystal1.IA_Crystal1'"));
	Crystal2Action = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Crystal2.IA_Crystal2'"));
	Crystal3Action = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Crystal3.IA_Crystal3'"));

	const TSubclassOf<UIGPlayerAnimInstance> BossAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGPlayerAnimInstance>(
		TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Main/Animaion/ABP_Player.ABP_Player_C"), EAssertionLevel::Check);
	GetMesh()->SetAnimInstanceClass(BossAnimInstanceClass);

	FIGConstructorHelper::FindClassAndInitialize<UIGIngameHUDWidget>(TEXT("/Game/_GorillaJiphyunjeon/UI/Game/WBP_GameHUD.WBP_GameHUD_C"), [&](TSubclassOf<UIGIngameHUDWidget> Class)
	{
		HudWidgetClass = Class;
	}, EAssertionLevel::Check);

	
	TestSoundDataAsset = LoadObject<UIGSoundDataAsset>(nullptr, TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/SoundCueDataAsset.SoundCueDataAsset'"), nullptr, LOAD_None, nullptr, nullptr);
	
	
	WalkSpeed = 500.f;
	SprintSpeed = 800.f;

	SunMoonValue = 0;
	SunMoonRecoveryAmountOnAttackHit = 5;
	SunMoonSection2Threshold = 30;
	SunMoonSection3Threshold = 70;
	SunMoonSection1DamageScaleFactor = 1;
	SunMoonSection2DamageScaleFactor = 2;
	SunMoonSection3DamageScaleFactor = 3;
	SunMoonConsumptionAmountOnAttack = 10;
	ExhaustionPhase1Duration = 3.f;
	ExhaustionPhase2Duration = 10.f;
	SunMoonAutoConsumptionDelay = 5.f;
	ElapsedSunMoonAutoConsumptionTime = 0.f;
	SunMoonAutoConsumptionAmount = 2;
	StaminaRecoveryAmountPerSecondOnIdle = 10.f;
	StaminaRecoveryAmountPerSecondOnWalk = 2.f;
	StaminaConsumptionAmountPerSecondOnRunning = 2.f;
	StaminaConsumptionAmountOnRoll = 10.f;
	ActivatedCrystal = ECrystal::None;

	NormalAttackDamage = 3;
	StrongAttackDamage = 7;
	StaminaConsumptionAmountOnNormalAttack = 5;
	StaminaConsumptionAmountOnStrongAttack = 7;
}

bool AIGPlayerCharacter::CheckPlayerState(const EPlayerState InState) const
{
	return EnumHasAnyFlags(CurrentState, InState);
}

void AIGPlayerCharacter::AddPlayerState(const EPlayerState InState)
{
	EnumAddFlags(CurrentState, InState);
}

void AIGPlayerCharacter::RemovePlayerState(const EPlayerState InState)
{
	EnumRemoveFlags(CurrentState, InState);
}

void AIGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	AnimInstance = CastChecked<UIGPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->SetSpeed(0.f);
	AnimInstance->OnFinishRoll.AddUObject(this, &AIGPlayerCharacter::FinishRolling);
	AnimInstance->OnFinishAttack.AddUObject(this, &AIGPlayerCharacter::FinishAttack);
	CurrentState = EPlayerState::Idling;

	HudWidget = CreateWidget<UIGIngameHUDWidget>(GetWorld(), HudWidgetClass);
	if (HudWidget)
	{
		HudWidget->AddToViewport();
		HudWidget->InitHpGauge(100.f, Hp);
		HudWidget->InitStaminaGauge(100.f, StaminaValue);
		HudWidget->InitSunMoonGauge(100.f, 0.f);
	}

	ManageStaminaByTime();
}

void AIGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if UE_EDITOR
	// Hp = CharacterDataTable->HPValue;
	// AttackValue = CharacterDataTable->AttackValue;
	// AttackRange = CharacterDataTable->AttackRange;
	// AttackRate = CharacterDataTable->AttackRate;
	// DefenceValue = CharacterDataTable->DefenseValue;
	// StaminaValue = CharacterDataTable->StaminaValue;
	FString DebugMessage = TEXT("<플레이어 상태>\n");

	if (CheckPlayerState(EPlayerState::Idling))
	{
		DebugMessage.Append(TEXT("정지\n"));
	}
	if (CheckPlayerState(EPlayerState::Walking))
	{
		DebugMessage.Append(TEXT("걷기\n"));
	}
	if (CheckPlayerState(EPlayerState::Running))
	{
		DebugMessage.Append(TEXT("달리기\n"));
	}
	if (CheckPlayerState(EPlayerState::Rolling))
	{
		DebugMessage.Append(TEXT("구르기\n"));
	}
	if (CheckPlayerState(EPlayerState::Attacking))
	{
		DebugMessage.Append(TEXT("공격\n"));
	}
	if (CheckPlayerState(EPlayerState::Enforced))
	{
		DebugMessage.Append(TEXT("강화됨\n"));
	}
	if (CheckPlayerState(EPlayerState::ExhaustedPhase1))
	{
		DebugMessage.Append(TEXT("탈진상태(게이지 획득 불가)\n"));
	}
	if (CheckPlayerState(EPlayerState::ExhaustedPhase2))
	{
		DebugMessage.Append(TEXT("탈진상태(게이지 획득량 감소)\n"));
	}
	if (CheckPlayerState(EPlayerState::CrystalActivated))
	{
		DebugMessage.Append(TEXT("결정 활성화 됨\n"));
	}
	if (CheckPlayerState(EPlayerState::CrystalCooldown))
	{
		DebugMessage.Append(TEXT("결정 활성화 쿨타임\n"));
	}
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, *DebugMessage);
#endif
	AnimInstance->SetSpeed(GetVelocity().Size2D());
}

void AIGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AIGPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AIGPlayerCharacter::SetIsIdling);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AIGPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AIGPlayerCharacter::SetIsRunning);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AIGPlayerCharacter::SetIsRunning);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AIGPlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, this, &AIGPlayerCharacter::StartRolling);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AIGPlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(ToggleSunMoonAction, ETriggerEvent::Started, this, &AIGPlayerCharacter::ToggleSunMoon);
		EnhancedInputComponent->BindAction(Crystal1Action, ETriggerEvent::Started, this, &AIGPlayerCharacter::ActivateCrystal1);
		EnhancedInputComponent->BindAction(Crystal2Action, ETriggerEvent::Started, this, &AIGPlayerCharacter::ActivateCrystal2);
		EnhancedInputComponent->BindAction(Crystal3Action, ETriggerEvent::Started, this, &AIGPlayerCharacter::ActivateCrystal3);
	}
}

void AIGPlayerCharacter::Move(const FInputActionValue& Value)
{
	RemovePlayerState(EPlayerState::Idling);
	if (!CheckPlayerState(EPlayerState::Running))
	{
		AddPlayerState(EPlayerState::Walking);
	}

	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller == nullptr)
	{
		return;
	}

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);

}

void AIGPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller == nullptr)
	{
		return;
	}

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AIGPlayerCharacter::SetIsIdling()
{
	RemovePlayerState(EPlayerState::Walking);
	RemovePlayerState(EPlayerState::Running);
	AddPlayerState(EPlayerState::Idling);
}

void AIGPlayerCharacter::SetIsRunning(const FInputActionValue& Value)
{
	const bool IsSprintKeyDown = Value.Get<bool>();
	if (IsSprintKeyDown)
	{
		RemovePlayerState(EPlayerState::Walking);
		AddPlayerState(EPlayerState::Running);
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
	else
	{
		RemovePlayerState(EPlayerState::Running);
		AddPlayerState(EPlayerState::Walking);
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AIGPlayerCharacter::Interact()
{
	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	float Radius = 100.f;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_INTERACTABLE,
		FCollisionShape::MakeSphere(Radius),
		CollisionParams
	);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Green, false, 2.f);

	if (!bHit)
	{
		return;
	}

	IInteractable* Interactable = Cast<IInteractable>(Result.GetActor());
	AIGCrystalBase* Crystal = Cast<AIGCrystalBase>(Result.GetActor());

	if (Interactable != nullptr)
	{
		Interactable->Interact();

		if (Crystal != nullptr)
		{
			PlayerInventory->AddCrystal(Crystal);
		}
	}
}

void AIGPlayerCharacter::Attack()
{
	if (CheckPlayerState(EPlayerState::Attacking) || CheckPlayerState(EPlayerState::Rolling))
	{
		return;
	}

	const bool IsEnforced = CheckPlayerState(EPlayerState::Enforced);
	// 스태미너 부족
	const float Cost = IsEnforced ? StaminaConsumptionAmountOnStrongAttack : StaminaConsumptionAmountOnNormalAttack;
	if (StaminaValue < Cost)
	{
		return;
	}

	//StaminaValue -= Cost;
	HudWidget->UpdateStaminaGauge(StaminaValue);

	AddPlayerState(EPlayerState::Attacking);
	ElapsedSunMoonAutoConsumptionTime = 0.f;
	AnimInstance->SetEnforced(IsEnforced);
	AnimInstance->StartAttack();

	float DamageScaleFactor = 1;
	if (IsEnforced)
	{
		SunMoonValue -= SunMoonConsumptionAmountOnAttack;
		if (SunMoonValue < 0)
		{
			SunMoonValue = 0;
			RemovePlayerState(EPlayerState::Enforced);
			AddPlayerState(EPlayerState::ExhaustedPhase1);
			EnableExhaustion();
		}

		HudWidget->UpdateSunMoonGauge(SunMoonValue);

		// 데미지 배율 계산
		if (SunMoonValue >= SunMoonSection3Threshold)
		{
			DamageScaleFactor = SunMoonSection3DamageScaleFactor;
		}
		else if (SunMoonValue >= SunMoonSection2Threshold)
		{
			DamageScaleFactor = SunMoonSection2DamageScaleFactor;
		}
		else
		{
			DamageScaleFactor = SunMoonSection1DamageScaleFactor;
		}
	}

	// ---- Temporal (Socket 등으로 위치 조정해줘야함)
	const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
	AIGProjectile* SpawnedActor = GetWorld()->SpawnActor<AIGProjectile>(SpawnLocation, FRotator::ZeroRotator);
	const float Damage = IsEnforced ? StrongAttackDamage * DamageScaleFactor : NormalAttackDamage;
	SpawnedActor->Init(Damage, GetActorForwardVector(), 1000.f, 10.f);
	SpawnedActor->OnHitProjectile.AddUObject(this, &AIGPlayerCharacter::OnHitProjectile);
	// ----
	UGameplayStatics::PlaySound2D(this, TestSoundDataAsset->PlayerAttackSoundCue);
}

void AIGPlayerCharacter::FinishAttack()
{
	RemovePlayerState(EPlayerState::Attacking);
}

void AIGPlayerCharacter::StartRolling()
{
	if (CheckPlayerState(EPlayerState::Rolling))
	{
		return;
	}

	if (StaminaValue < StaminaConsumptionAmountOnRoll)
	{
		return;
	}

	StaminaValue -= StaminaConsumptionAmountOnRoll;
	HudWidget->UpdateStaminaGauge(StaminaValue);

	AddPlayerState(EPlayerState::Rolling);
	AnimInstance->StartRoll();
	UGameplayStatics::PlaySound2D(this, TestSoundDataAsset->PlayerRollingSoundCue);
}

void AIGPlayerCharacter::FinishRolling()
{
	RemovePlayerState(EPlayerState::Rolling);
}

void AIGPlayerCharacter::ToggleSunMoon()
{
	if (CheckPlayerState(EPlayerState::Enforced))
	{
		RemovePlayerState(EPlayerState::Enforced);
	}
	else
	{
		AddPlayerState(EPlayerState::Enforced);
		ConsumeSunMoonByTime();
	}
}

void AIGPlayerCharacter::ConsumeSunMoonByTime()
{
	static bool bIsInitialDelayDone = false;
	const float DeltaTime = GWorld->DeltaTimeSeconds;
	ElapsedSunMoonAutoConsumptionTime += DeltaTime;

	if (!CheckPlayerState(EPlayerState::Enforced))
	{
		bIsInitialDelayDone = false;
		return;
	}

	if (!bIsInitialDelayDone)
	{
		if (ElapsedSunMoonAutoConsumptionTime < SunMoonAutoConsumptionDelay)
		{
			GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::ConsumeSunMoonByTime);
			return;
		}

		bIsInitialDelayDone = true;
		ensure(ElapsedSunMoonAutoConsumptionTime >= 1.f);
	}

	if (ElapsedSunMoonAutoConsumptionTime >= 1.f)
	{
		if (SunMoonValue < SunMoonAutoConsumptionAmount)
		{
			SunMoonValue = 0;
		}
		else
		{
			SunMoonValue -= SunMoonAutoConsumptionAmount;
		}
		HudWidget->UpdateSunMoonGauge(SunMoonValue);

		ElapsedSunMoonAutoConsumptionTime = 0.f;
	}

	GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::ConsumeSunMoonByTime);
}

void AIGPlayerCharacter::EnableExhaustion()
{
	static float ElapsedTime = 0.f;
	const float DeltaTime = GWorld->GetDeltaSeconds();
	ElapsedTime += DeltaTime;

	if (ElapsedTime <= ExhaustionPhase1Duration)
	{
		AddPlayerState(EPlayerState::ExhaustedPhase1);
	}
	else if (ElapsedTime <= ExhaustionPhase1Duration + ExhaustionPhase2Duration)
	{
		RemovePlayerState(EPlayerState::ExhaustedPhase1);
		AddPlayerState(EPlayerState::ExhaustedPhase2);
	}
	else
	{
		RemovePlayerState(EPlayerState::ExhaustedPhase1);
		RemovePlayerState(EPlayerState::ExhaustedPhase2);
		ElapsedTime = 0.f;
		return;
	}

	GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::EnableExhaustion);
}

void AIGPlayerCharacter::OnHitProjectile()
{
	if (CheckPlayerState(EPlayerState::ExhaustedPhase1) || CheckPlayerState(EPlayerState::Enforced))
	{
		return;
	}

	const uint32 ActualRecoveryAmount = CheckPlayerState(EPlayerState::ExhaustedPhase2) ? SunMoonRecoveryAmountOnAttackHit / 2 : SunMoonRecoveryAmountOnAttackHit;
	SunMoonValue += ActualRecoveryAmount;
	HudWidget->UpdateSunMoonGauge(SunMoonValue);
}

void AIGPlayerCharacter::ManageStaminaByTime()
{
	GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::ManageStaminaByTime);

	const float DeltaTime = GWorld->DeltaTimeSeconds;
	if (CheckPlayerState(EPlayerState::Idling))
	{
		StaminaValue += StaminaRecoveryAmountPerSecondOnIdle * DeltaTime;
	}
	else if (CheckPlayerState(EPlayerState::Walking))
	{
		StaminaValue += StaminaRecoveryAmountPerSecondOnWalk * DeltaTime;
	}
	else if (CheckPlayerState(EPlayerState::Running))
	{
		StaminaValue -= StaminaConsumptionAmountPerSecondOnRunning * DeltaTime;
	}
	else
	{
		return;
	}

	StaminaValue = FMath::Clamp(StaminaValue, 0.f, 100.f);
	HudWidget->UpdateStaminaGauge(StaminaValue);
}


void AIGPlayerCharacter::ActivateCrystalByIndex(uint32 Index)
{
	if (CheckPlayerState(EPlayerState::CrystalActivated) || CheckPlayerState(EPlayerState::CrystalCooldown))
	{
		return;
	}

	const TArray<AIGCrystalBase*> CrystalArray = PlayerInventory->GetCrystalArray();
	if (!CrystalArray.IsValidIndex(Index))
	{
		return;
	}

	const ECrystal Type = CrystalArray[Index]->GetCrystalType();
	ensure(Type != ECrystal::None);

	ActivatedCrystal = Type;
	switch (Type)
	{
	case ECrystal::Tree:
		UE_LOG(LogTemp, Log, TEXT("소나무의 결정 활성화"));
		break;
	case ECrystal::Wave:
		UE_LOG(LogTemp, Log, TEXT("물결의 결정 활성화"));
		break;
	case ECrystal::Mountain:
		UE_LOG(LogTemp, Log, TEXT("산의 결정 활성화"));
		break;
	case ECrystal::None:
		// intentional fall-through
	default:
		checkNoEntry();
	}

	AddPlayerState(EPlayerState::CrystalActivated);
	GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::ManageCrystalActivationByTime);
}

void AIGPlayerCharacter::ManageCrystalActivationByTime()
{
	constexpr float Duration = 3.f;
	const float DeltaTime = GWorld->DeltaTimeSeconds;
	ElapsedCrystalActivationTime += DeltaTime;
	
	if (ElapsedCrystalActivationTime >= Duration)
	{
		ActivatedCrystal = ECrystal::None;
		ElapsedCrystalActivationTime = 0.f;
		RemovePlayerState(EPlayerState::CrystalActivated);
		AddPlayerState(EPlayerState::CrystalCooldown);
		GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::ManageCrystalCooldownByTime);
		return;
	}

	GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::ManageCrystalActivationByTime);
}

void AIGPlayerCharacter::ManageCrystalCooldownByTime()
{
	constexpr float Duration = 5.f;
	const float DeltaTime = GWorld->DeltaTimeSeconds;
	ElapsedCrystalCooldownTime += DeltaTime;
	
	if (ElapsedCrystalCooldownTime >= Duration)
	{
		ElapsedCrystalCooldownTime = 0.f;
		RemovePlayerState(EPlayerState::CrystalCooldown);
		return;
	}
	
	GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::ManageCrystalCooldownByTime);
}



void AIGPlayerCharacter::ActivateCrystal1()
{
	ActivateCrystalByIndex(0);
}

void AIGPlayerCharacter::ActivateCrystal2()
{
	ActivateCrystalByIndex(1);
}

void AIGPlayerCharacter::ActivateCrystal3()
{
	ActivateCrystalByIndex(2);
}

void AIGPlayerCharacter::SetHp_DEBUG(const uint32 Value)
{
	Hp = Value;
	HudWidget->UpdateHpGauge(Hp);
}

void AIGPlayerCharacter::SetStaminaValue_DEBUG(const uint32 Value)
{
	StaminaValue = Value;
	HudWidget->UpdateStaminaGauge(StaminaValue);
}

void AIGPlayerCharacter::SetSunMoon_DEBUG(const uint32 Value)
{
	SunMoonValue = Value;
	HudWidget->UpdateSunMoonGauge(SunMoonValue);
}

void AIGPlayerCharacter::CheckCrystal_DEBUG()
{
	UE_LOG(LogTemp, Log, TEXT("크리스탈 목록"));

	auto CrystalArray = PlayerInventory->GetCrystalArray();
	for (auto Crystal : CrystalArray)
	{
		UE_LOG(LogTemp, Log, TEXT("[크리스탈]: %s"), *Crystal->GetCrystalName());
	}
}
