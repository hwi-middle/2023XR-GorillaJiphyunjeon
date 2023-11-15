// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/Battle/IGWispMountainAttackStone.h"

#include "NiagaraComponent.h"
#include "Indigo/Util/IGConstructorHelper.h"

// Sets default values
AIGWispMountainAttackStone::AIGWispMountainAttackStone()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileVFX"));
	UNiagaraSystem* NiagaraSystem = FIGConstructorHelper::FindAndGetObject<UNiagaraSystem>(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/_GorillaJiphyunjeon/Effect/NS_Wisp_Attack_CloseRange_Rock.NS_Wisp_Attack_CloseRange_Rock'"),
		EAssertionLevel::Check);
	NiagaraComp->SetAsset(NiagaraSystem);
	NiagaraComp->SetupAttachment(Mesh);
	Mesh->SetVisibility(false);
}


