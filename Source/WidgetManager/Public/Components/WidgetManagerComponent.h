// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/WidgetType.h"
#include "WidgetManagerComponent.generated.h"

/**
 * 위젯 풀링 기능을 지원하는 액터 컴포넌트로,
 * PlayerController 혹은 Pawn 클래스에서만 사용 가능합니다.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class WIDGETMANAGER_API UWidgetManagerComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>> WidgetMap;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TSubclassOf<UUserWidget> MainWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TArray<TSubclassOf<UUserWidget>> SubWidgets;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    uint32 bShowMouseCursor:1;

public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure)
    FORCEINLINE UUserWidget* GetOrCreateWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ShowWidget(TSubclassOf<UUserWidget> WidgetClass, EWidgetType WidgetType = EWidgetType::HUD);

    UFUNCTION(BlueprintCallable)
    virtual void HideWidget(TSubclassOf<UUserWidget> WidgetClass, EWidgetType WidgetType = EWidgetType::HUD);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass, EWidgetType WidgetType = EWidgetType::HUD);

protected:
    virtual void ShowMainWidget(TSubclassOf<UUserWidget> WidgetClass);
    virtual void HideMainWidget(TSubclassOf<UUserWidget> WidgetClass);
    virtual void ToggleMainWidget(TSubclassOf<UUserWidget> WidgetClass);

    virtual void ShowSubWidget(TSubclassOf<UUserWidget> WidgetClass);
    virtual void HideSubWidget(TSubclassOf<UUserWidget> WidgetClass);
    virtual void ToggleSubWidget(TSubclassOf<UUserWidget> WidgetClass);

    virtual bool ShowWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);
    virtual bool HideWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);
    virtual void ToggleWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);

    virtual bool IsInViewport(TSubclassOf<UUserWidget> WidgetClass) const;

    UFUNCTION(BlueprintPure)
    APlayerController* GetPlayerController() const;

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* RegisterWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void UnRegisterWidget(TSubclassOf<UUserWidget> WidgetClass);

    virtual void SetShowMouseCursor(bool bNewShowMouseCursor);
};
