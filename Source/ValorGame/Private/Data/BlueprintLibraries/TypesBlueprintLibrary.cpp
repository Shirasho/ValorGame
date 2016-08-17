// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "TypesBlueprintLibrary.h"

bool UTypesBlueprintLibrary::K2_StringToFloatArray(const TArray<FString>& InData, TArray<float>& OutData, int32 StartIndex)
{
	bool bSuccess = true;

	check(InData.IsValidIndex(StartIndex));
	for (int32 Value = StartIndex; Value < InData.Num(); ++Value)
	{
		if (ensureMsgf(InData[Value].IsNumeric(), TEXT("Invalid float found in string array. Invalid value - '%s'."), *(InData[Value])))
		{
			OutData.Add(FCString::Atof(*(InData[Value])));
		}
		else
		{
			bSuccess = false;
		}
	}

	return bSuccess;
}

bool UTypesBlueprintLibrary::K2_StringToUint8Array(const TArray<FString>& InData, TArray<uint8>& OutData, int32 StartIndex)
{
	bool bSuccess = true;

	check(InData.IsValidIndex(StartIndex));
	for (int32 Value = StartIndex; Value < InData.Num(); ++Value)
	{
		if (ensureMsgf(InData[Value].IsNumeric(), TEXT("Invalid uint8 found in string array. Invalid value - '%s'."), *(InData[Value])))
		{
			int32 Result = FCString::Atoi(*(InData[Value]));
			if (ensureMsgf(Result >= 0 && Result <= UINT8_MAX, TEXT("Cannot convert to uint8. The int value is either less than 0 or larger than %d. Provided value: "), UINT8_MAX, Result))
			{
				OutData.Add((uint8)Result);
			}
			else
			{
				bSuccess = false;
			}
		}
	}

	return bSuccess;
}

bool UTypesBlueprintLibrary::K2_StringToInt32Array(const TArray<FString>& InData, TArray<int32>& OutData, int32 StartIndex)
{
	bool bSuccess = true;

	check(InData.IsValidIndex(StartIndex));
	for (int32 Value = StartIndex; Value < InData.Num(); ++Value)
	{
		if (ensureMsgf(InData[Value].IsNumeric(), TEXT("Invalid int32 found in string array. Invalid value - '%s'."), *(InData[Value])))
		{
			OutData.Add(FCString::Atoi(*(InData[Value])));
		}
		else
		{
			bSuccess = false;
		}
	}

	return bSuccess;
}