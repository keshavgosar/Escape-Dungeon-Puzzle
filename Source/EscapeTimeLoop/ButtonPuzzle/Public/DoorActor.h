#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

UCLASS()
class ESCAPETIMELOOP_API ADoorActor : public AActor
{
	GENERATED_BODY()
    
public:    
	ADoorActor();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* DoorOpenSound;

	UFUNCTION(BlueprintCallable)
	void OpenDoor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FVector OpenOffset = FVector(0, 0, 400); // Upward

	UPROPERTY(EditAnywhere, Category = "Door")
	float DoorOpenSpeed = 200.0f;
	
	FVector InitialLocation;
	FVector TargetLocation;
	bool bIsOpening = false;
};
