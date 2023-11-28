// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IGBoss.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Audio/AudioDebug.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/LocalPlayer.h"
#include "Engine/PostProcessVolume.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Indigo/Animation/IGPlayerAnimInstance.h"
#include "Indigo/Animation/IGPlayerWeaponAnimInstance.h"
#include "Indigo/Battle/IGPlayerComboProjectile1.h"
#include "Indigo/Battle/IGPlayerComboProjectile2.h"
#include "Indigo/Battle/IGPlayerComboProjectile3.h"
#include "Indigo/Battle/IGProjectileBase.h"
#include "Indigo/Battle/IGStraightProjectile.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/DataAsset/IGPlayerControlDataAsset.h"
#include "Indigo/DataAsset/IGPlayerDataAsset.h"
#include "Indigo/DataAsset/IGSoundDataAsset.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "Indigo/Interactable/IGMountainCrystal.h"
#include "Indigo/Interactable/IGWaveCrystal.h"
#include "Indigo/Interactable/IGTreeCrystal.h"
#include "Indigo/Interface/Interactable.h"
#include "Indigo/Inventory/IGPlayerInventory.h"
#include "Indigo/UI/IGIngameHUDWidget.h"
#include "Indigo/UI/QuestUI/IGQuest.h"
#include "Indigo/UI/TutorialUI/IGTutotialWidget.h"
#include "Indigo/UI/TutorialUI/IGGIFTutorialWidget.h"
#include "Indigo/Util/IGCharacterDataTable.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "Indigo/Interactable/IGHintBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/AmbientSound.h"

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

	// FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Main/Weapon/SM_Main_Weapon.SM_Main_Weapon'"), [&](USkeletalMesh* MeshRef)
	// {
	// 	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BrushMesh"));
	// 	WeaponMesh->SetSkeletalMesh(MeshRef);
	// 	WeaponMesh->SetWorldLocation(GetMesh()->GetSocketLocation(TEXT("RightHand")));
	// 	WeaponMesh->SetupAttachment(GetMesh());
	// }, EAssertionLevel::Check);
	//
	// const TSubclassOf<UIGPlayerWeaponAnimInstance> WeaponAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGPlayerWeaponAnimInstance>(
	// 	TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Main/Weapon/ABP_PlayerWeapon.ABP_PlayerWeapon_C"), EAssertionLevel::Check);
	// WeaponMesh->SetAnimInstanceClass(WeaponAnimInstanceClass);

	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/PlayerWeapon/Mesh/SM_Weapon.SM_Weapon'"), [&](UStaticMesh* MeshRef)
	{
		WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrushMesh"));
		WeaponMesh->SetStaticMesh(MeshRef);
		WeaponMesh->SetWorldLocation(GetMesh()->GetSocketLocation(TEXT("RightHand")));
		WeaponMesh->SetupAttachment(GetMesh());
	}, EAssertionLevel::Check);

	PlayerControlDataAsset = FIGConstructorHelper::FindAndGetObject<UIGPlayerControlDataAsset>(TEXT("/Script/Indigo.IGPlayerControlDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_PlayerControlData.DA_PlayerControlData'"));
	DefaultMappingContext = PlayerControlDataAsset->DefaultMappingContext;
	MoveAction = PlayerControlDataAsset->MoveAction;
	LookAction = PlayerControlDataAsset->LookAction;
	RunAction = PlayerControlDataAsset->RunAction;
	InteractAction = PlayerControlDataAsset->InteractAction;
	RollAction = PlayerControlDataAsset->RollAction;
	AttackAction = PlayerControlDataAsset->AttackAction;
	Crystal1Action = PlayerControlDataAsset->Crystal1Action;
	Crystal2Action = PlayerControlDataAsset->Crystal2Action;
	Crystal3Action = PlayerControlDataAsset->Crystal3Action;
	ShowTutorialWidget = PlayerControlDataAsset->ShowTutorialWidget;
	UseHealKit = PlayerControlDataAsset->UseHealKit;

	const TSubclassOf<UIGPlayerAnimInstance> PlayerAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGPlayerAnimInstance>(
		TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Main/Animaion/ABP_Player.ABP_Player_C"), EAssertionLevel::Check);
	GetMesh()->SetAnimInstanceClass(PlayerAnimInstanceClass);

	FIGConstructorHelper::FindClassAndInitialize<UIGIngameHUDWidget>(TEXT("/Game/_GorillaJiphyunjeon/UI/Game/WBP_GameHUD.WBP_GameHUD_C"), [&](TSubclassOf<UIGIngameHUDWidget> Class)
	{
		HudWidgetClass = Class;
	}, EAssertionLevel::Check);

	FIGConstructorHelper::FindClassAndInitialize<UIGTutotialWidget>(TEXT("/Game/_GorillaJiphyunjeon/UI/Game/Tutorial/WBP_TutorialWidget.WBP_TutorialWidget_C"), [&](TSubclassOf<UIGTutotialWidget> Class)
	{
		TutorialWidgetClass = Class;
	}, EAssertionLevel::Check);

	FIGConstructorHelper::FindClassAndInitialize<UIGGIFTutorialWidget>(TEXT("/Game/_GorillaJiphyunjeon/UI/Game/Tutorial/WBP_GIFTutorialWidget.WBP_GIFTutorialWidget_C"), [&](TSubclassOf<UIGGIFTutorialWidget> Class)
	{
		GIFTutorialWidgetClass = Class;
	}, EAssertionLevel::Check);
	
	FIGConstructorHelper::FindObjectAndInitialize<UAnimMontage>(TEXT("/Script/Engine.AnimMontage'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Main/Animaion/AM_PlayerAttack.AM_PlayerAttack'"), [&](UAnimMontage* Montage)
	{
		ComboActionMontage = Montage;
	}, EAssertionLevel::Check);

	PlayerInventory = CreateDefaultSubobject<UIGPlayerInventory>(TEXT("Inventory"));
	Shinmyophil = CreateDefaultSubobject<UIGShinmyophil>(TEXT("Shinmyophil"));

	SoundDataAsset = LoadObject<UIGSoundDataAsset>(nullptr, TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_SoundCueData.DA_SoundCueData'"), nullptr, LOAD_None, nullptr, nullptr);
	PlayerDataAsset = FIGConstructorHelper::FindAndGetObject<UIGPlayerDataAsset>(TEXT("/Script/Indigo.IGPlayerDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_PlayerData.DA_PlayerData'"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	
	HealCount = 0;
	bIsFirstGetHealKit = false;
	bIsFirstMeetBoss = false;



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

	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	WalkSpeed = PlayerDataAsset->WalkSpeed;
	SprintSpeed = PlayerDataAsset->SprintSpeed;
	RollSpeed = PlayerDataAsset->RollSpeed;

	ExhaustionPhase1Duration = PlayerDataAsset->ExhaustionPhase1Duration;
	ExhaustionPhase2Duration = PlayerDataAsset->ExhaustionPhase2Duration;
	StaminaRecoveryAmountPerSecondOnIdle = PlayerDataAsset->StaminaRecoveryAmountPerSecondOnIdle;
	StaminaRecoveryAmountPerSecondOnWalk = PlayerDataAsset->StaminaRecoveryAmountPerSecondOnWalk;
	StaminaConsumptionAmountPerSecondOnRunning = PlayerDataAsset->StaminaConsumptionAmountPerSecondOnRunning;
	StaminaConsumptionAmountOnRoll = PlayerDataAsset->StaminaConsumptionAmountOnRoll;
	ActivatedCrystal = ECrystal::None;
	RotateToAimingTargetDuration = 0.2f;

	// TODO: 3타 데미지 적용
	DieZLocation = PlayerDataAsset->DieZLocation;
	ElapsedDieSequenceTime = 0.f;
	ElapsedFadeSequenceTime = 0.f;

	// WeaponAnimInstance = CastChecked<UIGPlayerWeaponAnimInstance>(WeaponMesh->GetAnimInstance());

	PlayerAnimInstance = CastChecked<UIGPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	PlayerAnimInstance->SetSpeed(0.f);
	PlayerAnimInstance->OnFinishRoll.AddUObject(this, &AIGPlayerCharacter::FinishRolling);
	PlayerAnimInstance->OnFinishAttack.AddUObject(this, &AIGPlayerCharacter::NotifyComboActionEnd);
	PlayerAnimInstance->OnShouldGenerateProjectile.AddUObject(this, &AIGPlayerCharacter::GenerateProjectile);
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

		for (int i = 0; i < Shinmyophil->GetQuestArray().Num(); i++)
		{
			HudWidget->InitQuestList(Shinmyophil->GetQuestArray()[i]);
		}
	}

	TutorialWidget = CreateWidget<UIGTutotialWidget>(GetWorld(), TutorialWidgetClass);
	if (TutorialWidget)
	{
		TutorialWidget->AddToViewport();
		TutorialWidget->CloseTutorialWidget();		
	}

	GIFTutorialWidget = CreateWidget<UIGGIFTutorialWidget>(GetWorld(), GIFTutorialWidgetClass);
	if (GIFTutorialWidget)
	{
		GIFTutorialWidget->AddToViewport(10);
		GIFTutorialWidget->CloseGIFTutorialWidget();
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

	SetVillageBGM();

	if(UGameplayStatics::GetCurrentLevelName(GetWorld(),false) == FString("UEDPIE_0_BOSS"))
	{
		TutorialWidget->CloseTutorialWidget();
	}
	else
	{
		TutorialWidget->VisibleTutorialWidget();
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

	// 조준
	int32 ViewportSizeX, ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenCenter(ViewportSizeX / 2.0f, ViewportSizeY / 2.0f);

	FVector WorldLocation;
	PlayerController->DeprojectScreenPositionToWorld(
		ScreenCenter.X,
		ScreenCenter.Y,
		WorldLocation,
		AimingWorldDirection
	);

	AimingStartPoint = WorldLocation;
	AimingEndPoint = WorldLocation + AimingWorldDirection * 3000.0f;

	bIsAimingHit = GetWorld()->LineTraceSingleByChannel(
		AimingHitResult,
		AimingStartPoint,
		AimingEndPoint,
		ECC_PROJECTILE
	);

	if (bIsAimingHit)
	{
		const AActor* HitActor = AimingHitResult.GetActor();
		bIsAimingProperActor = HitActor != nullptr;
	}
	else
	{
		bIsAimingProperActor = false;
	}

	// 애니메이션 관련 처리
	PlayerAnimInstance->SetSpeed(GetVelocity().Size2D());

	// 바닥에 떨어지면 사망
	if (GetActorLocation().Z <= DieZLocation)
	{
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerDeadSoundCue);
		if (!CheckPlayerState(EPlayerState::Dead))
		{
			PlayerAnimInstance->Die();
			HudWidget->UpdateHpGauge(0.f);
			AddPlayerState(EPlayerState::Dead);
			bIsDead = true;
			PlayDieSequence();
		}
		FVector AdjustedLocation = GetActorLocation();
		AdjustedLocation.Z = DieZLocation;
		SetActorLocation(AdjustedLocation);
	}

	// 무기 손에 붙이기
	WeaponMesh->SetWorldLocation(GetMesh()->GetSocketLocation(TEXT("RightHand")));
	WeaponMesh->SetWorldRotation(GetMesh()->GetSocketRotation(TEXT("RightHand")));
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
		EnhancedInputComponent->BindAction(Crystal1Action, ETriggerEvent::Started, this, &AIGPlayerCharacter::ActivateCrystal1);
		EnhancedInputComponent->BindAction(Crystal2Action, ETriggerEvent::Started, this, &AIGPlayerCharacter::ActivateCrystal2);
		EnhancedInputComponent->BindAction(Crystal3Action, ETriggerEvent::Started, this, &AIGPlayerCharacter::ActivateCrystal3);
		EnhancedInputComponent->BindAction(ShowTutorialWidget, ETriggerEvent::Started, this, &AIGPlayerCharacter::TutorialWidgetVisible);
		EnhancedInputComponent->BindAction(UseHealKit, ETriggerEvent::Started, this, &AIGPlayerCharacter::UseHeal);
	}
}

float AIGPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Log, TEXT("플레이어 TakeDamage"));

	AIGBoss* Boss = Cast<AIGBoss>(DamageCauser);
	if (Boss)
	{
		EAttackPattern CurGimmick = Boss->GetCurrentGimmick();
		
		if ((ActivatedCrystal == ECrystal::Mountain && CurGimmick == EAttackPattern::Close) ||
		(ActivatedCrystal == ECrystal::Wave && CurGimmick == EAttackPattern::Far) ||
		(ActivatedCrystal == ECrystal::Tree && CurGimmick == EAttackPattern::Floor)
		)
		{
			return 0.f;
		}
	}


	UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerGetDamageSoundCue);
	Hp -= DamageAmount;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Player HP: [%f]"), Hp));
	if (Hp <= 0)
	{
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerDeadSoundCue);
		PlayerAnimInstance->Die();
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

	AddControllerYawInput(LookAxisVector.X * PlayerDataAsset->MouseYawScale);
	AddControllerPitchInput(LookAxisVector.Y * PlayerDataAsset->MousePitchScale);
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
	// WeaponAnimInstance->SetIsPlayerRunning(IsSprintKeyDown);
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

	if (Interactable == nullptr)
	{
		return;
	}

	Interactable->Interact();

	if (Crystal != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->ObjectGetCrystalSoundCue);
		PlayerInventory->AddCrystal(Crystal->GetCrystalType());
		HudWidget->AddCrystal(Crystal);
	}
}

