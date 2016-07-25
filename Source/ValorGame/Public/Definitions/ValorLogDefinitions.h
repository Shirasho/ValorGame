// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#define VALOR_LOG(Message, ...) if (GEngine) { GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.f, FColor::Cyan, FString::Printf(TEXT(Message), ##__VA_ARGS__), false); }