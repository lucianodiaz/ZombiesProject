// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RTSUIInterfaces.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URTSUIInterfaces : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZOMBIESPROJECT_API IRTSUIInterfaces
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="UI")
	void OnShow();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="UI")
	void OnHide();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="UI")
	void SetActor(AActor* Owner);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="UI")
	void OnAction();
};
