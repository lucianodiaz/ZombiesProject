// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FResourceInfo.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/RTSGMInterface.h"
#include "RTSCityBuilderGM.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESPROJECT_API ARTSCityBuilderGM : public AGameModeBase, public IRTSGMInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int Food;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int MaterialConstruction;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Info")
	TArray<FResourceInfo> ResourcesArray;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Info")
	TArray<FCharacterInfo> AvatarInfoArray;
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GameMode")
	void AddResources(EResourceType ResourceType, int Amount);
	
	virtual void AddResources_Implementation(EResourceType ResourceType, int Amount);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GameMode")
	void GetResources(TArray<FResourceInfo>&Resources);

	virtual void GetResources_Implementation(TArray<FResourceInfo>&Resources);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GameMode")
	void GetCharacterInfo(FCharacterInfo& CharacterInfo);

	virtual void GetCharacterInfo_Implementation(FCharacterInfo& CharacterInfo);
};
