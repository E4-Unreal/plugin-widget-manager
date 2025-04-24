// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WidgetManagerPlayerController.generated.h"

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API AWidgetManagerPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UUserWidget>> DefaultWidgets;

protected:
    virtual void BeginPlay() override;
    virtual void Destroyed() override;
};
