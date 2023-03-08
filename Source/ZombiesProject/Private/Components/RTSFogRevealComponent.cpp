// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RTSFogRevealComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"

// Sets default values for this component's properties
URTSFogRevealComponent::URTSFogRevealComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SizeReveal = 0.05f;
	SizeInner = 0.05f;
	// ...
}


// Called when the game starts
void URTSFogRevealComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(FogMaterialInterface)
	{
		FogMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),FogMaterialInterface);

		FogMaterialInstance->SetScalarParameterValue(FName(TEXT("Size")),SizeReveal);
	}
	if(FogRevealMaterialInterface)
	{
		FogRevealMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),FogRevealMaterialInterface);
		FogRevealMaterialInstance->SetScalarParameterValue(FName(TEXT("Size")),SizeInner);
	}

	UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(),FogTextureRender);
	UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(),FogRevealTextureRender);
}


// Called every frame
void URTSFogRevealComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FHitResult HitResult;
	const TArray<AActor*> ActorsToIgnore;
	const FVector Start = GetOwner()->GetActorLocation() + FVector(0.0f,0.0f,500.0f);
	const FVector End = GetOwner()->GetActorLocation() + FVector(0.0f,0.0f,-500.0f);;
	const bool bIsHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(),Start,End,UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1),true,ActorsToIgnore,EDrawDebugTrace::None,HitResult,false); 
	if(bIsHit)
	{
		FVector2D UV;
		UGameplayStatics::FindCollisionUV(HitResult,0,UV);
		const FLinearColor LinearColor = FLinearColor(UV.X,UV.Y,0,0);

		FogMaterialInstance->SetVectorParameterValue(FName(TEXT("Location")),LinearColor);
		FogRevealMaterialInstance->SetVectorParameterValue(FName(TEXT("Location")),LinearColor);
		
		UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(),FogTextureRender,FogMaterialInstance);
		UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(),FogRevealTextureRender,FogRevealMaterialInstance);

		// UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(),FogMaterialInstance,FName(TEXT("Location")),LinearColor));
	}
}

