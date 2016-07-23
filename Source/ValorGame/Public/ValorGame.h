// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "Engine.h"				        // Core Engine

#include "Online.h"                     // Online subsystem
#include "Net/UnrealNetwork.h"	        // Replication

#include "SlateBasics.h"                // SWidget classes
#include "SlateExtras.h"                // SWidget classes extended

#include "ValorTypes.h"		            // Commonly-used types

#include "ParticleDefinitions.h"        // Particle systems
#include "SoundDefinitions.h"           // Sound systems

#include "ValorPlatformDefinitions.h"   // Platform definitions
#include "ValorOnlineDefinitions.h"     // Online definitions
#include "ValorPlayerDefinitions.h"     // Player definitions
#include "ValorUIDefinitions.h"         // UI definitions

DECLARE_LOG_CATEGORY_EXTERN(LogValor, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogValorClient, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogValorServer, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogValorHero, Log, All);

#define VALOR_LOG(Message) if (GEngine) { GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.f, FColor::Cyan, TEXT(Message), false); }
#define VALOR_LOGF(Message) if (GEngine) { GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.f, FColor::Cyan, Message, false); }

#define FIND_ROW_CONTEXT TEXT("VALOR_ROW_CONTEXT")