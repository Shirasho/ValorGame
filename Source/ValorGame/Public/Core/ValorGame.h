// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "Engine.h"				        // Core Engine

#include "Online.h"                     // Online subsystem
#include "Net/UnrealNetwork.h"	        // Replication

#include "ValorTypes.h"		            // Commonly-used types
#include "ValorStats.h"					// Stats

#include "ParticleDefinitions.h"        // Particle systems
#include "SoundDefinitions.h"           // Sound systems

#include "ValorPlatformDefinitions.h"   // Platform definitions
#include "ValorOnlineDefinitions.h"     // Online definitions
#include "ValorPlayerDefinitions.h"     // Player definitions
#include "ValorUIDefinitions.h"         // UI definitions
#include "ValorLogDefinitions.h"		// Logging macros
#include "ValorDataDefinitions.h"		// Definitions for data curves and tables
#include "ValorMiscDefinitions.h"		// Random definitions
#include "ValorCollisionDefinitions.h"	// Collision definitions (trace channels)

#include "ValorVariantData.h"

DECLARE_LOG_CATEGORY_EXTERN(LogValor, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogValorClient, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogValorServer, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogValorHero, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogValorCharacter, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogValorSpell, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogValorGUI, Log, All);
