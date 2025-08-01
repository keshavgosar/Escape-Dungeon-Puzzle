#include "MoverComponent.h"



// Sets default values for this component's properties
UMoverComponent::UMoverComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	
}


// Called when the game starts
void UMoverComponent::BeginPlay() {
	Super::BeginPlay();

	StartLocation = GetOwner() -> GetActorLocation();
	TargetLocation = StartLocation + MoveDistance;
	Speed = FVector::Distance(StartLocation, TargetLocation) / Time;
	
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentLocation = GetOwner() -> GetActorLocation();

	if (bShouldMove) {
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner() -> SetActorLocation(NewLocation);
	}

	else if (CurrentLocation != StartLocation) {
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, StartLocation, DeltaTime, Speed);
		GetOwner() -> SetActorLocation(NewLocation);
	}
}



void UMoverComponent::SetShouldMove(bool bNewShouldMove) {
	bShouldMove = bNewShouldMove;
}