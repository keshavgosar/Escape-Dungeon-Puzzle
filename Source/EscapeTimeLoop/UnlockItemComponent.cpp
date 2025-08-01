#include "UnlockItemComponent.h"
#include "MoverComponent.h"
#include "RotatorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EscapeTimeLoopCharacter.h"
#include "Camera/CameraComponent.h"



// Sets default values for this component's properties
UUnlockItemComponent::UUnlockItemComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MoverComp = nullptr;
    RotatorComp = nullptr;
    CameraComp = nullptr;

    MaxDistanceFromDoorHandle = 400.0f;
    SweepRadius = 5.0f;
}


// Called when the game starts
void UUnlockItemComponent::BeginPlay() {
	Super::BeginPlay();

    SetComponentTickEnabled(false);

	PlayerPawn = Cast<AEscapeTimeLoopCharacter> (UGameplayStatics::GetPlayerPawn(GetWorld(), 0) );
    MoverComp = Cast<UMoverComponent> (GetOwner() -> GetComponentByClass(UMoverComponent::StaticClass() ) );
    RotatorComp = Cast<URotatorComponent> (GetOwner() -> GetComponentByClass(URotatorComponent::StaticClass() ) );

    if (PlayerPawn) {
        CameraComp = Cast<UCameraComponent> (PlayerPawn -> GetComponentByClass(UCameraComponent::StaticClass() ) );
    }


    OnComponentBeginOverlap.AddDynamic(this, &UUnlockItemComponent::OnOverlapStart);
    OnComponentEndOverlap.AddDynamic(this, &UUnlockItemComponent::OnOverlapEnd);
}




void UUnlockItemComponent::OnOverlapStart(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, 
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
    // Do something when the player overlaps with this component.

    if (PlayerPawn && OtherActor != this -> GetOwner() && OtherActor == PlayerPawn) {
        SetComponentTickEnabled(true);
    }
}


void UUnlockItemComponent::OnOverlapEnd(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex) {
    if (PlayerPawn && OtherActor != this -> GetOwner() && OtherActor == PlayerPawn) {
        HideUI();
        SetComponentTickEnabled(false);

        if (bIsItemOpened) {
            PrimaryComponentTick.bCanEverTick = false;
        }
    }
}




// Called every frame
void UUnlockItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PlayerPawn) {
        return;
    }


    if (IsDoorHandleInReach() ) {
        DisplayUI();
        
        if (PlayerPawn -> bIsInteracting) {
            InteractWithItem();
            HideUI();
        }

    }
    else {
        HideUI();
    }
}




bool UUnlockItemComponent::IsDoorHandleInReach() {
    if (!CameraComp) {
        return false;
    }
    

    FVector Start = CameraComp -> GetComponentLocation();
    FVector End = Start + (CameraComp -> GetForwardVector() ) * MaxDistanceFromDoorHandle;

    //DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	//DrawDebugSphere(GetWorld(), End, SweepRadius, 10, FColor::Green, false, 5);

    FCollisionShape Sphere = FCollisionShape::MakeSphere(SweepRadius);
    FHitResult OutHitResult;

    bool HasHit = GetWorld() -> SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, Sphere);
    return HasHit;
}



void UUnlockItemComponent::InteractWithItem() {
    if (!PlayerPawn) {
        return;
    }

    if (!bIsLocked) {
        // Door/Chest is not Locked.
        OpenItem();
        return;
    }


    // Door/Chest is Locked.
    TArray<FName> PlayerInventory;
    PlayerPawn -> Inventory.GetKeys(PlayerInventory);

    if (PlayerInventory.Contains(UnlockTag) && PlayerPawn -> Inventory[UnlockTag] > 0) {
        PlayerPawn -> Inventory[UnlockTag] -= 1;
        bIsLocked = false;

        if (UnlockSound) {
            UGameplayStatics::SpawnSoundAttached(UnlockSound, this);
        }

        OpenItem();
    }

    else {
        if (LockedSound) {
            UGameplayStatics::SpawnSoundAttached(LockedSound, this);
        }
    }
}



void UUnlockItemComponent::OpenItem() {
    if (MoverComp) {
        MoverComp -> SetShouldMove(true);
    }

    if (RotatorComp) {
        RotatorComp -> SetShouldRotate(true);
    }

    if (ItemOpeningSound) {
        UGameplayStatics::SpawnSoundAttached(ItemOpeningSound, this);
    }

    bIsItemOpened = true;
}



void UUnlockItemComponent::DisplayUI() {
    if (!bIsUIAlreadyPresent && !bIsItemOpened) {
        PlayerPawn -> DisplayInteractPromptUI(bIsLocked, UnlockTag);
        bIsUIAlreadyPresent = true;
    }
}


void UUnlockItemComponent::HideUI() {
    if (bIsUIAlreadyPresent) {
        PlayerPawn -> RemoveInteractPromptUI();
        bIsUIAlreadyPresent = false;
    }
}


bool UUnlockItemComponent::HasItemOpened() {
    return bIsItemOpened;
}