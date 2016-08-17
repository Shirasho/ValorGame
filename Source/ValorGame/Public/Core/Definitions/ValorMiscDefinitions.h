// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#define SET_TIMER(FuncPointer, Rate, bLoop, FirstDelay) \
{ \
	FTimerHandle TimerHandle; \
	GetWorldTimerManager().SetTimer(TimerHandle, this, &FuncPointer, Rate, bLoop, FirstDelay); \
}

#define SET_TIMER_HANDLE(TimerHandle, FuncPointer, Rate, bLoop, FirstDelay) \
{ \
	GetWorldTimerManager().SetTimer(TimerHandle, this, &FuncPointer, Rate, bLoop, FirstDelay); \
}

#define CLEAR_TIMER(TimerHandle) \
{ \
	GetWorldTimerManager().ClearTimer(TimerHandle); \
}

#define IS_TIMER_ACTIVE(TimerHandle) \
{ \
	GetWorldTimerManager().IsTimerActive(TimerHandle); \
}