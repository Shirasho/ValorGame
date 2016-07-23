// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorLocalPlayer.generated.h"

UCLASS(Config=Engine, Transient)
class UValorLocalPlayer : public ULocalPlayer
{
    GENERATED_BODY()

public:

    /* Sets the player's controller Id to the specified Id. */
    virtual void SetControllerId(int32 NewControllerId) override;

    /* Gets the player's nickname. */
    virtual FString GetNickname() const;

    /* Gets the PersistentUser data. */
    class UValorPersistentUser* GetPersistentUser() const;

    /* Initializes the PersistentUser. */
    void LoadPersistentUser();

private:

    /* The PersistentUser data (the SaveGame). */
    UPROPERTY()
    class UValorPersistentUser* PersistentUser;
};

