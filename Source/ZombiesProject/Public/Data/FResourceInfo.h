// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "UObject/ObjectMacros.h"
#include "EResourceType.h"
#include "FResourceInfo.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct ZOMBIESPROJECT_API FResourceInfo
{
	GENERATED_BODY()
	
	FResourceInfo();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FSlateBrush Thumbnail{};
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString ResourceName{};

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	EResourceType ResourceType;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int Count{};
};