void AIGPlayerCharacter::Attack()
{
	if (CheckPlayerState(EPlayerState::Rolling) || CheckPlayerState(EPlayerState::Dead))
	{
		return;
	}

	// 스태미너 부족
	const float Cost = 10.f;
	if (StaminaValue < Cost)
	{
		return;
	}

	ProcessComboCommand();
}

void AIGPlayerCharacter::GenerateProjectile()
{
	const float Cost = 10.f;
	StaminaValue -= Cost;
	HudWidget->UpdateStaminaGauge(StaminaValue);

	AddPlayerState(EPlayerState::Attacking);

	const float Damage = ComputeDamage();

	// 타겟 방향으로 회전시키기
	const FVector LookAtTarget = bIsAimingProperActor ? AimingHitResult.ImpactPoint : AimingEndPoint;
	const FVector SpawnDirection = ((bIsAimingProperActor ? AimingHitResult.ImpactPoint : AimingEndPoint) - GetActorLocation()).GetSafeNormal();

	AimingOriginalYaw = GetActorRotation().Yaw;
	AimingTargetYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LookAtTarget).Yaw;
	// 카메라 떨림 현상으로 인해 임시 처리
	const FRotator ActorRot = GetActorRotation();
	SetActorRotation(FRotator(ActorRot.Pitch, AimingTargetYaw, ActorRot.Roll));
	//RotateToAimingTarget();

	//휘두르는 소리
	UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerSwingSoundCue);

	const FVector SpawnLocation = GetActorLocation() + AimingWorldDirection * 100.f;
	AIGStraightProjectile* SpawnedActor = nullptr;
	switch (CurrentCombo)
	{
	case 1:
		SpawnedActor = GetWorld()->SpawnActor<AIGPlayerComboProjectile1>(SpawnLocation, GetActorRotation());
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerAttackCombo1SoundCue);
		break;
	case 2:
		SpawnedActor = GetWorld()->SpawnActor<AIGPlayerComboProjectile2>(SpawnLocation, GetActorRotation());
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerAttackCombo2SoundCue);
		break;
	case 3:
		SpawnedActor = GetWorld()->SpawnActor<AIGPlayerComboProjectile3>(SpawnLocation, GetActorRotation());
		SpawnedActor->SetIsEnforced(true);
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerAttackCombo3SoundCue);
		break;
	default:
		checkNoEntry();
		break;
	}
	SpawnedActor->Init(Damage, SpawnDirection, 3000.f, 10.f, EProjectileSpawnType::SpawnedByPlayer);
	SpawnedActor->OnHitProjectile.AddUObject(this, &AIGPlayerCharacter::OnHitProjectile);

}

