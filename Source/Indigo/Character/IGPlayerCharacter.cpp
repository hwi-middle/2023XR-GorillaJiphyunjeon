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
#include "Engine/PostProcessVolume.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Indigo/Animation/IGPlayerAnimInstance.h"
#include "Indigo/Battle/IGProjectile.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/DataAsset/IGPlayerControlDataAsset.h"
#include "Indigo/DataAsset/IGPlayerDataAsset.h"
#include "Indigo/DataAsset/IGSoundDataAsset.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Inventory/IGPlayerInventory.h"
#include "Indigo/UI/IGIngameHUDWidget.h"
#include "Indigo/Util/IGCharacterDataTable.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "Indigo/Interactable/IGHintBase.h"
#include "Indigo/UI/QuestUI/IGQuest.h"

AIGPlayerCharacter::AIGPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

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

	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Main/Mesh/SM_Main_Rigging.SM_Main_Rigging'"), [&](USkeletalMesh* SkeletalMesh)
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh);
		// Temporal
		GetMesh()->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	}, EAssertionLevel::Check);

	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/PlayerWeapon/Mesh/SM_Weapon.SM_Weapon'"), [&](UStaticMesh* MeshRef)
	{
		BrushMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrushMesh"));
		BrushMesh->SetStaticMesh(MeshRef);
		BrushMesh->SetWorldLocation(GetMesh()->GetSocketLocation(TEXT("RightHand")));
		BrushMesh->SetupAttachment(GetMesh());

	}, EAssertionLevel::Check);



	PlayerControlDataAsset = FIGConstructorHelper::FindAndGetObject<UIGPlayerControlDataAsset>(TEXT("/Script/Indigo.IGPlayerControlDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_PlayerControlData.DA_PlayerControlData'"));
	DefaultMappingContext = PlayerControlDataAsset->DefaultMappingContext;
	MoveAction = PlayerControlDataAsset->MoveAction;
	LookAction = PlayerControlDataAsset->LookAction;
	RunAction = PlayerControlDataAsset->RunAction;
	InteractAction = PlayerControlDataAsset->InteractAction;
	RollAction = PlayerControlDataAsset->RollAction;
	AttackAction = PlayerControlDataAsset->AttackAction;
	ToggleSunMoonAction = PlayerControlDataAsset->ToggleSunMoonAction;
	Crystal1Action = PlayerControlDataAsset->Crystal1Action;
	Crystal2Action = PlayerControlDataAsset->Crystal2Action;
	Crystal3Action = PlayerControlDataAsset->Crystal3Action;

	const TSubclassOf<UIGPlayerAnimInstance> BossAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGPlayerAnimInstance>(
		TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Main/Animaion/ABP_Player.ABP_Player_C"), EAssertionLevel::Check);
	GetMesh()->SetAnimInstanceClass(BossAnimInstanceClass);

	FIGConstructorHelper::FindClassAndInitialize<UIGIngameHUDWidget>(TEXT("/Game/_GorillaJiphyunjeon/UI/Game/WBP_GameHUD.WBP_GameHUD_C"), [&](TSubclassOf<UIGIngameHUDWidget> Class)
	{
		HudWidgetClass = Class;
	}, EAssertionLevel::Check);
	
	PlayerInventory = CreateDefaultSubobject<UIGPlayerInventory>(TEXT("Inventory"));
	Shinmyophil = CreateDefaultSubobject<UIGShinmyophil>(TEXT("Shinmyophil"));
	

	TestSoundDataAsset = LoadObject<UIGSoundDataAsset>(nullptr, TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_SoundCueData.DA_SoundCueData'"), nullptr, LOAD_None, nullptr, nullptr);
	PlayerDataAsset = FIGConstructorHelper::FindAndGetObject<UIGPlayerDataAsset>(TEXT("/Script/Indigo.IGPlayerDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_PlayerData.DA_PlayerData'"));
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
	
	WalkSpeed = PlayerDataAsset->WalkSpeed;
	SprintSpeed = PlayerDataAsset->SprintSpeed;
	RollSpeed = PlayerDataAsset->RollSpeed;

	SunMoonValue = 0.f;
	SunMoonRecoveryAmountOnAttackHit = PlayerDataAsset->SunMoonRecoveryAmountOnAttackHit;
	SunMoonSection2Threshold = PlayerDataAsset->SunMoonSection2Threshold;
	SunMoonSection3Threshold = PlayerDataAsset->SunMoonSection3Threshold;
	SunMoonSection1DamageScaleFactor = PlayerDataAsset->SunMoonSection1DamageScaleFactor;
	SunMoonSection2DamageScaleFactor = PlayerDataAsset->SunMoonSection2DamageScaleFactor;
	SunMoonSection3DamageScaleFactor = PlayerDataAsset->SunMoonSection3DamageScaleFactor;
	SunMoonConsumptionAmountOnAttack = PlayerDataAsset->SunMoonConsumptionAmountOnAttack;
	ExhaustionPhase1Duration = PlayerDataAsset->ExhaustionPhase1Duration;
	ExhaustionPhase2Duration = PlayerDataAsset->ExhaustionPhase2Duration;
	SunMoonAutoConsumptionDelay = PlayerDataAsset->SunMoonAutoConsumptionDelay;
	ElapsedSunMoonAutoConsumptionTime = 0.f;
	SunMoonAutoConsumptionAmount = PlayerDataAsset->SunMoonAutoConsumptionAmount;
	StaminaRecoveryAmountPerSecondOnIdle = PlayerDataAsset->StaminaRecoveryAmountPerSecondOnIdle;
	StaminaRecoveryAmountPerSecondOnWalk = PlayerDataAsset->StaminaRecoveryAmountPerSecondOnWalk;
	StaminaConsumptionAmountPerSecondOnRunning = PlayerDataAsset->StaminaConsumptionAmountPerSecondOnRunning;
	StaminaConsumptionAmountOnRoll = PlayerDataAsset->StaminaConsumptionAmountOnRoll;
	ActivatedCrystal = ECrystal::None;

	NormalAttackDamageMin = PlayerDataAsset->NormalAttackDamageMin;
	NormalAttackDamageMax = PlayerDataAsset->NormalAttackDamageMax;
	StrongAttackDamageMin = PlayerDataAsset->StrongAttackDamageMin;
	StrongAttackDamageMax = PlayerDataAsset->StrongAttackDamageMax;

	StaminaConsumptionAmountOnNormalAttack = PlayerDataAsset->StaminaConsumptionAmountOnNormalAttack;
	StaminaConsumptionAmountOnStrongAttack = PlayerDataAsset->StaminaConsumptionAmountOnStrongAttack;
	DieZLocation = PlayerDataAsset->DieZLocation;
	ElapsedDieSequenceTime = 0.f;
	ElapsedFadeSequenceTime = 0.f;

	AnimInstance = CastChecked<UIGPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->SetSpeed(0.f);
	AnimInstance->OnFinishRoll.AddUObject(this, &AIGPlayerCharacter::FinishRolling);
	AnimInstance->OnFinishAttack.AddUObject(this, &AIGPlayerCharacter::FinishAttack);
	CurrentState = EPlayerState::Idling;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	HudWidget = CreateWidget<UIGIngameHUDWidget>(GetWorld(), HudWidgetClass);
	if (HudWidget)
	{
		HudWidget->AddToViewport();
		HudWidget->InitHpGauge(100.f, Hp);
		HudWidget->InitStaminaGauge(100.f, StaminaValue);
		HudWidget->InitSunMoonGauge(100.f, 0.f);
	

		for(int i= 0; i < Shinmyophil->GetQuestArray().Num(); i++)
		{
			HudWidget->InitQuestList(Shinmyophil->GetQuestArray()[i]);			
		}
		
	}

	ManageStaminaByTime();

	if (!GWorld->PostProcessVolumes.IsEmpty())
	{
		PostProcessVolume = Cast<APostProcessVolume>(GetWorld()->PostProcessVolumes[0]);
		FPostProcessSettings Settings = PostProcessVolume->Settings;

		UMaterial* CustomPostProcessMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/_GorillaJiphyunjeon/Material/PostProcess/M_Grayscale.M_Grayscale'"));
		UMaterialInstanceDynamic* GrayscaleMaterial = UMaterialInstanceDynamic::Create(CustomPostProcessMaterial, nullptr);

		CustomPostProcessMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/_GorillaJiphyunjeon/Material/PostProcess/M_PPFade.M_PPFade'"));
		UMaterialInstanceDynamic* FadeMaterial = UMaterialInstanceDynamic::Create(CustomPostProcessMaterial, nullptr);
		
		Settings.WeightedBlendables.Array.Empty();
		Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1.0f, GrayscaleMaterial));
		Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1.0f, FadeMaterial));
		PostProcessVolume->Settings = Settings;
		DMI_Grayscale = GrayscaleMaterial;
		DMI_Fade = FadeMaterial;
		PlayFadeInSequence();
	}
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
	if (CheckPlayerState(EPlayerState::Dead))
	{
		DebugMessage.Append(TEXT("사망\n"));
	}
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, *DebugMessage);
#endif

	AnimInstance->SetSpeed(GetVelocity().Size2D());
	if (GetActorLocation().Z <= DieZLocation)
	{
		if (!CheckPlayerState(EPlayerState::Dead))
		{
			AnimInstance->Die();
			HudWidget->UpdateHpGauge(0.f);
			AddPlayerState(EPlayerState::Dead);
			bIsDead = true;
			PlayDieSequence();
		}
		FVector AdjustedLocation = GetActorLocation();
		AdjustedLocation.Z = DieZLocation;
		SetActorLocation(AdjustedLocation);
	}
	BrushMesh->SetWorldLocation(GetMesh()->GetSocketLocation(TEXT("RightHand")));
	BrushMesh->SetWorldRotation(GetMesh()->GetSocketRotation(TEXT("RightHand")));
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
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AIGPlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(ToggleSunMoonAction, ETriggerEvent::Started, this, &AIGPlayerCharacter::ToggleSunMoon);
		EnhancedInputComponent->BindAction(Crystal1Action, ETriggerEvent::Started, this, &AIGPlayerCharacter::ActivateCrystal1);
		EnhancedInputComponent->BindAction(Crystal2Action, ETriggerEvent::Started, this, &AIGPlayerCharacter::ActivateCrystal2);
		EnhancedInputComponent->BindAction(Crystal3Action, ETriggerEvent::Started, this, &AIGPlayerCharacter::ActivateCrystal3);
	}
}

float AIGPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CheckPlayerState(EPlayerState::Rolling))
	{
		return 0.f;
	}
	Hp -= DamageAmount;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Player HP: [%f]"), Hp));
	if (Hp <= 0)
	{
		AnimInstance->Die();
		HudWidget->UpdateHpGauge(0.f);
		AddPlayerState(EPlayerState::Dead);
		bIsDead = true;
		PlayDieSequence();
		return DamageAmount;
	}

	HudWidget->UpdateHpGauge(Hp);
	return DamageAmount;
}

void AIGPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (CheckPlayerState(EPlayerState::Dead))
	{
		return;
	}

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
	AIGHintBase* Hint = Cast<AIGHintBase>(Result.GetActor());

	if (Interactable == nullptr)
	{
		return;
	}
	
	Interactable->Interact();

	if (Crystal != nullptr)
	{
		PlayerInventory->AddCrystal(Crystal);

		// Temporal
		FString CrystalDebugText;
		auto CrystalArray = PlayerInventory->GetCrystalArray();
		for (int i = 0; i < CrystalArray.Num(); i++)
		{
			CrystalDebugText.Append(FString::Printf(TEXT("%d. %s\n"), i + 1, *CrystalArray[i]->GetCrystalName()));
		}
		HudWidget->UpdateCrystalDebug(CrystalDebugText);
	}
	else if(Hint != nullptr)
	{
		PlayerInventory->AddHint(Hint->GetHint());
	}
}

