#include "Cabinet.h"



// Sets default values
ACabinet::ACabinet() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ACabinet::BeginPlay() {
	Super::BeginPlay();
	
	// Generate a random number from 1 to 7.
	int RandomNumber = FMath::RandRange(1, 7);

	// Generate the 3 digit code.
	int Code = GenerateBinaryNumber(RandomNumber);
}


// Called every frame
void ACabinet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!(LeftLever && MiddleLever && RightLever) ) {
		return;
	}

}



int ACabinet::GenerateBinaryNumber(int Number) {
	int sum = 0;
	for (int power = 1; Number > 0; power *= 10, Number /= 2) {
		int digit = Number % 2;
		sum += (digit * power);		
	}

	return sum;
}
