// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_ToggleWidget.h"

#include "InputAction.h"
#include "Blueprint/UserWidget.h"
#include "Subsystems/WidgetManagerSubsystem.h"

TArray<UInputAction*> UInputConfig_ToggleWidget::GetInputActions() const
{
    TArray<TObjectPtr<UInputAction>> InputActions;
    ToggleWidgetMap.GetKeys(InputActions);

    return InputActions;
}

void UInputConfig_ToggleWidget::OnTriggered_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance)
{
    Super::OnTriggered_Implementation(PlayerController, InputActionInstance);

    auto InputAction = InputActionInstance.GetSourceAction();
    if (!ToggleWidgetMap.Contains(InputAction)) return;

    auto WidgetClass = ToggleWidgetMap[InputAction];
    if (!WidgetClass) return;

    auto WidgetManagerSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UWidgetManagerSubsystem>();
    WidgetManagerSubsystem->ToggleWidget(WidgetClass);
}
