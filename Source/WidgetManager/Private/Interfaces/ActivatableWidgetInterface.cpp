// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/ActivatableWidgetInterface.h"

#include "Logging.h"

// Add default functionality here for any IActivatableWidgetInterface functions that are not pure virtual.
bool IActivatableWidgetInterface::IsActive_Implementation()
{
    LOG_TODO_INTERFACE

    return false;
}

void IActivatableWidgetInterface::Activate_Implementation()
{
    LOG_TODO_INTERFACE
}

void IActivatableWidgetInterface::Deactivate_Implementation()
{
    LOG_TODO_INTERFACE
}

