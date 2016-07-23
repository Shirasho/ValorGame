// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

/* Whether to simulate the console UI on PC/Mac/Linux platforms. */
#define VALOR_UI_SIMULATE_CONSOLE_UI    0

#if PLATFORM_CONSOLE || VALOR_UI_SIMULATE_CONSOLE_UI
    #define VALOR_UI_CONSOLE_UI 1
#else
    #define VALOR_UI_CONSOLE_UI 0
#endif