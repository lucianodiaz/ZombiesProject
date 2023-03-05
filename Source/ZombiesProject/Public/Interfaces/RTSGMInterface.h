// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/EResourceType.h"
#include "Data/FCharacterInfo.h"
#include "Data/FResourceInfo.h"
#include "UObject/Interface.h"
#include "RTSGMInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URTSGMInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZOMBIESPROJECT_API IRTSGMInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GameMode")
	void AddResources(EResourceType ResourceType, int Amount);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GameMode")
	void GetResources(TArray<FResourceInfo>&Resources);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GameMode")
	void GetCharacterInfo(FCharacterInfo& CharacterInfo);
};
