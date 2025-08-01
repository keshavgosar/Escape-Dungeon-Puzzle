#include "RotatorComponent.h"



// Sets default values for this component's properties
URotatorComponent::URotatorComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void URotatorComponent::BeginPlay() {
	Super::BeginPlay();

	StartRotation = GetOwner() -> GetActorRotation();
	TargetRotation = StartRotation + RotateAngle;

	Speed = RotateAngle.Euler().Length() / Time;
	
}


// Called every frame
void URotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator CurrentRotation = GetOwner() -> GetActorRotation();

	if (bShouldMove) {
		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, Speed);
		GetOwner() -> SetActorRotation(NewRotation);
	}

	else if (CurrentRotation != StartRotation) {
		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, Speed);
		GetOwner() -> SetActorRotation(NewRotation);
	}
}



void URotatorComponent::SetShouldRotate(bool bNewShouldMove) {
	bShouldMove = bNewShouldMove;
}