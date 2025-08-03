// PuzzleManager.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleManager.generated.h"

UCLASS()
class ESCAPETIMELOOP_API APuzzleManager : public AActor
{
	GENERATED_BODY()
    
public:
	APuzzleManager();

	UPROPERTY(EditAnywhere)
	TArray<FName> CorrectOrder;

	UFUNCTION(BlueprintCallable)
	void HandleButtonPressed(FName ButtonID);

	UPROPERTY(EditAnywhere)
	class ADoorActor* DoorToOpen;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* RestartSound;

	UFUNCTION(BlueprintCallable)
	void RestartLevel();

protected:
	virtual void BeginPlay() override;

private:
	TArray<FName> CurrentOrder;

	void CheckSolution();
	void ResetPuzzle();
};
