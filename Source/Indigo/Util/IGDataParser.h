// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IGDataParser.generated.h"

class IIGCharacterStatus;
struct FIGCharacterDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INDIGO_API UIGDataParser : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIGDataParser();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	//데이터 테이블 초기화
	void InitDataTable(FString InRowName, IIGCharacterStatus* OutStatus);
	
	//캐릭터 데이터 초기화 함수
	void SetCharacterStatusData();

	//캐릭터 데이터테이블 출력 함수
	void PrintCharacterDataTable();

	//동적 데이터 테이블 불러오기
	void DynamicLoadCharacterDataTable();
public:
	//캐릭터 데이터테이블 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterDataTablePath = TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/CharaterDatabase.CharaterDatabase'");
	
private:
	//가져올 열 이름
	FString RowName;
	//가져올 캐릭터 데이터테이블
	FIGCharacterDataTable* IGCharacterDataTable = nullptr;
	//세팅할 캐릭터 인터페이스
	IIGCharacterStatus* CharacterInterface = nullptr;
};
