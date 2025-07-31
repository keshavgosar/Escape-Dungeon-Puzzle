#include "PlayerHUD.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"



void UPlayerHUD::NativeConstruct() {
    Super::NativeConstruct();
    StartTimer();
}


void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
    Super::NativeTick(MyGeometry, InDeltaTime);
    
    if (Timer < 0) {
        // TODO:- Restart Level.
        StopTimer();
        return;
    }

    if (!TimerDisplay) {
        return;
    }

    TimerDisplay -> SetText(GetTimerText());
}


void UPlayerHUD::StartTimer() {
    GetWorld() -> GetTimerManager().SetTimer(TimerHandle, this, &UPlayerHUD::DecrementTime, 1.0f, true);
}

void UPlayerHUD::StopTimer() {
    GetWorld() -> GetTimerManager().ClearTimer(TimerHandle);
}

void UPlayerHUD::DecrementTime() {
    Timer--;
}


FText UPlayerHUD::GetTimerText() {
    Minutes = Timer / 60;
    Seconds = Timer % 60;

    FNumberFormattingOptions TimeFormat;
    TimeFormat.MinimumIntegralDigits = 2;

    const FString TimeString = FText::AsNumber(Minutes, &TimeFormat).ToString() + " : "  + FText::AsNumber(Seconds, &TimeFormat).ToString();
    return FText::FromString(TimeString);
}