// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Food	UMETA(DisplayName="Food"),
	Materials	UMETA(DisplayName="Materials"),
	People	UMETA(DisplayName="People")
};