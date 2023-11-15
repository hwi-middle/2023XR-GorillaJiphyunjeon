// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/Battle/IGStraightWaveProjectile.h"

#include "NiagaraComponent.h"
#include "Indigo/Util/IGConstructorHelper.h"

AIGStraightWaveProjectile::AIGStraightWaveProjectile()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileVFX"));
	UNiagaraSystem* NiagaraSystem = FIGConstructorHelper::FindAndGetObject<UNiagaraSystem>(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/_GorillaJiphyunjeon/Effect/NS_Boss_Attack_LongRange_Projectile03.NS_Boss_Attack_LongRange_Projectile03'"),
		EAssertionLevel::Check);
	NiagaraComp->SetAsset(NiagaraSystem);
	RootComponent = NiagaraComp;
}
