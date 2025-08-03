#include "EscapeTimeLoop/MirrorReflectionPuzzle/Public/LightSourceActor.h"
#include "EscapeTimeLoop/MirrorReflectionPuzzle/Public/MirrorActor.h"
#include "EscapeTimeLoop/MirrorReflectionPuzzle/Public/TargetActor.h"
#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

// Sets default values
ALightSourceActor::ALightSourceActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALightSourceActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ALightSourceActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FireBeam();
}

void ALightSourceActor::FireBeam()
{
    // Destroy previously spawned beams to prevent accumulation
    for (UNiagaraComponent* Beam : SpawnedBeams)
    {
        if (Beam)
        {
            Beam->DestroyComponent();
        }
    }
    SpawnedBeams.Empty();

    FVector Start = GetActorLocation();
    FVector Dir = GetActorForwardVector();

    for (int32 i = 0; i < MaxReflections; ++i)
    {
        FHitResult Hit;
        FVector End = Start + Dir * 5000.0f;
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);

        // Debug line before trace
        DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.1f, 0, 2.0f);

        if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
        {
            // Debug: log hit
            UE_LOG(LogTemp, Warning, TEXT("Hit %s at %s"), *Hit.GetActor()->GetName(), *Hit.ImpactPoint.ToString());

            // Spawn Niagara beam
            UNiagaraComponent* Beam = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                GetWorld(),
                LaserBeamFX,
                Start,
                FRotator::ZeroRotator
            );

            if (Beam)
            {
                Beam->SetVectorParameter(TEXT("Beam Start"), Start);
                Beam->SetVectorParameter(TEXT("Beam End"), Hit.ImpactPoint);
                SpawnedBeams.Add(Beam);
            }

            // Draw debug hit normal
            DrawDebugDirectionalArrow(GetWorld(), Hit.ImpactPoint, Hit.ImpactPoint + Hit.ImpactNormal * 100.0f, 50.0f, FColor::Yellow, false, 1.0f, 0, 2.0f);

            if (AMirrorActor* Mirror = Cast<AMirrorActor>(Hit.GetActor()))
            {
                FVector OldDir = Dir;
                Dir = Mirror->GetReflectedDirection(Dir, Hit.ImpactNormal);
                UE_LOG(LogTemp, Warning, TEXT("Reflected Direction: %s -> %s"), *OldDir.ToString(), *Dir.ToString());

                Start = Hit.ImpactPoint;
                continue;
            }
            else if (ATargetActor* Target = Cast<ATargetActor>(Hit.GetActor()))
            {
                UE_LOG(LogTemp, Warning, TEXT("Hit Target!"));
                Target->OnHit();
                break;
            }

            // Hit something else
            UE_LOG(LogTemp, Warning, TEXT("Beam hit a non-reflective surface"));
            break;
        }
        else
        {
            // Final beam if nothing hit
            DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 2.0f);

            UNiagaraComponent* Beam = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                GetWorld(),
                LaserBeamFX,
                Start,
                FRotator::ZeroRotator
            );

            if (Beam)
            {
                Beam->SetVectorParameter(TEXT("Beam Start"), Start);
                Beam->SetVectorParameter(TEXT("Beam End"), End);
                SpawnedBeams.Add(Beam);
            }

            UE_LOG(LogTemp, Warning, TEXT("Beam reached max range without hitting anything"));
            break;
        }
    }
}
