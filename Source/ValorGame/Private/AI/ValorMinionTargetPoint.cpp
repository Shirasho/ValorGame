// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorMinionTargetPoint.h"


AValorMinionTargetPoint* AValorMinionTargetPoint::GetTeamOneNextTargetPointRandom() const
{
	return TeamOneNextTargetPoints.Num() > 0 ? TeamOneNextTargetPoints[FMath::RandHelper(TeamOneNextTargetPoints.Num())] : nullptr;
}

AValorMinionTargetPoint* AValorMinionTargetPoint::GetTeamTwoNextTargetPointRandom() const
{
	return TeamTwoNextTargetPoints.Num() > 0 ? TeamTwoNextTargetPoints[FMath::RandHelper(TeamTwoNextTargetPoints.Num())] : nullptr;
}

AValorMinionTargetPoint* AValorMinionTargetPoint::GetTeamThreeNextTargetPointRandom() const
{
	return TeamThreeNextTargetPoints.Num() > 0 ? TeamThreeNextTargetPoints[FMath::RandHelper(TeamThreeNextTargetPoints.Num())] : nullptr;
}

AValorMinionTargetPoint* AValorMinionTargetPoint::GetTeamFourNextTargetPointRandom() const
{
	return TeamFourNextTargetPoints.Num() > 0 ? TeamFourNextTargetPoints[FMath::RandHelper(TeamFourNextTargetPoints.Num())] : nullptr;
}