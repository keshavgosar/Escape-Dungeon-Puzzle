#include "EscapeTimeLoop//MirrorReflectionPuzzle/Public/TargetActor.h"

ATargetActor::ATargetActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATargetActor::OnHit()
{
	OnPuzzleSolved.Broadcast();
}
