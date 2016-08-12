// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

namespace EValorVariantDataType
{
	enum Type
	{
		/** Means the data should be ignored */
		Empty,
		/** 32 bit integer */
		Int32,
		/** 32 bit unsigned integer */
		UInt32,
		/** 64 bit integer */
		Int64,
		/** 64 bit unsigned integer */
		UInt64,
		/** Double (8 byte) */
		Double,
		/** Unicode string */
		String,
		/** Float (4 byte) */
		Float,
		/** Binary data */
		Blob,
		/** bool data (1 byte) */
		Bool,
		MAX
	};
}

class FValorVariantData
{

private:

	/** Current data type */
	EValorVariantDataType::Type Type;
	/** Union of all possible types that can be stored */
	union ValueUnion
	{
		bool AsBool;
		int32 AsInt;
		uint32 AsUInt;
		float AsFloat;
		int64 AsInt64;
		uint64 AsUInt64;
		double AsDouble;
		TCHAR* AsTCHAR;
		struct
		{
			uint8* BlobData;
			uint32 BlobSize;
		} AsBlob;

		ValueUnion() { FMemory::Memset(this, 0, sizeof(ValueUnion)); }
	} Value;

public:

	/** Constructor */
	FValorVariantData() :
		Type(EValorVariantDataType::Empty)
	{
	}

	/** Constructor starting with an initialized value/type */
	template<typename ValueType>
	FValorVariantData(const ValueType& InData) :
		Type(EValorVariantDataType::Empty)
	{
		SetValue(InData);
	}

	/**
	* Copy constructor. Copies the other into this object
	*
	* @param Other the other structure to copy
	*/
	FValorVariantData(const FValorVariantData& Other);

	/**
	* Assignment operator. Copies the other into this object
	*
	* @param Other the other structure to copy
	*/
	FValorVariantData& operator=(const FValorVariantData& Other);

	/**
	* Cleans up the data to prevent leaks
	*/
	~FValorVariantData()
	{
		Empty();
	}

	/**
	* Cleans up the existing data and sets the type to ODT_Empty
	*/
	void Empty();

	/**
	*	Get the key for this key value pair
	*/
	const EValorVariantDataType::Type GetType() const
	{
		return Type;
	}

	/**
	* Copies the data and sets the type
	*
	* @param InData the new data to assign
	*/
	void SetValue(const FString& InData);

	/**
	* Copies the data and sets the type
	*
	* @param InData the new data to assign
	*/
	void SetValue(const TCHAR* InData);

	/**
	* Copies the data and sets the type
	*
	* @param InData the new data to assign
	*/
	void SetValue(int32 InData);

	/**
	* Copies the data and sets the type
	*
	* @param InData the new data to assign
	*/
	void SetValue(uint32 InData);

	/**
	* Copies the data and sets the type
	*
	* @param InData the new data to assign
	*/
	void SetValue(bool InData);

	/**
	* Copies the data and sets the type
	*
	* @param InData the new data to assign
	*/
	void SetValue(double InData);

	/**
	* Copies the data and sets the type
	*
	* @param InData the new data to assign
	*/
	void SetValue(float InData);

	/**
	* Copies the data and sets the type
	*
	* @param InData the new data to assign
	*/
	void SetValue(const TArray<uint8>& InData);

	/**
	* Copies the data and sets the type
	*
	* @param Size the length of the buffer to copy
	* @param InData the new data to assign
	*/
	void SetValue(uint32 Size, const uint8* InData);

	/**
	* Copies the data and sets the type
	*
	* @param InData the new data to assign
	*/
	void SetValue(int64 InData);

	/**
	* Copies the data and sets the type
	*
	* @param InData the new data to assign
	*/
	void SetValue(uint64 InData);

	/**
	* Copies the data after verifying the type
	*
	* @param OutData out value that receives the copied data
	*/
	void GetValue(FString& OutData) const;

	/**
	* Copies the data after verifying the type
	*
	* @param OutData out value that receives the copied data
	*/
	void GetValue(int32& OutData) const;

	/**
	* Copies the data after verifying the type
	*
	* @param OutData out value that receives the copied data
	*/
	void GetValue(uint32& OutData) const;

	/**
	* Copies the data after verifying the type
	*
	* @param OutData out value that receives the copied data
	*/
	void GetValue(bool& OutData) const;

	/**
	Copies the data after verifying the type
	*
	* @param OutData out value that receives the copied data
	*/
	void GetValue(int64& OutData) const;

	/**
	Copies the data after verifying the type
	*
	* @param OutData out value that receives the copied data
	*/
	void GetValue(uint64& OutData) const;

	/**
	* Copies the data after verifying the type
	*
	* @param OutData out value that receives the copied data
	*/
	void GetValue(float& OutData) const;

	/**
	* Copies the data after verifying the type
	*
	* @param OutData out value that receives the copied data
	*/
	void GetValue(TArray<uint8>& OutData) const;

	/**
	* Copies the data after verifying the type.
	* NOTE: Performs a deep copy so you are responsible for freeing the data
	*
	* @param OutSize out value that receives the size of the copied data
	* @param OutData out value that receives the copied data
	*/
	void GetValue(uint32& OutSize, uint8** OutData) const;

	/**
	* Copies the data after verifying the type
	*
	* @param OutData out value that receives the copied data
	*/
	void GetValue(double& OutData) const;

	/**
	* Increments the value by the specified amount
	*
	* @param IncBy the amount to increment by
	*/
	template<typename TYPE, EValorVariantDataType::Type ENUM_TYPE>
	FORCEINLINE void Increment(TYPE IncBy)
	{
		checkSlow(Type == EValorVariantDataType::Int32 || Type == EValorVariantDataType::Int64 ||
			Type == EValorVariantDataType::UInt32 || Type == EValorVariantDataType::UInt64 ||
			Type == EValorVariantDataType::Float || Type == EValorVariantDataType::Double);
		if (Type == ENUM_TYPE)
		{
			*(TYPE*)&Value += IncBy;
		}
	}

	/**
	* Decrements the value by the specified amount
	*
	* @param DecBy the amount to decrement by
	*/
	template<typename TYPE, EValorVariantDataType::Type ENUM_TYPE>
	FORCEINLINE void Decrement(TYPE DecBy)
	{
		checkSlow(Type == EValorVariantDataType::Int32 || Type == EValorVariantDataType::Int64 ||
			Type == EValorVariantDataType::UInt32 || Type == EValorVariantDataType::UInt64 ||
			Type == EValorVariantDataType::Float || Type == EValorVariantDataType::Double);
		if (Type == ENUM_TYPE)
		{
			*(TYPE*)&Value -= DecBy;
		}
	}

	/**
	* Comparison of two settings data classes
	*
	* @param Other the other settings data to compare against
	*
	* @return true if they are equal, false otherwise
	*/
	bool operator==(const FValorVariantData& Other) const;
	bool operator!=(const FValorVariantData& Other) const;
};