// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WidgetManagerComponent.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "Subsystems/WidgetManagerSubsystem.h"

void UWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (auto WidgetManagerSystem = GetWidgetManagerSubsystem())
    {
        for (auto DefaultWidget : DefaultWidgets)
        {
            WidgetManagerSystem->ShowWidget(DefaultWidget);
        }
    }
}

void UWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    if (auto WidgetManagerSystem = GetWidgetManagerSubsystem())
    {
        for (auto DefaultWidget : DefaultWidgets)
        {
            WidgetManagerSystem->RemoveWidget(DefaultWidget);
        }
    }

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

UWidgetManagerSubsystem* UWidgetManagerComponent::GetWidgetManagerSubsystem() const
{
    ULocalPlayer* LocalPlayer = nullptr;

    if (APawn* OwningPawn = Cast<APawn>(GetOwner()))
    {
        if (OwningPawn->IsLocallyControlled())
        {
            LocalPlayer = Cast<APlayerController>(OwningPawn->GetController())->GetLocalPlayer();
        }
    }
    else if (APlayerController* OwningPlayerController = Cast<APlayerController>(GetOwner()))
    {
        if (OwningPlayerController->IsLocalController())
        {
            LocalPlayer = OwningPlayerController->GetLocalPlayer();
        }
    }
    else if (AGameModeBase* GameMode = Cast<AGameModeBase>(GetOwner()))
    {
        if (UWorld* World = GetWorld())
        {
            LocalPlayer = World->GetFirstLocalPlayerFromController();
        }
    }
    else if (AGameStateBase* GameState = Cast<AGameStateBase>(GetOwner()))
    {
        if (UWorld* World = GetWorld())
        {
            LocalPlayer = World->GetFirstLocalPlayerFromController();
        }
    }

    return LocalPlayer ? LocalPlayer->GetSubsystem<UWidgetManagerSubsystem>() : nullptr;
}
