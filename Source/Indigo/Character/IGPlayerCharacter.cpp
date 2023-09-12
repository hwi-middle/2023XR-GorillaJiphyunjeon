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
#include "Indigo/Util/IGConstructorHelper.h"

AIGPlayerCharacter::AIGPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
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

	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/SampleCharacter/SKM_Manny.SKM_Manny'"), [&](USkeletalMesh* SkeletalMesh)
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh);
		// Temporal
		GetMesh()->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	}, EAssertionLevel::Check);


	DefaultMappingContext = FIGConstructorHelper::FindAndGetObject<UInputMappingContext>(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/_GorillaJiphyunjeon/Input/IMC_Default.IMC_Default'"));
	JumpAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Jump.IA_Jump'"));
	MoveAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Move.IA_Move'"));
	LookAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Look.IA_Look'"));
	RunAction = FIGConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/_GorillaJiphyunjeon/Input/Actions/IA_Run.IA_Run'"));
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
}

void AIGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AIGPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AIGPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AIGPlayerCharacter::SetIsRunning);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AIGPlayerCharacter::SetIsRunning);
	}
}

void AIGPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller == nullptr)
	{
		return;
	}
	
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
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
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	SetActorRelativeRotation(YawRotation);
}

void AIGPlayerCharacter::SetIsRunning(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Sprint"));
		GetCharacterMovement()->MaxWalkSpeed = 1500.f;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Walk"));
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}
}
