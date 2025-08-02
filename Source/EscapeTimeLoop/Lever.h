#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"



class URotatorComponent;


UCLASS()
class ESCAPETIMELOOP_API ALever : public AActor {
    GENERATED_BODY()

public:
	// Sets default values for this actor's properties
    ALever();

protected:
	// Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* LeverMesh;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    URotatorComponent* RotatorComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCorrectState = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOn = false;
};