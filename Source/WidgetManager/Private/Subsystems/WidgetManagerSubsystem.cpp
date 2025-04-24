// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/WidgetManagerSubsystem.h"

#include "CommonActivatableWidget.h"
#include "Blueprint/UserWidget.h"

bool UWidgetManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
    {
        TArray<UClass*> ChildClasses;
        GetDerivedClasses(GetClass(), ChildClasses, false);

        return ChildClasses.Num() == 0;
    }

    return false;
}

void UWidgetManagerSubsystem::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass) return;

    auto Widget = GetOrCreateWidget(WidgetClass);
    ActivateWidget(Widget);
}

void UWidgetManagerSubsystem::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass) return;

    auto Widget = GetOrCreateWidget(WidgetClass);
    DeactivateWidget(Widget);
}

void UWidgetManagerSubsystem::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass) return;

    auto Widget = GetOrCreateWidget(WidgetClass);
    if (IsActive(Widget))
    {
        ActivateWidget(Widget);
    }
    else
    {
        DeactivateWidget(Widget);
    }
}

UUserWidget* UWidgetManagerSubsystem::GetOrCreateWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass) return nullptr;

    // 기존 위젯 가져오기
    if (DoesWidgetExist(WidgetClass)) return WidgetMap[WidgetClass];

    // 새로운 위젯 생성
    auto Widget = CreateWidget(GetLocalPlayer()->PlayerController, WidgetClass);

    // 새로운 위젯 등록
    RegisterWidget(Widget);

    return Widget;
}

void UWidgetManagerSubsystem::RegisterWidget(UUserWidget* Widget)
{
    if (!Widget) return;

    // 등록 여부 확인
    TSubclassOf<UUserWidget> WidgetClass = Widget->GetClass();
    if (DoesWidgetExist(WidgetClass)) return;

    // 등록
    WidgetMap.Emplace(WidgetClass, Widget);

    // 활성화
    ActivateWidget(Widget);
}

void UWidgetManagerSubsystem::UnRegisterWidget(UUserWidget* Widget)
{
    if (!Widget) return;

    // 등록 여부 확인
    TSubclassOf<UUserWidget> WidgetClass = Widget->GetClass();
    if (!DoesWidgetExist(WidgetClass)) return;

    // 비활성화
    DeactivateWidget(Widget);

    // 등록 해제
    WidgetMap.Remove(WidgetClass);
}

bool UWidgetManagerSubsystem::IsActive(UUserWidget* Widget)
{
    if (!Widget) return false;

    // TODO 인터페이스

    if (auto ActivatableWidget = Cast<UCommonActivatableWidget>(Widget))
    {
        return ActivatableWidget->IsActivated();
    }
    else
    {
        return Widget->IsInViewport();
    }
}

void UWidgetManagerSubsystem::ActivateWidget(UUserWidget* Widget)
{
    if (!Widget) return;

    // 활성화 여부 확인
    if (IsActive(Widget)) return;

    // 활성화
    if (auto ActivatableWidget = Cast<UCommonActivatableWidget>(Widget))
    {
        ActivatableWidget->ActivateWidget();
    }
    else if (!Widget->IsInViewport())
    {
        Widget->AddToViewport();
    }

    // TODO 인터페이스
}

void UWidgetManagerSubsystem::DeactivateWidget(UUserWidget* Widget)
{
    if (!Widget) return;

    // 활성화 여부 확인
    if (!IsActive(Widget)) return;

    // 비활성화
    if (auto ActivatableWidget = Cast<UCommonActivatableWidget>(Widget))
    {
        ActivatableWidget->DeactivateWidget();
    }
    else if (Widget->IsInViewport())
    {
        Widget->RemoveFromParent();
    }

    // TODO 인터페이스
}
