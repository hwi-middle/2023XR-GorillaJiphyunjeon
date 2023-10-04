// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGMainLobby.generated.h"

/**
 * 
 */

class UIGMainLobbyWidget;

UCLASS()
class INDIGO_API AIGMainLobby : public AActor
{
GENERATED_BODY()
	
public:
	AIGMainLobby();
	~AIGMainLobby();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIGMainLobbyWidget> MainLobbyWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UIGMainLobbyWidget> MainLobbyWidget;

private:
	
};