void AIGPlayerCharacter::Attack()
{
	if (CheckPlayerState(EPlayerState::Attacking) || CheckPlayerState(EPlayerState::Rolling) || CheckPlayerState(EPlayerState::Dead))
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

	StaminaValue -= Cost;
	HudWidget->UpdateStaminaGauge(StaminaValue);

	AddPlayerState(EPlayerState::Attacking);
	ElapsedSunMoonAutoConsumptionTime = 0.f;
	AnimInstance->SetEnforced(IsEnforced);
	AnimInstance->StartAttack();

	//데미지 연산뒤 선문게이지 감소
	const float Damage = ComputeDamage();
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("데미지: [%f]"), Damage));
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
	}

	// ---- Temporal (Socket 등으로 위치 조정해줘야함)
	const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
	AIGProjectile* SpawnedActor = GetWorld()->SpawnActor<AIGProjectile>(SpawnLocation, FRotator::ZeroRotator);
	SpawnedActor->Init(Damage, GetActorForwardVector(), 1000.f, 10.f, EProjectileType::SpawnedByPlayer);
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
	if (CheckPlayerState(EPlayerState::Rolling) || CheckPlayerState(EPlayerState::Attacking))
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
	GetCharacterMovement()->MaxWalkSpeed = RollSpeed;
	AnimInstance->StartRoll();
	UGameplayStatics::PlaySound2D(this, TestSoundDataAsset->PlayerRollingSoundCue);
}

