#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cabinet.generated.h"



UCLASS()
class ESCAPETIMELOOP_API ACabinet : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACabinet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int GenerateBinaryNumber(int Number);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	AActor* LeftLever;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	AActor* MiddleLever;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	AActor* RightLever;
};