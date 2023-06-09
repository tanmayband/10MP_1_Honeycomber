// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DayCheckpoint.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"
#include "Subsystems/MoneyFlowSubsystem.h"
#include "Subsystems/ResourceManagerSubsystem.h"
#include "Subsystems/BeehiveManagerSubsystem.h"

void UDayCheckpoint::SetupCheckpoint(uint8 dayNum)
{
	BGMaterial = IrisBG->GetDynamicMaterial();
	SetBGRadius(0);
	DayText->SetRenderOpacity(0);
	MoneyText->SetRenderOpacity(0);
	BeesText->SetRenderOpacity(0);

	DayText->SetText(FText::FromString(FString::Printf(TEXT("Day %d"), dayNum)));

	UMoneyFlowSubsystem* moneySubsystem = GetGameInstance()->GetSubsystem<UMoneyFlowSubsystem>();
	MoneyText->SetText(FText::FromString(FString::Printf(TEXT("Money: %d"), moneySubsystem->GetCurrentMoney())));

	UBeehiveManagerSubsystem* beehiveSubsystem = GetGameInstance()->GetSubsystem<UBeehiveManagerSubsystem>();
	BeesText->SetText(FText::FromString(FString::Printf(TEXT("Bees Alive: %d"), beehiveSubsystem->GetAllBees())));
}

void UDayCheckpoint::UpdateDayCount()
{

}

void UDayCheckpoint::StartDayAnim()
{
	PlayAnimationForward(DayIn);
}

void UDayCheckpoint::EndDayAnim()
{
	PlayAnimationForward(DayOut);
}

void UDayCheckpoint::GameOverAnim()
{
	BeesText->SetText(FText::FromString(FString::Printf(TEXT("Bees Alive: 0"))));
	PlayAnimationForward(GameOver);
}

void UDayCheckpoint::SetBGRadius(float newRadius)
{
	CurrentBGRadius = FMath::Clamp(newRadius,0,1);
	BGMaterial->SetScalarParameterValue("Radius", CurrentBGRadius);
}

void UDayCheckpoint::StartDayAnimDone()
{
	OnDayAnimDoneDelegate.ExecuteIfBound(true);
}

void UDayCheckpoint::EndDayAnimDone()
{
	OnDayAnimDoneDelegate.ExecuteIfBound(false);
}
