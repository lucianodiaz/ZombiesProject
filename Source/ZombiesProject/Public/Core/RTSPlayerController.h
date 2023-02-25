// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

class ARTSCamera;
/**	
 * 
 */
UCLASS()
class ZOMBIESPROJECT_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARTSPlayerController();

protected:
	virtual void SetupInputComponent() override;

	void Wheel(float AxisValue)const;

	void Selection();

	void Action();
	
	void ClearSelection();

	UPROPERTY()
	AActor* ActorSelected;

	UPROPERTY(BlueprintReadOnly)
	FVector TargetLocation;
public:
	UPROPERTY(BlueprintReadWrite)
	ARTSCamera* PlayerCam;

	UFUNCTION(BlueprintGetter,BlueprintCallable)
	virtual FVector GetTargetLocationAI()const;
	
};
