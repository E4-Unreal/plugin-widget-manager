// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WidgetManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Logging.h"

UUserWidget* UWidgetManagerComponent::GetOrCreateWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass ==  nullptr) return nullptr;

    return WidgetMap.Contains(WidgetClass) ? WidgetMap[WidgetClass].Get() : RegisterWidget(WidgetClass);
}

void UWidgetManagerComponent::ShowWidget(TSubclassOf<UUserWidget> WidgetClass, EWidgetType WidgetType)
{
    if (!WidgetClass) return;

    switch (WidgetType)
    {
    case EWidgetType::HUD:
        ShowWidgetByClass(WidgetClass);
        break;
    case EWidgetType::Main:
        ShowMainWidget(WidgetClass);
        break;
    case EWidgetType::Sub:
        ShowSubWidget(WidgetClass);
        break;
    }
}

void UWidgetManagerComponent::HideWidget(TSubclassOf<UUserWidget> WidgetClass, EWidgetType WidgetType)
{
    if (!WidgetClass) return;

    switch (WidgetType)
    {
    case EWidgetType::HUD:
        HideWidgetByClass(WidgetClass);
        break;
    case EWidgetType::Main:
        HideMainWidget(WidgetClass);
        break;
    case EWidgetType::Sub:
        HideSubWidget(WidgetClass);
        break;
    }
}

void UWidgetManagerComponent::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass, EWidgetType WidgetType)
{
    if (!WidgetClass) return;

    switch (WidgetType)
    {
    case EWidgetType::HUD:
        ToggleWidgetByClass(WidgetClass);
        break;
    case EWidgetType::Main:
        ToggleMainWidget(WidgetClass);
        break;
    case EWidgetType::Sub:
        ToggleSubWidget(WidgetClass);
        break;
    }
}

void UWidgetManagerComponent::ShowMainWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass || IsInViewport(WidgetClass)) return;

    auto OldMainWidget = MainWidget;
    auto NewMainWidget = WidgetClass;

    // Show New Main Widget
    MainWidget = NewMainWidget;
    ShowWidgetByClass(NewMainWidget);
    SetShowMouseCursor(true);

    // Hide Old Main Widget
    HideMainWidget(OldMainWidget);

    // Hide All Sub Widgets
    for (int32 Index = SubWidgets.Num() - 1; Index >= 0; --Index)
    {
        HideSubWidget(SubWidgets[Index]);
    }
}

void UWidgetManagerComponent::HideMainWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass || MainWidget != WidgetClass || !IsInViewport(WidgetClass)) return;

    auto OldMainWidget = MainWidget;
    HideWidgetByClass(OldMainWidget);
    MainWidget = nullptr;

    SetShowMouseCursor(false);
}

void UWidgetManagerComponent::ToggleMainWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass) return;

    if (IsInViewport(WidgetClass))
    {
        HideMainWidget(WidgetClass);
    }
    else
    {
        ShowMainWidget(WidgetClass);
    }
}

void UWidgetManagerComponent::ShowSubWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass || IsInViewport(WidgetClass)) return;

    // 메인 위젯이 표시되고 있는 동안에는 서브 위젯을 표시할 수 없습니다.
    if (MainWidget) return;

    SubWidgets.Emplace(WidgetClass);
    ShowWidgetByClass(WidgetClass);
    SetShowMouseCursor(true);
}

void UWidgetManagerComponent::HideSubWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass || !IsInViewport(WidgetClass)) return;

    SubWidgets.RemoveSingle(WidgetClass);
    HideWidgetByClass(WidgetClass);
    SetShowMouseCursor(false);
}

void UWidgetManagerComponent::ToggleSubWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass) return;

    if (IsInViewport(WidgetClass))
    {
        HideSubWidget(WidgetClass);
    }
    else
    {
        ShowSubWidget(WidgetClass);
    }
}

bool UWidgetManagerComponent::ShowWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
    if (UUserWidget* Widget = GetOrCreateWidget(WidgetClass))
    {
        if (Widget->IsInViewport())
        {
            LOG_ACTOR_COMPONENT(Warning, TEXT("%s is already in viewport."), *WidgetClass->GetName())
        }
        else
        {
            LOG_ACTOR_COMPONENT(Log, TEXT("%s is added to viewport."), *WidgetClass->GetName())

            Widget->AddToViewport();

            return true;
        }
    }

    return false;
}

