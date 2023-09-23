// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IGCharacterDataParser.generated.h"

class IIGCharacterStatus;
struct FIGCharacterDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INDIGO_API UIGCharacterDataParser : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIGCharacterDataParser();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	//데이터 테이블 초기화
	void InitDataTable(FString InRowName, IIGCharacterStatus* InStatus);
	
	//캐릭터 데이터 초기화 함수
	void SetCharacterStatusData();

	//캐릭터 데이터테이블 출력 함수
	void PrintCharacterDataTable();

	//동적 데이터 테이블 불러오기
	void DynamicLoadCharacterDataTable();

	FORCEINLINE void SetCharacterDataTablePath(const FString InPath) { CharacterDataTablePath = InPath; }
	
public:
	//캐릭터 데이터테이블 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterDataTablePath;

	
	
private:

	//가져올 캐릭터 데이터테이블
	FIGCharacterDataTable* IGCharacterDataTable = nullptr;
	//세팅할 캐릭터 인터페이스
	IIGCharacterStatus* CharacterInterface = nullptr;
};
