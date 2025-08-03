#include "EscapeTimeLoop/ButtonPuzzle/Public/DoorActor.h"

#include "Kismet/GameplayStatics.h"


ADoorActor::ADoorActor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
}

void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	TargetLocation = InitialLocation + OpenOffset;
}

void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOpening)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, DoorOpenSpeed);

		SetActorLocation(NewLocation);

		// Stop interpolating if we're close enough
		if (FVector::Dist(NewLocation, TargetLocation) < 1.0f)
		{
			SetActorLocation(TargetLocation);
			bIsOpening = false;
		}
	}
}

void ADoorActor::OpenDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Door is starting to open!"));
	bIsOpening = true;

	if (DoorOpenSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DoorOpenSound, GetActorLocation());
	}
}