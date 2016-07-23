// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorPersistentUser.h"

#include "ValorLocalPlayer.h"

UValorPersistentUser::UValorPersistentUser(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SetToDefaults();
}

void UValorPersistentUser::SetToDefaults()
{
    bIsDirty = false;

    Gamma = 2.2f;
    BotsCount = 1;
    bIsRecordingDemos = false;
}

void UValorPersistentUser::SavePersistentUser()
{
    UGameplayStatics::SaveGameToSlot(this, SlotName, UserIndex);
    bIsDirty = false;
}

int32 UValorPersistentUser::GetUserIndex() const
{
	return UserIndex;
}

uint32 UValorPersistentUser::GetKills(EValorGameMode ForGameMode) const
{
	return Kills.FindRef(ForGameMode);
}

uint32 UValorPersistentUser::GetDeaths(EValorGameMode ForGameMode) const
{
	return Deaths.FindRef(ForGameMode);
}

uint32 UValorPersistentUser::GetAssists(EValorGameMode ForGameMode) const
{
	return Assists.FindRef(ForGameMode);
}

uint32 UValorPersistentUser::GetLeaves(EValorGameMode ForGameMode) const
{
	return Leaves.FindRef(ForGameMode);
}

uint32 UValorPersistentUser::GetWins(EValorGameMode ForGameMode) const
{
	return Wins.FindRef(ForGameMode);
}

uint32 UValorPersistentUser::GetLosses(EValorGameMode ForGameMode) const
{
	return Losses.FindRef(ForGameMode);
}

uint32 UValorPersistentUser::GetGames(EValorGameMode ForGameMode) const
{
	return GameCount.FindRef(ForGameMode);
}


UValorPersistentUser* UValorPersistentUser::LoadPersistentUser(FString SlotName, const int32 UserIndex)
{
    UValorPersistentUser* Result = nullptr;

    if (SlotName.Len() > 0)
    {
        Result = Cast<UValorPersistentUser>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
        if (!Result)
        {
            Result = Cast<UValorPersistentUser>(UGameplayStatics::CreateSaveGameObject(UValorPersistentUser::StaticClass()));
        }

        check(Result);

        Result->SlotName = SlotName;
        Result->UserIndex = UserIndex;
    }

    return Result;
}

void UValorPersistentUser::SaveIfDirty()
{
    if (bIsDirty)
    {
        SavePersistentUser();
    }
}

void UValorPersistentUser::AddMatchResult(uint32 InKills, uint32 InDeaths, uint32 InAssists, EValorGameMode InGameMode, bool bInIsMatchWinner)
{
	// Update the number of games played.
	++(GameCount.FindOrAdd(InGameMode));

	// Update the number of games won/lost.
	if (bInIsMatchWinner)
	{
		++(Wins.FindOrAdd(InGameMode));
	}
	else
	{
		++(Losses.FindOrAdd(InGameMode));
	}

	// Update kills.
	Kills.FindOrAdd(InGameMode) += InKills;

	// Update deaths.
	Deaths.FindOrAdd(InGameMode) += InDeaths;

	// Update Assists.
	Assists.FindOrAdd(InGameMode) += InAssists;

    bIsDirty = true;
}

void UValorPersistentUser::AddLeave(EValorGameMode InGameMode)
{
	// Update the number of games played.
	++(GameCount.FindOrAdd(InGameMode));

	// Update the number of games left.
	++(Leaves.FindOrAdd(InGameMode));

	bIsDirty = true;
}

void UValorPersistentUser::TellInputAboutKeybindings()
{
	TArray<APlayerController*> PlayerList;
	if (GEngine)
	{
		GEngine->GetAllLocalPlayerControllers(PlayerList);
	}

	for (APlayerController* Controller : PlayerList)
	{
		if (!Controller || !Controller->Player || !Controller->PlayerInput)
		{
			continue;
		}

		// Update key bindings for current user only.
		UValorLocalPlayer* LocalPlayer = Cast<UValorLocalPlayer>(Controller->Player);
		if (!LocalPlayer || LocalPlayer->GetPersistentUser() != this)
		{
			continue;
		}

		// Update bindings.
		/*int32 AxisMapCount = Controller->PlayerInput->AxisMappings.Num();
		for (int32 AxisMapIndex = 0; AxisMapIndex < AxisMapCount; ++AxisMapIndex)
		{
		FInputAxisKeyMapping& AxisMapping = PC->PlayerInput->AxisMappings[AxisMapIndex];
		if (AxisMapping.AxisName == "")
		{
		AxisMapping.Scale = 1;
		}
		}
		Controller->PlayerInput->ForceRebuildingKeyMaps();*/
	}
}