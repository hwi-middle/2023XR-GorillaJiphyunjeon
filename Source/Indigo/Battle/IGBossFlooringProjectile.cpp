// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBossFlooringProjectile.h"

#include "NiagaraComponent.h"
#include "Indigo/Util/IGConstructorHelper.h"

AIGBossFlooringProjectile::AIGBossFlooringProjectile()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileVFX"));
	UNiagaraSystem* NiagaraSystem = FIGConstructorHelper::FindAndGetObject<UNiagaraSystem>(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/_GorillaJiphyunjeon/Effect/NS_Boss_Attack_FlooringRange_Projectile01.NS_Boss_Attack_FlooringRange_Projectile01'"),
		EAssertionLevel::Check);
	NiagaraComp->SetAsset(NiagaraSystem);
	RootComponent = NiagaraComp;
}
