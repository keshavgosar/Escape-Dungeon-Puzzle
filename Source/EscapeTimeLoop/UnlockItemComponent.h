#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "UnlockItemComponent.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ESCAPETIMELOOP_API UUnlockItemComponent : public UBoxComponent {
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UUnlockItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tag")
	FName UnlockTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLocked = false;

	UFUNCTION()
	void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	bool HasItemOpened();

private:
	class AEscapeTimeLoopCharacter* PlayerPawn;

	class URotatorComponent* RotatorComp;
	class UMoverComponent* MoverComp;
	class UCameraComponent* CameraComp;

	bool bIsUIAlreadyPresent = false;
	bool bIsItemOpened = false;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* LockedSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* UnlockSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* ItemOpeningSound;

	UPROPERTY(EditAnywhere, Category = "DoorHandle")
	float MaxDistanceFromDoorHandle;

	UPROPERTY(EditAnywhere, Category = "DoorHandle")
	float SweepRadius;
	
	bool IsDoorHandleInReach();

	void InteractWithItem();
	void OpenItem();
	void DisplayUI();
	void HideUI();
};