// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
    TObjectPtr<UUserWidget> MainWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TArray<TSubclassOf<UUserWidget>> SubWidgets;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    uint32 bShowMouseCursor:1;

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE UUserWidget* GetOrCreateWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);

protected:
    UFUNCTION(BlueprintPure)
    APlayerController* GetPlayerController() const;

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* RegisterWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void UnRegisterWidget(TSubclassOf<UUserWidget> WidgetClass);

    virtual void SetShowMouseCursor(bool bNewShowMouseCursor);
};
