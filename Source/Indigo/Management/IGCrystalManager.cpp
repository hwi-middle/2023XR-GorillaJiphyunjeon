// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGCrystalManager.h"

#include "Indigo/Interface/IGCrystalInterface.h"
#include "Indigo/Inventory/IGPlayerInventory.h"

static TSharedPtr<IGCrystalManager> Instance = MakeShareable(new IGCrystalManager());

IGCrystalManager::IGCrystalManager()
{
	PlayerInventory = nullptr;
}

IGCrystalManager::~IGCrystalManager()
{
	Instance.Reset();	
}

TSharedPtr<IGCrystalManager> IGCrystalManager::GetInstance()
{
	Instance.Reset();
	Instance = MakeShareable(new IGCrystalManager());
	return Instance;
}

void IGCrystalManager::ActivitedCrystal(IIGCrystalInterface* InCrystal)
{
	if(PlayerInventory == nullptr)
	{
		PlayerInventory = new IGPlayerInventory();
	}
	
	PlayerInventory->AddCrystals(InCrystal);
}
