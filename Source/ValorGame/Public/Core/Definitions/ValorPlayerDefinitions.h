// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#if PLATFORM_WIN
	#include "ValorWindowsPlayerDefinitions.h"
#elseif PLATFORM_MAC
	#include "ValorMacPlayerDefinitions.h"
#elseif PLATFORM_LINUX
	#include "ValorLinuxPlayerDefinitions.h"
#endif

#ifndef VALOR_PLAYER_MAX_NAME_LENGTH
	/* The maximum number of characters to display on the UI before it gets cut off. */
	#define VALOR_PLAYER_MAX_NAME_LENGTH    16
#endif