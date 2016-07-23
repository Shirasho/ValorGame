// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorPersistentUser.generated.h"

UCLASS()
class UValorPersistentUser : public USaveGame
{
    GENERATED_UCLASS_BODY()

public:

    /* Loads user persistence data if it exists, creates an empty record otherwise. */
    static UValorPersistentUser* LoadPersistentUser(FString SlotName, const int32 UserIndex);

    /* Saves data if anything has changed. */
    void SaveIfDirty();

    /* Records the result of a match. */
    void AddMatchResult(uint32 InKills, uint32 InDeaths, uint32 InAssists, EValorGameMode InGameMode, bool bInIsMatchWinner);

	/* Records a leave. */
	void AddLeave(EValorGameMode InGameMode);

    /* Needed because we can recreate the subsystem that stores it. */
    void TellInputAboutKeybindings();

    int32 GetUserIndex() const;

	uint32 GetKills(EValorGameMode ForGameMode) const;

	uint32 GetDeaths(EValorGameMode ForGameMode) const;

	uint32 GetAssists(EValorGameMode ForGameMode) const;

	uint32 GetLeaves(EValorGameMode ForGameMode) const;

	uint32 GetWins(EValorGameMode ForGameMode) const;

	uint32 GetLosses(EValorGameMode ForGameMode) const;

	uint32 GetGames(EValorGameMode ForGameMode) const;

    /** Getter for the gamma correction */
    FORCEINLINE float GetGamma() const
    {
        return Gamma;
    }

    void SetGamma(float InGamma);

    FORCEINLINE int32 GetBotsCount() const
    {
        return BotsCount;
    }

    void SetBotsCount(int32 InCount);

    FORCEINLINE bool IsRecordingDemos() const
    {
        return bIsRecordingDemos;
    }

    void SetIsRecordingDemos(const bool InbIsRecordingDemos);

    FORCEINLINE FString GetName() const
    {
        return SlotName;
    }

protected:

    void SetToDefaults();

    /** Triggers a save of this data. */
    void SavePersistentUser();

    /* Lifetime count of kills. */
    UPROPERTY()
		TMap<EValorGameMode, uint32> Kills;

    /* Lifetime count of deaths. */
    UPROPERTY()
		TMap<EValorGameMode, uint32> Deaths;

    /* Lifetime count of assists. */
    UPROPERTY()
		TMap<EValorGameMode, uint32> Assists;

	/* Lifetime count of leaves. */
	UPROPERTY()
		TMap<EValorGameMode, uint32> Leaves;

    /* Lifetime count of match wins. */
    UPROPERTY()
		TMap<EValorGameMode, uint32> Wins;

    /* Lifetime count of match losses. */
    UPROPERTY()
		TMap<EValorGameMode, uint32> Losses;

	/* Lifetime count of games played. */
	UPROPERTY()
		TMap<EValorGameMode, uint32> GameCount;

    /* How many bots join hosted game */
    UPROPERTY()
        int32 BotsCount;

    /* Recording demos? */
    UPROPERTY()
        bool bIsRecordingDemos;

    /* Holds the gamma correction setting */
    UPROPERTY()
        float Gamma;

private:
    /* True if data is changed but hasn't been saved. */
    bool bIsDirty;

    /* The string identifier used to save/load this persistent user. */
    FString SlotName;
    int32 UserIndex;
};