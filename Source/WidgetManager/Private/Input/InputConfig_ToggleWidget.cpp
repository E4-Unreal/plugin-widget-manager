// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_ToggleWidget.h"

#include "Components/WidgetManagerComponent.h"

void UInputConfig_ToggleWidget::OnTriggered_Implementation(APawn* Pawn, APlayerController* PlayerController,
                                                           const FInputActionValue& InputActionValue)
{
    Super::OnTriggered_Implementation(Pawn, PlayerController, InputActionValue);

    auto Target = bPlayerController ? Cast<AActor>(PlayerController) : Cast<AActor>(Pawn);
    auto WidgetManagerComponent = Target->GetComponentByClass<UWidgetManagerComponent>();
    if (WidgetManagerComponent) WidgetManagerComponent->ToggleWidget(WidgetClass, WidgetType);
}
