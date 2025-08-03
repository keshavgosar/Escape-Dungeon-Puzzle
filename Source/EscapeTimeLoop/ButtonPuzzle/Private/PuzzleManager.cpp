#include "EscapeTimeLoop/ButtonPuzzle/Public/PuzzleManager.h"
#include "EscapeTimeLoop/ButtonPuzzle/Public/DoorActor.h"
#include "EscapeTimeLoop/ButtonPuzzle/Public/PuzzleButton.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

APuzzleManager::APuzzleManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APuzzleManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundButtons;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APuzzleButton::StaticClass(), FoundButtons);

	for (AActor* Actor : FoundButtons)
	{
		if (APuzzleButton* Button = Cast<APuzzleButton>(Actor))
		{
			Button->OnButtonPressed.AddDynamic(this, &APuzzleManager::HandleButtonPressed);
			UE_LOG(LogTemp, Warning, TEXT("Bound Button: %s to Manager"), *Button->GetName());
		}
	}


	CurrentOrder.Empty();
	
}

void APuzzleManager::HandleButtonPressed(FName ButtonID)
{


	UE_LOG(LogTemp, Warning, TEXT("Manager received button press: %s"), *ButtonID.ToString());
	
	if (CurrentOrder.Num() >= CorrectOrder.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Too many button presses. Ignoring extra input."));
		return;
	}

	CurrentOrder.Add(ButtonID);
	UE_LOG(LogTemp, Warning, TEXT("Button Pressed: %s"), *ButtonID.ToString());


	if (CurrentOrder.Num() == CorrectOrder.Num())
	{
		CheckSolution();
	}
}

void APuzzleManager::CheckSolution()
{
	bool bSuccess = true;

	for (int32 i = 0; i < CorrectOrder.Num(); ++i)
	{
		if (CurrentOrder[i] != CorrectOrder[i])
		{
			bSuccess = false;
			break;
		}
	}

	if (bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT(" Correct sequence! Door opening..."));

		if (DoorToOpen)
		{
			DoorToOpen->OpenDoor();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" Incorrect sequence! Restarting level in 1.5 seconds..."));


		GetWorld()->GetTimerManager().SetTimer(RestartTimer, this, &APuzzleManager::RestartLevel, 1.5f, false);
	}
}

void APuzzleManager::ResetPuzzle()
{
	CurrentOrder.Empty();
}

void APuzzleManager::RestartLevel()
{
	if (RestartSound)
	{
		UGameplayStatics::PlaySound2D(this, RestartSound);
	}
	
	ResetPuzzle();
	
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
