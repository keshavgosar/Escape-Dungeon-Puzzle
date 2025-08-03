#include "EscapeTimeLoop/MirrorReflectionPuzzle/Public/MirrorActor.h"


AMirrorActor::AMirrorActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(true);
}

void AMirrorActor::BeginPlay()
{
	Super::BeginPlay();
	EnableInput(GetWorld()->GetFirstPlayerController());
}

FVector AMirrorActor::GetReflectedDirection(const FVector& Incident, const FVector& HitNormal) const
{
	
	return FMath::GetReflectionVector(Incident, HitNormal);
	
}

void AMirrorActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("Mirror clicked!"));
	FRotator NewRot = GetActorRotation();
	TArray<float> SnapAngles = {0.f, 45.f, 90.f, 135.f, 180.f, 225.f, 270.f, 315.f};
	CurrentIndex = (CurrentIndex + 1) % SnapAngles.Num();
	NewRot.Yaw = SnapAngles[CurrentIndex];
	SetActorRotation(NewRot);
}