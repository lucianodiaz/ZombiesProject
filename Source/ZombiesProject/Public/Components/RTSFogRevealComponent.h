// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RTSFogRevealComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIESPROJECT_API URTSFogRevealComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTSFogRevealComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UMaterialInterface* FogMaterialInterface;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UMaterialInterface* FogRevealMaterialInterface;

	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* FogMaterialInstance;
	
	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* FogRevealMaterialInstance;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UTextureRenderTarget2D* FogTextureRender;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UTextureRenderTarget2D* FogRevealTextureRender;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float SizeReveal;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float SizeInner;
};
