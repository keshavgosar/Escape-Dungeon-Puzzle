#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleSolved);

UCLASS()
class ESCAPETIMELOOP_API ATargetActor : public AActor
{
	GENERATED_BODY()

public:
	ATargetActor();

	void OnHit();

	// Blueprint-exposed event
	UPROPERTY(BlueprintAssignable)
	FOnPuzzleSolved OnPuzzleSolved;
};
