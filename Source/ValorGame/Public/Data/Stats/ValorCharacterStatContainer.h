// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorDataDefinitions.h"
#include "ValorCharacterStatTableRow.h"
#include "ValorCharacterExperienceTableRow.h"
#include "ValorCharacterStatContainer.generated.h"

USTRUCT(BlueprintType)
struct FValorCharacterStatContainer
{
	GENERATED_USTRUCT_BODY()

private:

	/* Since Visual Studio is a shitty application this needs to be here
	 * in order to make StatInformation work with Intellisence. */
	//float Dummy;

public:

	/* The external data table to read the base stats from. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
		FDataTableRowHandle StatInformation;
	/* The external data table to read the experience from. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
		FDataTableRowHandle ExperienceInformation;

public:

	/* The current health of the character. */
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float Health;
	/* The current primary resource (mana) of the character. */
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float PrimaryResource;
	/* The current secondary resource (character-specific) of the character. */
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float SecondaryResource;
	/* The current health regen of the character. */
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float HealthRegen;
	/* The current health regen of the character. */
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float PrimaryResourceRegen;
	/* The current health regen of the character. */
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float SecondaryResourceRegen;

public:

	/* The base health of the character. */
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BaseHealth;
	/* The base primary resource (mana) of the character. */
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BasePrimaryResource;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BaseSecondaryResource;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BaseHealthRegen;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BasePrimaryResourceRegen;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BaseSecondaryResourceRegen;

public:

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BonusHealth;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BonusPrimaryResource;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BonusSecondaryResource;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BonusHealthRegen;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BonusPrimaryResourceRegen;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BonusSecondaryResourceRegen;

public:

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<int32> ExperienceRequiredPerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> HealthGainPerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> PrimaryResourceGainPerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> SecondaryResourceGainPerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> HealthRegenPerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> PrimaryResourceRegenPerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> SecondaryResourceRegenPerLevel;

public:

	FValorCharacterStatContainer()
		: Health(100)
		, PrimaryResource(0)
		, SecondaryResource(0)
		, BaseHealth(100)
		, BasePrimaryResource(0)
		, BaseSecondaryResource(0)
		, BonusHealth(0)
		, BonusPrimaryResource(0)
		, BonusSecondaryResource(0)
		, BonusHealthRegen(0)
		, BonusPrimaryResourceRegen(0)
		, BonusSecondaryResourceRegen(0)
		, BaseHealthRegen(1)
		, BasePrimaryResourceRegen(1)
		, BaseSecondaryResourceRegen(0)
	{
		/* Only perform check in development builds. */
		checkCode(if (GWorld && GWorld->HasBegunPlay())
		{
			if (StatInformation.DataTable)
			{
				ensure(StatInformation.DataTable->RowStruct->IsChildOf(FValorCharacterStatTableRow::StaticStruct()));
			}
			if (ExperienceInformation.DataTable)
			{
				ensure(ExperienceInformation.DataTable->RowStruct->IsChildOf(FValorCharacterStatTableRow::StaticStruct()));
			}
		});

		ExperienceInformation.RowName = TEXT("Value");
		//if (BaseStatInformation.DataTable && BaseStatInformation.RowName != NAME_None)
		//{
		//	BaseHealth = BaseStatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->BaseHealth;
		//	BaseHealthRegen = BaseStatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->BaseHealthRegen;
		//	BasePrimaryResource = BaseStatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->BasePrimaryResource;
		//	BasePrimaryResourceRegen = BaseStatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->BasePrimaryResourceRegen;
		//	BaseSecondaryResource = BaseStatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->BaseSecondaryResource;
		//	BaseSecondaryResourceRegen = BaseStatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->BaseSecondaryResourceRegen;
		//	//MaxSecondaryResource = BaseStatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->MaxSecondaryResource;
		//}
	}
};