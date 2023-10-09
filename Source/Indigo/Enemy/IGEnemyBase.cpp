// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGEnemyBase.h"
#include "Indigo/Util/IGSoundDataAsset.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIGEnemyBase::AIGEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SoundDataAsset = LoadObject<UIGSoundDataAsset>(nullptr, TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/SoundCueDataAsset.SoundCueDataAsset'"), nullptr, LOAD_None, nullptr, nullptr);
	
}

// Called when the game starts or when spawned
void AIGEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	MaxHp = 1000;
	Hp = MaxHp;
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

float AIGEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if(bIsEnforcedHit == true)
	{
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->BossAttackDamageArray[FMath::RandRange(0, SoundDataAsset->BossAttackDamageArray.Num() - 1)]);		
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->BossEnforcedDamageArray[FMath::RandRange(0, SoundDataAsset->BossEnforcedDamageArray.Num() - 1)]);		
	}
	
	Hp -= DamageAmount;
	UE_LOG(LogTemp,Log,TEXT("[보스 체력] %f / %f"), Hp, MaxHp);
	return DamageAmount;
}

