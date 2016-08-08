// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "Engine.h"
#include "ModuleInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(ValorGameEditor, Log, All)

class FValorGameEditorModule : public IModuleInterface
{

public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};