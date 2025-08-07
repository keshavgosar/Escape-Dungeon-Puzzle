#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSourceActor.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class ESCAPETIMELOOP_API ALightSourceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALightSourceActor();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
	int32 MaxReflections = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
	UNiagaraSystem* LaserBeamFX;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void FireBeam();

	UPROPERTY()
	TArray<UNiagaraComponent*> SpawnedBeams;
};
