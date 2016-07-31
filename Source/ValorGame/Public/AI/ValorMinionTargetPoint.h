// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "Engine/TargetPoint.h"
#include "ValorMinionTargetPoint.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AValorMinionTargetPoint : public ATargetPoint
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Pathfinding)
		TArray<AValorMinionTargetPoint*> TeamOneNextTargetPoints;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Pathfinding)
		TArray<AValorMinionTargetPoint*> TeamTwoNextTargetPoints;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Pathfinding)
		TArray<AValorMinionTargetPoint*> TeamThreeNextTargetPoints;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Pathfinding)
		TArray<AValorMinionTargetPoint*> TeamFourNextTargetPoints;

public:

	UFUNCTION(BlueprintPure, Category = Pathfinding)
	void GetTeamOneNextTargetPoints(TArray<AValorMinionTargetPoint*>& OutTeamOneNextTargetPoints) const
	{
		OutTeamOneNextTargetPoints = TeamOneNextTargetPoints;
	}

	UFUNCTION(BlueprintPure, Category = Pathfinding)
	void GetTeamTwoNextTargetPoints(TArray<AValorMinionTargetPoint*>& OutTeamTwoNextTargetPoints) const
	{
		OutTeamTwoNextTargetPoints = TeamTwoNextTargetPoints;
	}

	UFUNCTION(BlueprintPure, Category = Pathfinding)
	void GetTeamThreeNextTargetPoints(TArray<AValorMinionTargetPoint*>& OutTeamThreeNextTargetPoints) const
	{
		OutTeamThreeNextTargetPoints = TeamThreeNextTargetPoints;
	}

	UFUNCTION(BlueprintPure, Category = Pathfinding)
	void GetTeamFourNextTargetPoints(TArray<AValorMinionTargetPoint*>& OutTeamFourNextTargetPoints) const
	{
		OutTeamFourNextTargetPoints = TeamFourNextTargetPoints;
	}


	UFUNCTION(BlueprintPure, Category = Pathfinding)
		AValorMinionTargetPoint* GetTeamOneNextTargetPointRandom() const;

	UFUNCTION(BlueprintPure, Category = Pathfinding)
		AValorMinionTargetPoint* GetTeamTwoNextTargetPointRandom() const;

	UFUNCTION(BlueprintPure, Category = Pathfinding)
		AValorMinionTargetPoint* GetTeamThreeNextTargetPointRandom() const;

	UFUNCTION(BlueprintPure, Category = Pathfinding)
		AValorMinionTargetPoint* GetTeamFourNextTargetPointRandom() const;
};
