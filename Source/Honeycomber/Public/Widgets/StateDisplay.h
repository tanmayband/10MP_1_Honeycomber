// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StateDisplay.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class HONEYCOMBER_API UStateDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupState(FString stateName, FString initialStateValue);
	void UpdateState(FString newStateValue);
	void SetBGColour(FLinearColor newColour);
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UImage* StateBG;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* StateName;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* StateValue;
};
