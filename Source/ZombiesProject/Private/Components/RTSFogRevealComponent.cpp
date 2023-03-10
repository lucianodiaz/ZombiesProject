// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RTSFogRevealComponent.h"

#include "Components/SphereComponent.h"
#include "Interfaces/RTSPawnInterfaces.h"
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
	Radius = 200.0f;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// SphereComponent->SetupAttachment(GetOwner()->GetRootComponent());
	SphereComponent->SetSphereRadius(Radius);
	SphereComponent->SetHiddenInGame(false);
	// ...
}


// Called when the game starts
void URTSFogRevealComponent::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&URTSFogRevealComponent::OverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this,&URTSFogRevealComponent::OverlapEnd);
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

	const auto bImpl = UKismetSystemLibrary::DoesImplementInterface(GetOwner(),URTSPawnInterfaces::StaticClass());
	if(bImpl)
	{
		if(!IRTSPawnInterfaces::Execute_IsUserController(GetOwner()))
		{
			SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetOwner()->SetActorHiddenInGame(true);
		}
	}
}


// Called every frame
void URTSFogRevealComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(GetOwner())
	{
		SphereComponent->SetWorldLocation(GetOwner()->GetActorLocation());
		SphereComponent->SetSphereRadius(Radius);
	}
	bool Exec = false;
	const auto bImpl = UKismetSystemLibrary::DoesImplementInterface(GetOwner(),URTSPawnInterfaces::StaticClass());
	if(bImpl)
	{
		Exec = IRTSPawnInterfaces::Execute_IsUserController(GetOwner());
	}
	if(Exec)
	{
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

	
}

void URTSFogRevealComponent::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	const auto bImpl = UKismetSystemLibrary::DoesImplementInterface(OtherActor,URTSPawnInterfaces::StaticClass());
	if(bImpl)
	{
		if(!IRTSPawnInterfaces::Execute_IsUserController(OtherActor))
		{
			OtherActor->SetActorHiddenInGame(false);
		}
	}
	
}

void URTSFogRevealComponent::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const auto bImpl = UKismetSystemLibrary::DoesImplementInterface(OtherActor,URTSPawnInterfaces::StaticClass());
	if(bImpl)
	{
		if(!IRTSPawnInterfaces::Execute_IsUserController(OtherActor))
		{
			OtherActor->SetActorHiddenInGame(true);
		}
	}
}

