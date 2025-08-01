#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETIMELOOP_API UMoverComponent : public UActorComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover")
	FVector MoveDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover")
	float Time = 4.0f;

	UFUNCTION(BlueprintCallable)
	void SetShouldMove(bool bNewShouldMove);
	
private:
	FVector StartLocation, TargetLocation;
	float Speed;
	bool bShouldMove = false;
};