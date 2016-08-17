// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

/* Whether to simulate the console UI on PC/Mac/Linux platforms. */
#define VALOR_UI_SIMULATE_CONSOLE_UI    0

#if PLATFORM_WIN
	#include "ValorWindowsUIDefinitions.h"
#elseif PLATFORM_MAC
	#include "ValorMacUIDefinitions.h"
#elseif PLATFORM_LINUX
	#include "ValorLinuxUIDefinitions.h"
#endif

#if VALOR_UI_SIMULATE_CONSOLE_UI
    #define VALOR_UI_CONSOLE_UI 1
#elseif !defined(VALOR_UI_CONSOLE_UI)
	#define VALOR_UI_CONSOLE_UI 0
#else
    #define VALOR_UI_CONSOLE_UI 0
#endif