// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGEnemyBase.h"

// Sets default values
AIGEnemyBase::AIGEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIGEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	Hp = MaxHp;
	Origin = GetActorLocation();
}

// Called every frame
void AIGEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIGEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AIGEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Hp -= DamageAmount;
	UE_LOG(LogTemp, Log, TEXT("[보스 체력] %f / %f"), Hp, MaxHp);
	return DamageAmount;
}
