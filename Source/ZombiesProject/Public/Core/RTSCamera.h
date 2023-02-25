// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"

#include "RTSCamera.generated.h"




class UCameraComponent;
UCLASS()
class ZOMBIESPROJECT_API ARTSCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTSCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// void UpLeft(float Margin,float ScaleFactor);
	// void DownRight();
	void MoveUpCamera() const;
	void MoveDownCamera()const;
	void MoveRightCamera() const;

	UFUNCTION()
	float GetCameraSpeed(const float ScaleFactor) const;
	
	//Variables
	
	UPROPERTY(EditAnywhere)
	float VelocityMultiplier = 10;
	
	UPROPERTY()
	APlayerController* PC;
	
	UPROPERTY()
	float CamSpeed = 4;

	UPROPERTY()
	float ZoomFactor = 5;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Components
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootScene;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;
	
	void ZoomingCamera(const float AxisValue);
	
};
