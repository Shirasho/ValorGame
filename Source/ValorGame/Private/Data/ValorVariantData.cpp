// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorVariantData.h"

/**
* Copy constructor. Copies the other into this object
*
* @param Other the other structure to copy
*/
FValorVariantData::FValorVariantData(const FValorVariantData& Other) :
	Type(EValorVariantDataType::Empty)
{
	// Use common methods for doing deep copy or just do a simple shallow copy
	if (Other.Type == EValorVariantDataType::String)
	{
		SetValue(Other.Value.AsTCHAR);
	}
	else if (Other.Type == EValorVariantDataType::Blob)
	{
		SetValue(Other.Value.AsBlob.BlobSize, Other.Value.AsBlob.BlobData);
	}
	else
	{
		// Shallow copy is safe
		FMemory::Memcpy(this, &Other, sizeof(FValorVariantData));
	}
}

/**
* Assignment operator. Copies the other into this object
*
* @param Other the other structure to copy
*/
FValorVariantData& FValorVariantData::operator=(const FValorVariantData& Other)
{
	if (this != &Other)
	{
		// Use common methods for doing deep copy or just do a simple shallow copy
		if (Other.Type == EValorVariantDataType::String)
		{
			SetValue(Other.Value.AsTCHAR);
		}
		else if (Other.Type == EValorVariantDataType::Blob)
		{
			SetValue(Other.Value.AsBlob.BlobSize, Other.Value.AsBlob.BlobData);
		}
		else
		{
			Empty();
			// Shallow copy is safe
			FMemory::Memcpy(this, &Other, sizeof(FValorVariantData));
		}
	}
	return *this;
}

/**
* Copies the data and sets the type
*
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(const TCHAR* InData)
{
	Empty();
	Type = EValorVariantDataType::String;
	if (InData != NULL)
	{
		int32 StrLen = FCString::Strlen(InData);
		// Allocate a buffer for the string plus terminator
		Value.AsTCHAR = new TCHAR[StrLen + 1];
		if (StrLen > 0)
		{
			// Copy the data
			FCString::Strcpy(Value.AsTCHAR, StrLen + 1, InData);
		}
		else
		{
			Value.AsTCHAR[0] = TEXT('\0');
		}
	}
}

/**
* Copies the data and sets the type
*
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(const FString& InData)
{
	SetValue(*InData);
}

/**
* Copies the data and sets the type
*
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(int32 InData)
{
	Empty();
	Type = EValorVariantDataType::Int32;
	Value.AsInt = InData;
}

/**
* Copies the data and sets the type
*
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(uint32 InData)
{
	Empty();
	Type = EValorVariantDataType::UInt32;
	Value.AsUInt = InData;
}

/**
* Copies the data and sets the type
*
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(bool InData)
{
	Empty();
	Type = EValorVariantDataType::Bool;
	Value.AsBool = InData;
}

/**
* Copies the data and sets the type
*
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(double InData)
{
	Empty();
	Type = EValorVariantDataType::Double;
	Value.AsDouble = InData;
}

/**
* Copies the data and sets the type
*
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(float InData)
{
	Empty();
	Type = EValorVariantDataType::Float;
	Value.AsFloat = InData;
}

/**
* Copies the data and sets the type
*
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(const TArray<uint8>& InData)
{
	SetValue((uint32)InData.Num(), (const uint8*)InData.GetData());
}

/**
* Copies the data and sets the type
*
* @param Size the length of the buffer to copy
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(uint32 Size, const uint8* InData)
{
	Empty();
	Type = EValorVariantDataType::Blob;
	if (Size > 0)
	{
		// Deep copy the binary data
		Value.AsBlob.BlobSize = Size;
		Value.AsBlob.BlobData = new uint8[Size];
		FMemory::Memcpy(Value.AsBlob.BlobData, InData, Size);
	}
}

/**
* Copies the data and sets the type
*
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(int64 InData)
{
	Empty();
	Type = EValorVariantDataType::Int64;
	Value.AsInt64 = InData;
}

/**
* Copies the data and sets the type
*
* @param InData the new data to assign
*/
void FValorVariantData::SetValue(uint64 InData)
{
	Empty();
	Type = EValorVariantDataType::UInt64;
	Value.AsUInt64 = InData;
}

/**
* Copies the data after verifying the type
*
* @param OutData out value that receives the copied data
*/
void FValorVariantData::GetValue(FString& OutData) const
{
	if (Type == EValorVariantDataType::String && Value.AsTCHAR != NULL)
	{
		OutData = Value.AsTCHAR;
	}
	else
	{
		OutData = TEXT("");
	}
}

/**
* Copies the data after verifying the type
*
* @param OutData out value that receives the copied data
*/
void FValorVariantData::GetValue(int32& OutData) const
{
	if (Type == EValorVariantDataType::Int32)
	{
		OutData = Value.AsInt;
	}
	else
	{
		OutData = 0;
	}
}

/**
* Copies the data after verifying the type
*
* @param OutData out value that receives the copied data
*/
void FValorVariantData::GetValue(uint32& OutData) const
{
	if (Type == EValorVariantDataType::UInt32)
	{
		OutData = Value.AsUInt;
	}
	else
	{
		OutData = 0;
	}
}

