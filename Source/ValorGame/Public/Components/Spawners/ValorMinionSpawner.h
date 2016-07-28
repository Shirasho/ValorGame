// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "Engine/NavigationObjectBase.h"
#include "ValorMinionSpawner.generated.h"

/* The spawner base class for all spawnable minions. It does
 * not extend APlayerStart so it does not interfere with player
 * spawning operations and isn't included in AGameMode::FindPlayerStart
 * and AGameMode::ChoosePlayerStart. */
UCLASS(Abstract, hidecategories = Collision)
class VALORGAME_API AValorMinionSpawner : public ANavigationObjectBase
{

protected:

	GENERATED_UCLASS_BODY()

public:

	/* Used when searching for which ValorMinionSpawner to use. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object)
	FName MinionStartTag;

	/* Which team can spawn at this point. */
	UPROPERTY(EditInstanceOnly, Category = Spawner)
	EValorTeam SpawnTeam;

#if WITH_EDITORONLY_DATA
private:

	class UArrowComponent* ArrowComponent;
#endif

public:

#if WITH_EDITORONLY_DATA
	/* Returns ArrowComponent subobject **/
	class UArrowComponent* GetArrowComponent() const;
#endif

	virtual void SpawnUnit();
};