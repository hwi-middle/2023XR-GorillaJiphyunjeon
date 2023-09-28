// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

/**
 * 
 */

class INDIGO_API FIGDataTableParser
{
public:
	//데이터 테이블만 가져오기
	static UDataTable* LoadAndGetDataTable(const TCHAR* InName, const uint32 InLoadFlags = LOAD_None )
	{
		static TMap<FName, UDataTable*> Cache;

		if(Cache.Contains(InName))
		{
			return Cast<UDataTable>(Cache[InName]);
		}
		
		UDataTable* DataTableFind = LoadObject<UDataTable>(nullptr, InName, nullptr, InLoadFlags, nullptr);
		Cache.Add(InName, DataTableFind);
		return DataTableFind;
	}	

	//데이터 테이블만 가져와서 초기화	
	static void LoadAndInitializeDataTable(const TCHAR* InName, TFunctionRef<void(UDataTable*)> Func, const uint32 InLoadFlags = LOAD_None )
	{
		if(UDataTable* DataTable = LoadAndGetDataTable(InName, InLoadFlags))
		{
			Func(DataTable);
		}
	}

	//데이터 테이블의 하나의 열을 구조체로서 가져오기
	template<class T>
	static T* LoadAndGetDataTableStruct(const TCHAR* InName, const TCHAR* InRowName, const uint32 InLoadFlags = LOAD_None )
	{		
		const UDataTable* DataTableFind = LoadObject<UDataTable>(nullptr, InName, nullptr, InLoadFlags, nullptr);			
		T* RowData = DataTableFind->FindRow<T>(InRowName, FString(""));
		return RowData;	
	}
	
	//데이터 테이블의 하나의 열을 구조체로서 가져와서 초기화
	template<class T>
	static void LoadAndInitializeDataTableStruct(const TCHAR* InName, const TCHAR* InRowName, TFunctionRef<void(T*)> Func, const uint32 InLoadFlags = LOAD_None )
	{
		if(T* DataTableStruct = LoadAndGetDataTableStruct<T>(InName, InRowName, InLoadFlags))
		{
			Func(DataTableStruct);	
		}
	}	
};
