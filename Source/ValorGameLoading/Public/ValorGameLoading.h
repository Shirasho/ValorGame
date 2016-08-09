// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ModuleInterface.h"

class IValorGameLoadingModule : public IModuleInterface
{

public:

	virtual void StartLoadingScreen() = 0;
};