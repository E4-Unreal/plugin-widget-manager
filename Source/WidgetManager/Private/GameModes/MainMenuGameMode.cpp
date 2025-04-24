// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MainMenuGameMode.h"

#include "Subsystems/WidgetManagerSubsystem.h"

void AMainMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (auto LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
    {
        auto WidgetManagerSubsystem = LocalPlayer->GetSubsystem<UWidgetManagerSubsystem>();
        for (auto DefaultWidget : DefaultWidgets)
        {
            WidgetManagerSubsystem->ShowWidget(DefaultWidget);
        }
    }
}

void AMainMenuGameMode::Destroyed()
{
    if (auto LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
    {
        auto WidgetManagerSubsystem = LocalPlayer->GetSubsystem<UWidgetManagerSubsystem>();
        for (auto DefaultWidget : DefaultWidgets)
        {
            WidgetManagerSubsystem->RemoveWidget(DefaultWidget);
        }
    }

    Super::Destroyed();
}
