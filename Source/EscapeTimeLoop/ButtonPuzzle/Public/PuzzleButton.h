#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonPressed, FName, ButtonID);

UCLASS()
class ESCAPETIMELOOP_API APuzzleButton : public AActor
{
	GENERATED_BODY()

public:
	APuzzleButton();

	UPROPERTY(EditAnywhere)
	FName ButtonID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsClickable = true;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* StonePressSound;

	UPROPERTY(BlueprintAssignable)
	FOnButtonPressed OnButtonPressed;

	UFUNCTION(BlueprintCallable)
	void PressButton();

	FVector InitialLocation;
	FVector PressedTargetLocation;
	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, Category = "Button")
	float PressInterpSpeed = 150.0f;

	UPROPERTY(EditAnywhere, Category = "Button")
	float PressDepth = 10.0f;

	bool bHasBeenPressed = false;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ButtonMesh;

	UFUNCTION()
	void HandleClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);
};
