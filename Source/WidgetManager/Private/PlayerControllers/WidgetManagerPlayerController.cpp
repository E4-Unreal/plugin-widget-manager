// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/WidgetManagerPlayerController.h"

#include "Subsystems/WidgetManagerSubsystem.h"

void AWidgetManagerPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto WidgetManagerSubsystem = GetLocalPlayer()->GetSubsystem<UWidgetManagerSubsystem>();
    for (auto DefaultWidget : DefaultWidgets)
    {
        WidgetManagerSubsystem->ShowWidget(DefaultWidget);
    }
}

void AWidgetManagerPlayerController::Destroyed()
{
    auto WidgetManagerSubsystem = GetLocalPlayer()->GetSubsystem<UWidgetManagerSubsystem>();
    for (auto DefaultWidget : DefaultWidgets)
    {
        WidgetManagerSubsystem->RemoveWidget(DefaultWidget);
    }

    Super::Destroyed();
}
