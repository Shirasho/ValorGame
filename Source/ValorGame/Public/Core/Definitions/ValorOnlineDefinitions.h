// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#if PLATFORM_WIN
	#include "ValorWindowsOnlineDefinitions.h"
#elseif PLATFORM_MAC
	#include "ValorMacOnlineDefinitions.h"
#elseif PLATFORM_LINUX
	#include "ValorLinuxOnlineDefinitions.h"
#endif

/* Whether the game requires a license to play. */
#ifndef VALOR_ONLINE_LICENSE_REQUIRED
	#define VALOR_ONLINE_LICENSE_REQUIRED 0
#endif