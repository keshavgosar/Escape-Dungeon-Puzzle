#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MirrorActor.generated.h"

UCLASS()
class ESCAPETIMELOOP_API AMirrorActor : public AActor
{
	GENERATED_BODY()

public:
	AMirrorActor();

	UPROPERTY()
	int32 CurrentIndex = 0;

	// Calculates reflected direction
	FVector GetReflectedDirection(const FVector& Incident, const FVector& HitNormal) const;

protected:
	virtual void BeginPlay() override;

public:
	// Simple player input for demo - rotates mirror
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;
};