void AIGPlayerCharacter::RotateToAimingTarget()
{
	const float DeltaTime = GWorld->DeltaTimeSeconds;
	ElapsedRotateToAimingTargetTime += DeltaTime;
	const float CurrentYaw = FMath::Lerp(AimingOriginalYaw, AimingTargetYaw, ElapsedRotateToAimingTargetTime / RotateToAimingTargetDuration);
	const FRotator ActorRot = GetActorRotation();
	SetActorRotation(FRotator(ActorRot.Pitch, CurrentYaw, ActorRot.Roll));
	UE_LOG(LogTemp, Log, TEXT("회전 (%.3f/%.3f)"), ElapsedRotateToAimingTargetTime, RotateToAimingTargetDuration);
	if (ElapsedRotateToAimingTargetTime >= RotateToAimingTargetDuration)
	{
		//SetActorRotation(FRotator(ActorRot.Pitch, AimingTargetYaw, ActorRot.Roll));
		ElapsedRotateToAimingTargetTime = 0.f;
		return;
	}

	GetWorldTimerManager().SetTimerForNextTick(this, &AIGPlayerCharacter::RotateToAimingTarget);
}

void AIGPlayerCharacter::ProcessComboCommand()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}
}

void AIGPlayerCharacter::ComboActionBegin()
{
	CurrentCombo = 1;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	PlayerAnimInstance->Montage_Play(ComboActionMontage);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AIGPlayerCharacter::ComboActionEnd);
	PlayerAnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void AIGPlayerCharacter::SetComboCheckTimer()
{
	const int32 FrameCount = GetComboAnimationFrameCount();
	constexpr float AnimationFrameRate = 30.f;
	const float ComboDelayTime = FrameCount / AnimationFrameRate;

	if (ComboDelayTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AIGPlayerCharacter::ComboCheck, ComboDelayTime, false);
	}
}