/**
* Copies the data after verifying the type
*
* @param OutData out value that receives the copied data
*/
void FValorVariantData::GetValue(bool& OutData) const
{
	if (Type == EValorVariantDataType::Bool)
	{
		OutData = Value.AsBool;
	}
	else
	{
		OutData = false;
	}
}

/**
* Copies the data after verifying the type
*
* @param OutData out value that receives the copied data
*/
void FValorVariantData::GetValue(int64& OutData) const
{
	if (Type == EValorVariantDataType::Int64)
	{
		OutData = Value.AsInt64;
	}
	else
	{
		OutData = 0;
	}
}

/**
* Copies the data after verifying the type
*
* @param OutData out value that receives the copied data
*/
void FValorVariantData::GetValue(uint64& OutData) const
{
	if (Type == EValorVariantDataType::UInt64)
	{
		OutData = Value.AsUInt64;
	}
	else
	{
		OutData = 0;
	}
}

/**
* Copies the data after verifying the type
*
* @param OutData out value that receives the copied data
*/
void FValorVariantData::GetValue(float& OutData) const
{
	if (Type == EValorVariantDataType::Float)
	{
		OutData = Value.AsFloat;
	}
	else
	{
		OutData = 0.f;
	}
}

/**
* Copies the data after verifying the type
* NOTE: Performs a deep copy so you are responsible for freeing the data
*
* @param OutSize out value that receives the size of the copied data
* @param OutData out value that receives the copied data
*/
void FValorVariantData::GetValue(uint32& OutSize, uint8** OutData) const
{
	if (Type == EValorVariantDataType::Blob)
	{
		OutSize = Value.AsBlob.BlobSize;
		// Need to perform a deep copy
		*OutData = new uint8[OutSize];
		FMemory::Memcpy(*OutData, Value.AsBlob.BlobData, OutSize);
	}
	else
	{
		OutSize = 0;
		*OutData = NULL;
	}
}

/**
* Copies the data after verifying the type
*
* @param OutData out value that receives the copied data
*/
void FValorVariantData::GetValue(TArray<uint8>& OutData) const
{
	if (Type == EValorVariantDataType::Blob)
	{
		// Presize the array so it only allocates what's needed
		OutData.Empty(Value.AsBlob.BlobSize);
		OutData.AddUninitialized(Value.AsBlob.BlobSize);
		// Copy into the array
		FMemory::Memcpy(OutData.GetData(), Value.AsBlob.BlobData, Value.AsBlob.BlobSize);
	}
	else
	{
		OutData.Empty();
	}
}

/**
* Copies the data after verifying the type
*
* @param OutData out value that receives the copied data
*/
void FValorVariantData::GetValue(double& OutData) const
{
	if (Type == EValorVariantDataType::Double)
	{
		OutData = Value.AsDouble;
	}
	else
	{
		OutData = 0.0;
	}
}

/**
* Cleans up the existing data and sets the type to EValorVariantDataType::Empty
*/
void FValorVariantData::Empty()
{
	// Be sure to delete deep allocations
	switch (Type)
	{
		case EValorVariantDataType::String:
			delete[] Value.AsTCHAR;
			break;
		case EValorVariantDataType::Blob:
			delete[] Value.AsBlob.BlobData;
			break;
	}

	Type = EValorVariantDataType::Empty;

	FMemory::Memset(&Value, 0, sizeof(ValueUnion));
}

/**
* Comparison of two settings data classes
*
* @param Other the other settings data to compare against
*
* @return true if they are equal, false otherwise
*/
bool FValorVariantData::operator==(const FValorVariantData& Other) const
{
	if (Type == Other.Type)
	{
		switch (Type)
		{
			case EValorVariantDataType::Float:
			{
				return Value.AsFloat == Other.Value.AsFloat;
			}
			case EValorVariantDataType::Int32:
			{
				return Value.AsInt == Other.Value.AsInt;
			}
			case EValorVariantDataType::UInt32:
			{
				return Value.AsUInt == Other.Value.AsUInt;
			}
			case EValorVariantDataType::Int64:
			{
				return Value.AsInt64 == Other.Value.AsInt64;
			}
			case EValorVariantDataType::UInt64:
			{
				return Value.AsInt64 == Other.Value.AsUInt64;
			}
			case EValorVariantDataType::Double:
			{
				return Value.AsDouble == Other.Value.AsDouble;
			}
			case EValorVariantDataType::String:
			{
				return FCString::Strcmp(Value.AsTCHAR, Other.Value.AsTCHAR) == 0;
			}
			case EValorVariantDataType::Blob:
			{
				return (Value.AsBlob.BlobSize == Other.Value.AsBlob.BlobSize) &&
					(FMemory::Memcmp(Value.AsBlob.BlobData, Other.Value.AsBlob.BlobData, Value.AsBlob.BlobSize) == 0);
			}
			case EValorVariantDataType::Bool:
			{
				return Value.AsBool == Other.Value.AsBool;
			}
		}
	}
	return false;
}
bool FValorVariantData::operator!=(const FValorVariantData& Other) const
{
	return !(operator==(Other));
}