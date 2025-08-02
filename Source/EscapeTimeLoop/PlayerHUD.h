#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"



class UCanvasPanel;
class UTextBlock;

UCLASS()
class ESCAPETIMELOOP_API UPlayerHUD : public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	int Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PromptDisplay;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText GetTimerText();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* Panel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TimerDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	int Minutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	int Seconds;

private:
    FTimerHandle TimerHandle;

	void StartTimer();
	void StopTimer();
	void DecrementTime();
};