int32 AIGPlayerCharacter::GetComboAnimationFrameCount() const
{
	switch (CurrentCombo)
	{
	case 1:
		return 18;
	case 2:
		return 12;
	case 3:
		return -1;
	default:
		checkNoEntry();
		return -1;
	}
}

void AIGPlayerCharacter::ComboCheck()
{
	ComboTimerHandle.Invalidate();
	if (!HasNextComboCommand)
	{
		return;
	}

	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, 3);
	const FName NextSection = *FString::Printf(TEXT("PlayerAttack%d"), CurrentCombo);
	PlayerAnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
	SetComboCheckTimer();
	HasNextComboCommand = false;
}

void AIGPlayerCharacter::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	CurrentCombo = 0;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	NotifyComboActionEnd();
}

void AIGPlayerCharacter::NotifyComboActionEnd()
{
	CurrentCombo = 0;
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
	PlayerAnimInstance->StartRoll();
	UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerRollSoundCue);
}

void AIGPlayerCharacter::FinishRolling()
{
	GetCharacterMovement()->MaxWalkSpeed = CheckPlayerState(EPlayerState::Running) ? SprintSpeed : WalkSpeed;
	RemovePlayerState(EPlayerState::Rolling);
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
	if (CheckPlayerState(EPlayerState::ExhaustedPhase1))
	{
		return;
	}
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
	if (StaminaValue == 0.0f)
	{
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerLowStaminaSoundCue);
	}
	HudWidget->UpdateStaminaGauge(StaminaValue);
}


