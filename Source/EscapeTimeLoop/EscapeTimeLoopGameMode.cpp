// Copyright Epic Games, Inc. All Rights Reserved.

#include "EscapeTimeLoopGameMode.h"
#include "EscapeTimeLoopCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEscapeTimeLoopGameMode::AEscapeTimeLoopGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
