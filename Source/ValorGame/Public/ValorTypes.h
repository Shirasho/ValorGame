// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

namespace ValorGameState
{
    extern const FName None;
    extern const FName PendingInvite;
    extern const FName WelcomeScreen;
    extern const FName MainMenu;
    extern const FName MessageMenu;
    extern const FName Playing;
}

namespace ValorKeywords
{
    const FString CustomMatchKeyword("Custom");
}

UENUM(BlueprintType)
enum class EValorGameMode : uint8
{
    None = 0,
    Classic
};

UENUM(BlueprintType)
enum class EValorMatchState : uint8
{
    Warmup,
    Playing,
    Won,
    Lost
};

UENUM(BlueprintType)
enum class EValorDialogType : uint8
{
    None,
    Generic,
    ControllerDisconnected
};

UENUM(BlueprintType)
enum class EValorAbilityAimType : uint8
{
    /* No aiming - the spell is cast instantly. */
    Self,

    /* The ability fires freely in the direction of the cursor or click point. */
    Cursor,

    /* The ability only worked when clicking a unit. */
    Target
};

UENUM(BlueprintType, meta = (Bitflags))
enum class EValorTeam : uint8
{
    None,
    One,
    Two,
    Three,
    Four
};
ENUM_CLASS_FLAGS(EValorTeam)