void AIGPlayerCharacter::ActivateCrystalByIndex(uint32 Index)
{
	if (CheckPlayerState(EPlayerState::CrystalActivated) || CheckPlayerState(EPlayerState::CrystalCooldown))
	{
		return;
	}

	ECrystal Type = ECrystal::None;
	const TArray<AIGMountainCrystal*> MountainCrystalArray = PlayerInventory->GetMountainCrystalArray();
	const TArray<AIGTreeCrystal*> TreeCrystalArray = PlayerInventory->GetTreeCrystalArray();
	const TArray<AIGWaveCrystal*> WaveCrystalArray = PlayerInventory->GetWaveCrystalArray();

	if (Index == 0 && MountainCrystalArray.Num() >= 3)
	{
		Type = ECrystal::Mountain;
	}
	else if (Index == 1 && TreeCrystalArray.Num() >= 3)
	{
		Type = ECrystal::Tree;
	}
	else if (Index == 2 && WaveCrystalArray.Num() >= 3)
	{
		Type = ECrystal::Wave;
	}
	else
	{
		return;
	}
	UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerCrystalActivitySoundCue);

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
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->PlayerCrystalDisableSoundCue);
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
	HudWidget->MountainCrystalCooltime(1 - ElapsedCrystalCooldownTime / Duration);
	HudWidget->WaveCrystalCooltime(1 - ElapsedCrystalCooldownTime / Duration);
	HudWidget->TreeCrystalCooltime(1 - ElapsedCrystalCooldownTime / Duration);
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

