// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Interactable.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/InteractionPopup.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	check(SceneRoot);
	SetRootComponent(SceneRoot);
	
	InteractionArea = CreateDefaultSubobject<UBoxComponent>("InteractionArea");
	check(InteractionArea);
	InteractionArea->SetupAttachment(SceneRoot);
	InteractionArea->SetBoxExtent(FVector(50, 50, 50));

	InteractionPopupComponent = CreateDefaultSubobject<UWidgetComponent>("InteractionPopup");
	check(InteractionPopupComponent);
	InteractionPopupComponent->SetupAttachment(SceneRoot);
	InteractionPopupComponent->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionPopupComponent->SetHiddenInGame(true);

	Tags.Add("Interactable" );
}

void AInteractable::OnConstruction(const FTransform& Transform)
{
	InteractionPopupComponent->SetRelativeLocation(PopupLocation);
	InteractionPopupComponent->SetWidgetClass(InteractionPopupClass);
	InteractionPopupComponent->SetPivot(PopupPivot);
}

void AInteractable::ToggleInteractionPopup(bool show)
{
	InteractionPopup->UnhighlightAllInteractionOptions();
	InteractionPopupComponent->SetHiddenInGame(!show);
}

void AInteractable::Interact()
{
	if(InteractionOptions.Num() > 0)
		UE_LOG(LogTemp, Warning, TEXT("Option executed: %s"), *InteractionOptions[CurrentOptionIndex].OptionText);
}

void AInteractable::InteractOption(uint8 index)
{
	CurrentOptionIndex = index;
	Interact();
}

void AInteractable::CycleOptions(uint8 nextIndex)
{
	CurrentOptionIndex = FMath::Clamp(CurrentOptionIndex + nextIndex, 0, InteractionOptions.Num() - 1);
	InteractionPopup->HighlightInteractionOption(CurrentOptionIndex);
}

void AInteractable::SetInteractableName(FString newName)
{
	InteractableName = newName;
	InteractionPopup->SetupPopupName(InteractableName);
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	InteractionPopup = CastChecked<UInteractionPopup, UUserWidget>(InteractionPopupComponent->GetUserWidgetObject());
	InteractionPopup->SetupPopup(InteractableName, InteractionOptions, PopupPivot);
	InteractionPopup->OnOptionSelectedDelegate.BindUObject(this, &AInteractable::InteractOption);
}