bool UWidgetManagerComponent::HideWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
    // 위젯 비활성화
    if (UUserWidget* Widget = GetOrCreateWidget(WidgetClass))
    {
        if (!Widget->IsInViewport())
        {
            LOG_ACTOR_COMPONENT(Warning, TEXT("%s is already not in viewport."), *WidgetClass->GetName())
        }
        else
        {
            LOG_ACTOR_COMPONENT(Log, TEXT("%s is removed from viewport."), *WidgetClass->GetName())

            Widget->RemoveFromParent();

            return true;
        }
    }

    return false;
}

void UWidgetManagerComponent::ToggleWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass) return;

    if (IsInViewport(WidgetClass))
    {
        HideWidgetByClass(WidgetClass);
    }
    else
    {
        ShowWidgetByClass(WidgetClass);
    }
}

bool UWidgetManagerComponent::IsInViewport(TSubclassOf<UUserWidget> WidgetClass) const
{
    if (!WidgetMap.Contains(WidgetClass)) return false;

    return WidgetMap[WidgetClass]->IsInViewport();
}

APlayerController* UWidgetManagerComponent::GetPlayerController() const
{
    UClass* OwnerClass = GetOwner()->GetClass();
    APlayerController* PlayerController = nullptr;

    if (OwnerClass->IsChildOf(APlayerController::StaticClass()))
    {
        PlayerController = Cast<APlayerController>(GetOwner());
    }
    else if (OwnerClass->IsChildOf(APawn::StaticClass()))
    {
        APawn* OwningPawn = Cast<APawn>(GetOwner());
        PlayerController = Cast<APlayerController>(OwningPawn->Controller);
    }

    return PlayerController;
}

UUserWidget* UWidgetManagerComponent::RegisterWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    // 유효성 검사
    if (WidgetClass == nullptr) return nullptr;

    // 중복 호출 방지
    if (WidgetMap.Contains(WidgetClass))
    {
        LOG_ACTOR_COMPONENT(Error, TEXT("%s is already registered."), *WidgetClass->GetName())
    }
    else
    {
        // 위젯 생성 및 등록
        UUserWidget* Widget = CreateWidget<UUserWidget>(GetPlayerController(), WidgetClass);
        WidgetMap.Emplace(WidgetClass, Widget);

        LOG_ACTOR_COMPONENT(Log, TEXT("%s is registered"), *WidgetClass->GetName())
    }

    return WidgetMap[WidgetClass];
}

void UWidgetManagerComponent::UnRegisterWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    // 유효성 검사
    if (WidgetClass == nullptr) return;

    // 중복 호출 방지
    if (!WidgetMap.Contains(WidgetClass))
    {
        LOG_ACTOR_COMPONENT(Error, TEXT("%s is already unregistered."), *WidgetClass->GetName())
        return;
    }

    // 위젯 파괴 및 등록 해제
    HideWidgetByClass(WidgetClass);
    WidgetMap.Remove(WidgetClass);

    LOG_ACTOR_COMPONENT(Log, TEXT("%s is unregistered"), *WidgetClass->GetName())
}

void UWidgetManagerComponent::SetShowMouseCursor(bool bNewShowMouseCursor)
{
    if (bShowMouseCursor == bNewShowMouseCursor) return;

    auto OwningPlayerController = GetPlayerController();
    if (bNewShowMouseCursor)
    {
        int32 SizeX, SizeY;
        OwningPlayerController->GetViewportSize(SizeX, SizeY);
        OwningPlayerController->SetMouseLocation(SizeX / 2, SizeY / 2);
        bShowMouseCursor = true;
        OwningPlayerController->SetShowMouseCursor(true);
        OwningPlayerController->SetIgnoreLookInput(true);
        FInputModeGameAndUI InputMode;
        InputMode.SetHideCursorDuringCapture(false);
        OwningPlayerController->SetInputMode(InputMode);
    }
    else if (!MainWidget && SubWidgets.IsEmpty())
    {
        bShowMouseCursor = false;
        OwningPlayerController->SetShowMouseCursor(false);
        OwningPlayerController->SetIgnoreLookInput(false);
        OwningPlayerController->SetInputMode(FInputModeGameOnly());
    }
}
