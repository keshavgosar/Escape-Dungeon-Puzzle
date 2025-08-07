#include "EscapeTimeLoop/ButtonPuzzle/Public/PuzzleButton.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

APuzzleButton::APuzzleButton()
{
	PrimaryActorTick.bCanEverTick = true;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	RootComponent = ButtonMesh;
	
	ButtonMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ButtonMesh->SetCollisionResponseToAllChannels(ECR_Block);
	ButtonMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	ButtonMesh->SetGenerateOverlapEvents(true);
	ButtonMesh->SetNotifyRigidBodyCollision(true);
	ButtonMesh->SetSimulatePhysics(false);
	ButtonMesh->bSelectable = true;
	ButtonMesh->bReturnMaterialOnMove = true;
}

void APuzzleButton::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		//PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}

	if (ButtonMesh)
	{
		ButtonMesh->OnClicked.AddDynamic(this, &APuzzleButton::HandleClicked);
	}

	InitialLocation = ButtonMesh->GetRelativeLocation();
	PressedTargetLocation = InitialLocation - FVector(0, 0, PressDepth);
}

void APuzzleButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving && ButtonMesh)
	{
		FVector CurrentLocation = ButtonMesh->GetRelativeLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, PressedTargetLocation, DeltaTime, PressInterpSpeed);
		ButtonMesh->SetRelativeLocation(NewLocation);

		if (FVector::Dist(NewLocation, PressedTargetLocation) < 0.5f)
		{
			ButtonMesh->SetRelativeLocation(PressedTargetLocation);
			bIsMoving = false;
		}
	}
}

void APuzzleButton::HandleClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	if (bIsClickable)
	{
		PressButton();
	}
}

void APuzzleButton::PressButton()
{
	if (bHasBeenPressed) return;

	bIsMoving = true;
	bHasBeenPressed = true;

	if (StonePressSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, StonePressSound, GetActorLocation());
	}

	OnButtonPressed.Broadcast(ButtonID);
	UE_LOG(LogTemp, Warning, TEXT("Broadcasting ButtonID: %s"), *ButtonID.ToString());
}
