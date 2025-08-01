#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotatorComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETIMELOOP_API URotatorComponent : public UActorComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover")
	FRotator RotateAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover")
	float Time = 4.0f;

	UFUNCTION(BlueprintCallable)
	void SetShouldRotate(bool bNewShouldMove);

private:
	FRotator StartRotation, TargetRotation;
	float Speed;

	bool bShouldMove = false;
};