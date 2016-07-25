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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float Health;
	/* The current primary resource (mana) of the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float PrimaryResource;
	/* The current secondary resource (character-specific) of the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float SecondaryResource;
	/* The current health regen of the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float HealthRegen;
	/* The current health regen of the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float PrimaryResourceRegen;
	/* The current health regen of the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float SecondaryResourceRegen;

public:

	/* The base health of the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BaseHealth;
	/* The base primary resource (mana) of the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BasePrimaryResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BaseSecondaryResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BaseHealthRegen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BasePrimaryResourceRegen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BaseSecondaryResourceRegen;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusPrimaryResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusSecondaryResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusHealthRegen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusPrimaryResourceRegen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusSecondaryResourceRegen;

public:

	UPROPERTY()
		TArray<int32> ExperienceRequiredPerLevel;

	UPROPERTY()
		TArray<float> HealthGainPerLevel;

	UPROPERTY()
		TArray<float> PrimaryResourceGainPerLevel;

	UPROPERTY()
		TArray<float> SecondaryResourceGainPerLevel;

	UPROPERTY()
		TArray<float> HealthRegenPerLevel;

	UPROPERTY()
		TArray<float> PrimaryResourceRegenPerLevel;

	UPROPERTY()
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