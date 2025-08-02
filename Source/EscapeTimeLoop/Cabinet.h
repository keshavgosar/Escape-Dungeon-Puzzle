#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cabinet.generated.h"



class ALever;
class UPointLightComponent;


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

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CabinetMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* CabinetDoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BulbMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPointLightComponent* BulbLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lever")
	UChildActorComponent* LeftLever;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lever")
	UChildActorComponent* MiddleLever;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lever")
	UChildActorComponent* RightLever;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ALever> LeverClass;

	

	int GenerateBinaryNumber(int Number);

};