void AIGPlayerCharacter::FinishRolling()
{
	GetCharacterMovement()->MaxWalkSpeed = CheckPlayerState(EPlayerState::Running) ? SprintSpeed : WalkSpeed;
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

	// 구르기와 이동상태는 중첩될 수 있으나, 스태미너 계산에는 제외
	if (CheckPlayerState(EPlayerState::Rolling))
	{
		return;
	}

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

void AIGPlayerCharacter::PlayDieSequence()
{
	constexpr float Duration = 1.f;
	ElapsedDieSequenceTime += GWorld->GetDeltaSeconds();

	if (ElapsedDieSequenceTime >= Duration)
	{
		PlayFadeOutSequence();
		return;
	}

	DMI_Grayscale->SetScalarParameterValue("Alpha", FMath::Clamp(ElapsedDieSequenceTime / Duration, 0.f, 1.f));

	GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::PlayDieSequence);
}

void AIGPlayerCharacter::PlayFadeInSequence()
{
	constexpr float Duration = 1.f;
	ElapsedFadeSequenceTime += GWorld->GetDeltaSeconds();

	if (ElapsedFadeSequenceTime >= Duration)
	{
		ElapsedFadeSequenceTime = 0.f;
		return;
	}

	DMI_Fade->SetScalarParameterValue("Alpha", 1 - FMath::Clamp(ElapsedFadeSequenceTime / Duration, 0.f, 1.f));

	GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::PlayFadeInSequence);
}

void AIGPlayerCharacter::PlayFadeOutSequence()
{
	constexpr float Duration = 1.f;
	ElapsedFadeSequenceTime += GWorld->GetDeltaSeconds();

	if (ElapsedFadeSequenceTime >= Duration)
	{
		UGameplayStatics::OpenLevel(this, TEXT("AD_GrayBox"));
		return;
	}

	DMI_Fade->SetScalarParameterValue("Alpha", FMath::Clamp(ElapsedFadeSequenceTime / Duration, 0.f, 1.f));

	GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::PlayFadeOutSequence);
}

float AIGPlayerCharacter::ComputeDamage()
{
	if (CheckPlayerState(EPlayerState::Enforced))
	{
		float DamageScaleFactor = 1.0f;

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

		return DamageScaleFactor * FMath::RandRange(StrongAttackDamageMin, StrongAttackDamageMax);
	}

	return FMath::RandRange(NormalAttackDamageMin, NormalAttackDamageMax);
}

void AIGPlayerCharacter::UpdateShinmyophilScript(const FString InText)
{
	HudWidget->UpdateShinmyophilText(InText);
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
