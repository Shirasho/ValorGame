// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorLocalPlayer.h"

#include "ValorPlayerDefinitions.h"
#include "ValorPersistentUser.h"
#include "ValorGameInstance.h"


UValorPersistentUser* UValorLocalPlayer::GetPersistentUser() const
{
    // If persistent data isn't loaded yet, load it.
    if (!PersistentUser)
    {
        // Since LoadPersistentUser() is not const we need to cast away constness
        // in order to enable caching implementation behavior.
        UValorLocalPlayer* MutableThis = const_cast<UValorLocalPlayer*>(this);
        MutableThis->LoadPersistentUser();
    }
    return PersistentUser;
}

void UValorLocalPlayer::LoadPersistentUser()
{
    // If we changed ControllerId or User we need to load the appropriate persistent user.
    if (PersistentUser && (GetControllerId() != PersistentUser->GetUserIndex() || GetNickname() != PersistentUser->GetName()))
    {
        PersistentUser->SaveIfDirty();
        PersistentUser = nullptr;
    }

    if (!PersistentUser)
    {
        // Use the platform id here to be resilient in the face of controller swapping and similar situations.
        FPlatformUserId PlatformId = GetControllerId();

        IOnlineIdentityPtr IdentityInterface = Online::GetIdentityInterface();
        if (IdentityInterface.IsValid() && GetPreferredUniqueNetId().IsValid())
        {
            PlatformId = IdentityInterface->GetPlatformUserIdFromUniqueNetId(*GetPreferredUniqueNetId());
        }

        PersistentUser = UValorPersistentUser::LoadPersistentUser(GetNickname(), PlatformId);
    }
}

void UValorLocalPlayer::SetControllerId(int32 NewControllerId)
{
    ULocalPlayer::SetControllerId(NewControllerId);

    // if we changed controllerid / user, then we need to load the appropriate persistent user.
    if (PersistentUser && (GetControllerId() != PersistentUser->GetUserIndex() || GetNickname() != PersistentUser->GetName()))
    {
        PersistentUser->SaveIfDirty();
        PersistentUser = nullptr;
    }

    if (!PersistentUser)
    {
        LoadPersistentUser();
    }
}

FString UValorLocalPlayer::GetNickname() const
{
    FString UserNickName = Super::GetNickname();

    if (UserNickName.Len() > VALOR_PLAYER_MAX_NAME_LENGTH)
    {
        UserNickName = UserNickName.Left(VALOR_PLAYER_MAX_NAME_LENGTH) + "...";
    }

    bool bReplace = (UserNickName.Len() == 0);

    // Check for duplicate nicknames...and prevent reentry
    static bool bReentry = false;
    if (!bReentry)
    {
        bReentry = true;
        UValorGameInstance* GameInstance = GetWorld() ? Cast<UValorGameInstance>(GetWorld()->GetGameInstance()) : nullptr;
        if (GameInstance)
        {
            // Check all the names that occur before ours that are the same
            const TArray<ULocalPlayer*>& LocalPlayers = GameInstance->GetLocalPlayers();
            for (int i = 0; i < LocalPlayers.Num(); ++i)
            {
                const ULocalPlayer* LocalPlayer = LocalPlayers[i];
                if (this == LocalPlayer)
                {
                    break;
                }

                if (UserNickName == LocalPlayer->GetNickname())
                {
                    bReplace = true;
                    break;
                }
            }
        }
        bReentry = false;
    }

    if (bReplace)
    {
        UserNickName = FString::Printf(TEXT("Player%i"), GetControllerId() + 1);
    }

    return UserNickName;
}
