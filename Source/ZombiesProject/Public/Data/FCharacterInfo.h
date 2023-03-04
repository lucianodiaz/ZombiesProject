// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Styling/SlateBrush.h"
#include "UObject/ObjectMacros.h"
#include "FCharacterInfo.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct ZOMBIESPROJECT_API FCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()
	
	FCharacterInfo();
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FText Name{};
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FText Genre{};
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FSlateBrush Thumbnail;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bInUse{};
};
