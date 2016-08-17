// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#ifdef PLATFORM_CONSOLE
    // This is defined in Platform.h but is deprecated. We still want to have it defined.
    #undef PLATFORM_CONSOLE
    /* Whether the platform is a console platform. */
    #define PLATFORM_CONSOLE PLATFORM_XBOXONE || PLATFORM_PS4
#endif

#ifndef PLATFORM_MOBILE
    /* Wether the platform is a console platform. */
    #define PLATFORM_MOBILE PLATFORM_IOS || PLATFORM_ANDROID || PLATFORM_WINRT || PLATFORM_WINRT_ARM
#endif

#ifndef PLATFORM_WEB
    /* Whether the platform a is a web platform. */
    #define PLATFORM_WEB PLATFORM_HTML5
#endif

#if PLATFORM_WIN
	#include "ValorWindowsPlatformDefinitions.h"
#elseif PLATFORM_MAC
	#include "ValorMacPlatformDefinitions.h"
#elseif PLATFORM_LINUX
	#include "ValorLinuxPlatformDefinitions.h"
#endif