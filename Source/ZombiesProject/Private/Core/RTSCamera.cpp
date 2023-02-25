// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RTSCamera.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/Widget.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARTSCamera::ARTSCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootScene);
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->SetRelativeRotation(FRotator(-60,0,0));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ARTSCamera::BeginPlay()
{
	Super::BeginPlay();
	PC = UGameplayStatics::GetPlayerController(GetWorld(),0);

	PC->SetViewTargetWithBlend(this);
}

// Called every frame
void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveUpCamera();
	MoveDownCamera();
	MoveRightCamera();
}

float ARTSCamera::GetCameraSpeed(const float ScaleFactor) const
{
	return ((UKismetMathLibrary::NormalizeToRange(SpringArmComp->TargetArmLength,1000,2000) * VelocityMultiplier)+40) * ScaleFactor;
}

void ARTSCamera::MoveUpCamera() const
{
	const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) * UWidgetLayoutLibrary::GetViewportScale(GetWorld()) ;
	const float ViewPortSizeY = UWidgetLayoutLibrary::GetViewportSize(GetWorld()).Y;
	//UP
	
	 const float NormalizedScale = UKismetMathLibrary::Clamp(UKismetMathLibrary::NormalizeToRange(MousePosition.Y,0,ViewPortSizeY* 0.02f),0,1) -1;

	RootScene->AddRelativeLocation(FVector(GetCameraSpeed(-1),0,0) * NormalizedScale);
	//End UP
	
}

void ARTSCamera::MoveDownCamera() const
{
	const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) * UWidgetLayoutLibrary::GetViewportScale(GetWorld()) ;
	const float ViewPortSizeY = UWidgetLayoutLibrary::GetViewportSize(GetWorld()).Y;

	//MoveDownCamera
	const float NormalizedScale = UKismetMathLibrary::Clamp(UKismetMathLibrary::NormalizeToRange(MousePosition.Y,ViewPortSizeY*0.95f,ViewPortSizeY*0.02),0,1);

	RootScene->AddRelativeLocation(FVector(GetCameraSpeed(-1),0,0) * NormalizedScale);
}

void ARTSCamera::MoveRightCamera() const
{
	const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) * UWidgetLayoutLibrary::GetViewportScale(GetWorld()) ;
	const float ViewPortSizeX = UWidgetLayoutLibrary::GetViewportSize(GetWorld()).X;
	//LEFT
	
	float NormalizedScale = UKismetMathLibrary::Clamp(UKismetMathLibrary::NormalizeToRange(MousePosition.X,0,ViewPortSizeX* 0.02f),0,1) -1;

	RootScene->AddRelativeLocation(FVector(0,GetCameraSpeed(1),0) * NormalizedScale);
	//End LEFT

	
	//RIGHT
	NormalizedScale = UKismetMathLibrary::Clamp(UKismetMathLibrary::NormalizeToRange(MousePosition.X,ViewPortSizeX*0.95f,ViewPortSizeX*0.05),0,1);

	RootScene->AddRelativeLocation(FVector(0,GetCameraSpeed(1),0) * NormalizedScale);
	//End RIGHT
}

void ARTSCamera::ZoomingCamera(const float AxisValue)
{
	ZoomFactor = UKismetMathLibrary::Clamp(AxisValue * -1.0f + ZoomFactor,0,10);

	SpringArmComp->TargetArmLength = UKismetMathLibrary::Clamp(ZoomFactor * 200 + 1000,600,1700);
}

