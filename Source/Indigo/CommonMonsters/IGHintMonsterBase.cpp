// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGHintMonsterBase.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Interactable/IGHintBase.h"
#include "Indigo/Interactable/IGBlankHint.h"
#include "Indigo/Interactable/IGMainHint.h"
#include "Indigo/Util/IGSoundDataAsset.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIGHintMonsterBase::AIGHintMonsterBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AIGHintMonsterBase::AIGHintMonsterBase(const FString InSectorName)
	:SectorName(InSectorName)
{
	PrimaryActorTick.bCanEverTick = true;
	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleSphere/SM_SampleSphere.SM_SampleSphere'"), [&](UStaticMesh* MeshRef)
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(MeshRef);
	RootComponent = Mesh;
}, EAssertionLevel::Check);

	SoundDataAsset = LoadObject<UIGSoundDataAsset>(nullptr, TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/SoundCueDataAsset.SoundCueDataAsset'"), nullptr, LOAD_None, nullptr, nullptr);
	

}

// Called when the game starts or when spawned
void AIGHintMonsterBase::BeginPlay()
{
	Super::BeginPlay();	

	AIGEnemyBase::SetHp(9);
}

// Called every frame
void AIGHintMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AIGHintMonsterBase::DropHint()
{
	const int8 HintDropPercent = FMath::RandRange(0,1);
	
	if(HintDropPercent == 1)
	{		
		const int8 MainHintDropPercent = FMath::RandRange(0,1);
		
		if(MainHintDropPercent == 1)
		{
			GetWorld()->SpawnActor<AIGMainHint>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("메인 힌트 드랍!")));
		}
		else
		{
			GetWorld()->SpawnActor<AIGBlankHint>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("꽝 힌트 드랍!")));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("힌트 드랍 안됨!")));
	}
	
	Destroy();
}

float AIGHintMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	SetHp(GetHp() - DamageAmount);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("[도깨비불 체력] %f"), GetHp()));
	if(GetHp() <= 0)
	{
		DropHint();
	}

	//피격음!!!!!!!!!!!!!!!
	UGameplayStatics::PlaySound2D(this, SoundDataAsset->WispDamageArray[FMath::RandRange(0, SoundDataAsset->WispDamageArray.Num() - 1)]);
	
	return DamageAmount;
}



