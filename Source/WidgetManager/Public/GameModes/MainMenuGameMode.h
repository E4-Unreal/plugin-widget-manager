// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API AMainMenuGameMode : public AGameModeBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UUserWidget>> DefaultWidgets;

protected:
    virtual void BeginPlay() override;
    virtual void Destroyed() override;
};
