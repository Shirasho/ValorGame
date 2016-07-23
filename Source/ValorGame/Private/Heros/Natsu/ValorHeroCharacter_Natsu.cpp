// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorHeroCharacter_Natsu.h"


AValorHeroCharacter_Natsu::AValorHeroCharacter_Natsu(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AValorHeroCharacter_Natsu::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		/*if (StatInformation.DataTable)
		{
			BaseHealth = StatInformation.GetRow<FValorCharacterStatTableRow>(TEXT("Natsu"))->BaseHealth;
			BaseHealthRegen = StatInformation.GetRow<FValorCharacterStatTableRow>(TEXT("Natsu"))->BaseHealthRegen;
			BasePrimaryResource = StatInformation.GetRow<FValorCharacterStatTableRow>(TEXT("Natsu"))->BasePrimaryResource;
			BasePrimaryResourceRegen = StatInformation.GetRow<FValorCharacterStatTableRow>(TEXT("Natsu"))->BasePrimaryResourceRegen;
			BaseSecondaryResource = StatInformation.GetRow<FValorCharacterStatTableRow>(TEXT("Natsu"))->BaseSecondaryResource;
			BaseSecondaryResourceRegen = StatInformation.GetRow<FValorCharacterStatTableRow>(TEXT("Natsu"))->BaseSecondaryResourceRegen;
			MaxSecondaryResource = StatInformation.GetRow<FValorCharacterStatTableRow>(TEXT("Natsu"))->MaxSecondaryResource;
		}
		else
		{
			VALOR_LOG("A ValorCharacterStatTableRow has not been assigned for character Natsu. Please assign one in the editor.");
		}*/
	}
}

void AValorHeroCharacter_Natsu::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}