// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetClassList.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FWidgetClassList
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSubclassOf<UUserWidget>> List;
};
