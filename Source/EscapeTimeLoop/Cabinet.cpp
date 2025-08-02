#include "Cabinet.h"
#include "Lever.h"
#include "Components/PointLightComponent.h"



// Sets default values
ACabinet::ACabinet() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent> (TEXT("Root"));
	RootComponent = RootComp;

	CabinetMesh = CreateDefaultSubobject<UStaticMeshComponent> (TEXT("CabinetMesh"));
	CabinetMesh -> SetupAttachment(RootComp);

	CabinetDoorMesh = CreateDefaultSubobject<USkeletalMeshComponent> (TEXT("CabinetDoor"));
	CabinetDoorMesh -> SetupAttachment(CabinetMesh);

	BulbMesh = CreateDefaultSubobject<UStaticMeshComponent> (TEXT("BulbMesh"));
	BulbMesh -> SetupAttachment(CabinetMesh);

	BulbLight = CreateDefaultSubobject<UPointLightComponent> (TEXT("BulbLight"));
	BulbLight -> SetupAttachment(CabinetMesh);

	LeftLever = CreateDefaultSubobject<UChildActorComponent> (TEXT("LeftLever"));
	LeftLever -> SetupAttachment(CabinetMesh, TEXT("LeftLeverSocket") );
	LeftLever -> SetChildActorClass(LeverClass);

	MiddleLever = CreateDefaultSubobject<UChildActorComponent> (TEXT("MiddleLever"));
	MiddleLever -> SetupAttachment(CabinetMesh, TEXT("MiddleLeverSocket") );
	MiddleLever -> SetChildActorClass(LeverClass);

	RightLever = CreateDefaultSubobject<UChildActorComponent> (TEXT("RightLever"));
	RightLever -> SetupAttachment(CabinetMesh, TEXT("RightLeverSocket") );
	RightLever -> SetChildActorClass(LeverClass);
}


// Called when the game starts or when spawned
void ACabinet::BeginPlay() {
	Super::BeginPlay();
	
	// Generate a random number from 1 to 7.
	int RandomNumber = FMath::RandRange(1, 7);

	// Generate the 3 digit code.
	int Code = GenerateBinaryNumber(RandomNumber);
	UE_LOG(LogTemp, Warning, TEXT("Code = %d"), Code);

	// Assign correct unlocking state to each switch.
	if (RightLever) {
		ALever* Lever = Cast<ALever> (RightLever -> GetChildActor() );
		if (Lever) {
			Lever -> bCorrectState = (Code % 10) ? true : false;
			UE_LOG(LogTemp, Warning, TEXT("LeftLever = %d"), Lever -> bCorrectState);
		}
	}
	Code /= 10;

	if (MiddleLever) {
		ALever* Lever = Cast<ALever> (MiddleLever -> GetChildActor() );
		if (Lever) {
			Lever -> bCorrectState = (Code % 10) ? true : false;
			UE_LOG(LogTemp, Warning, TEXT("MiddleLever = %d"), Lever -> bCorrectState);
		}
	}
	Code /= 10;
	
	if (LeftLever) {
		ALever* Lever = Cast<ALever> (LeftLever -> GetChildActor() );
		if (Lever) {
			Lever -> bCorrectState = (Code % 10) ? true : false;
			UE_LOG(LogTemp, Warning, TEXT("RightLever = %d"), Lever -> bCorrectState);
		}
	}
}


// Called every frame
void ACabinet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);


}



int ACabinet::GenerateBinaryNumber(int Number) {
	int sum = 0;
	for (int power = 1; Number > 0; power *= 10, Number /= 2) {
		int digit = Number % 2;
		sum += (digit * power);		
	}

	return sum;
}