void AIGPlayerCharacter::TutorialWidgetVisible()
{
	if (TutorialWidget)
	{
		if (TutorialWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			TutorialWidget->VisibleTutorialWidget();			
		}
		else if(TutorialWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			TutorialWidget->CloseTutorialWidget();			
		}
	}
}

void AIGPlayerCharacter::UseHeal()
{
	if (HealCount <= 0)
	{
		return;
	}

	HealCount--;
	Hp = FMath::Clamp(Hp + 30.0f, 0, 100.0f);

	if (HudWidget != nullptr)
	{
		HudWidget->SetHealKit(HealCount);
		HudWidget->UpdateHpGauge(Hp);
	}


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

void AIGPlayerCharacter::DisableHUD()
{
	HudWidget->SetVisibility(ESlateVisibility::Hidden);
}

float AIGPlayerCharacter::ComputeDamage()
{
	return 10.f; // TODO: 3타 데미지 적용
}

void AIGPlayerCharacter::UpdateShinmyophilScript(const FString InText)
{
	HudWidget->UpdateShinmyophilText(InText);
}

void AIGPlayerCharacter::AddHealKit()
{
	if(!bIsFirstGetHealKit)
	{
		bIsFirstGetHealKit = true;
		ShowFirstHealKitGIFTutorial();
	}
	HealCount++;
	if (HudWidget != nullptr)
	{
		HudWidget->SetHealKit(HealCount);
	}
}

void AIGPlayerCharacter::SetVillageBGM()
{
		AudioComponent->Stop();
		CurrentBGM = SoundDataAsset->BGMVillageSoundCue;
		AudioComponent = UGameplayStatics::SpawnSound2D(this, CurrentBGM);
		AudioComponent->Play();
}

void AIGPlayerCharacter::SetBossBGM()
{
	AudioComponent->Stop();
	CurrentBGM = SoundDataAsset->BGMBossSoundCue;
	AudioComponent = UGameplayStatics::SpawnSound2D(this, CurrentBGM);
	AudioComponent->Play();
}

void AIGPlayerCharacter::ShowFirstHealKitGIFTutorial()
{
	GIFTutorialWidget->VisibleGIFTutorialWidget();
	GIFTutorialWidget->PreSetByFirstHealKit();
}

void AIGPlayerCharacter::ShowFirstCrystalGIFTutorial()
{
	GIFTutorialWidget->VisibleGIFTutorialWidget();
	GIFTutorialWidget->PreSetByFirstCrystal();
}

void AIGPlayerCharacter::ShowFirstBossGIFTutorial()
{
	if(bIsFirstMeetBoss)
	{
		return;
	}
	
	GIFTutorialWidget->VisibleGIFTutorialWidget();
	GIFTutorialWidget->PreSetByFirstBoss();
	bIsFirstMeetBoss = true;
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

void AIGPlayerCharacter::CheckCrystal_DEBUG()
{
	UE_LOG(LogTemp, Log, TEXT("크리스탈 목록"));

	auto MountainCrystalArray = PlayerInventory->GetMountainCrystalArray();
	auto WaveCrystalArray = PlayerInventory->GetWaveCrystalArray();
	auto TreeCrystalArray = PlayerInventory->GetTreeCrystalArray();

	UE_LOG(LogTemp, Log, TEXT("[산 크리스탈 파편 갯수]: %d"), MountainCrystalArray.Num());
	UE_LOG(LogTemp, Log, TEXT("[물결 크리스탈 파편 갯수]: %d"), WaveCrystalArray.Num());
	UE_LOG(LogTemp, Log, TEXT("[나무 크리스탈 파편 갯수]: %d"), TreeCrystalArray.Num());
}
