// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#define VALOR_NET_MODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
	: ((GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
	: ((GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
	: ((GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
	: TEXT("[Standalone] ")))))

#if _MSC_VER
#define VALOR_FUNC_NAME TEXT(__FUNCTION__)
#else
#define VALOR_FUNC_NAME TEXT(__func__)
#endif

#define VALOR_LOG(LogCategory, LogVerbosity, Format, ...) \
{\
	const FString Message = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogCategory, LogVerbosity, TEXT("%s %s() - %s"), VALOR_NET_MODE_WORLD, VALOR_FUNC_NAME, *Message); \
}

#define VALOR_PRINT(Format, ...) \
{\
	const FString Prepend = FString::Printf(TEXT("%s %s() - "), VALOR_NET_MODE_WORLD, VALOR_FUNC_NAME, ##__VA_ARGS__); \
	const FString Message = Prepend + FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	if (GEngine) \
	{ \
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.f, FColor::Cyan, *Message, false); \
	} \
}