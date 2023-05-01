// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RTSPlayerController.h"

#include "Core/RTSCamera.h"
#include "Interfaces/RTSInteractable.h"
#include "Kismet/KismetSystemLibrary.h"

ARTSPlayerController::ARTSPlayerController()
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;
	bEnableTouchEvents = true;
}
void ARTSPlayerController::UISelection_Implementation(AActor* Actor)
{
	if(ActorSelected != Actor)
	{
		AActor* LastActorSelected = ActorSelected;
			
		ActorSelected = Actor;

			
		const IRTSInteractable* LastInterface = Cast<IRTSInteractable>(LastActorSelected);
		if(LastInterface)
		{
			LastInterface->Execute_OnDeselect(LastActorSelected);
			LastActorSelected = nullptr;
		}
		else
		{
			LastActorSelected = nullptr;
		}
			
		const IRTSInteractable* Interface = Cast<IRTSInteractable>(ActorSelected);
		if(Interface)
		{
			Interface->Execute_OnSelect(ActorSelected);
			UE_LOG(LogTemp,Display,TEXT("The Actor's name is %s"),*ActorSelected->GetName());
			UKismetSystemLibrary::PrintString(GetWorld(),ActorSelected->GetName());
			PlayerCam->SetActorLocation(FVector(ActorSelected->GetActorLocation().X,ActorSelected->GetActorLocation().Y,PlayerCam->GetActorLocation().Z));
		}
		else
		{
			ClearSelection();
		}
			
	}
	else
	{
		ClearSelection();
	}
}
void ARTSPlayerController::Selection()
{
	FHitResult HitResult;
	const bool bIsHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1,true,HitResult);
	if(bIsHit)
	{
		if(ActorSelected != HitResult.GetActor())
		{
			AActor* LastActorSelected = ActorSelected;
			
			ActorSelected = HitResult.GetActor();

			
			const IRTSInteractable* LastInterface = Cast<IRTSInteractable>(LastActorSelected);
			if(LastInterface)
			{
				LastInterface->Execute_OnDeselect(LastActorSelected);
				LastActorSelected = nullptr;
			}
			else
			{
				LastActorSelected = nullptr;
			}
			
			const IRTSInteractable* Interface = Cast<IRTSInteractable>(ActorSelected);
			if(Interface)
			{
				Interface->Execute_OnSelect(ActorSelected);
				UE_LOG(LogTemp,Display,TEXT("The Actor's name is %s"),*ActorSelected->GetName());
				UKismetSystemLibrary::PrintString(GetWorld(),ActorSelected->GetName());

				PlayerCam->SetActorLocation(FVector(ActorSelected->GetActorLocation().X,ActorSelected->GetActorLocation().Y,PlayerCam->GetActorLocation().Z));
			}
			else
			{
				ClearSelection();
			}
			
		}
		else
		{
			ClearSelection();
		}
	}
	else
	{
		ClearSelection();
	}
}

void ARTSPlayerController::Action()
{
	if(ActorSelected)
	{
		FHitResult HitResult;
		const bool bIsHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1,true,HitResult);
		if(bIsHit)
		{
			const IRTSInteractable* Interface = Cast<IRTSInteractable>(ActorSelected);
			if(Interface)
			{
				TargetLocation = HitResult.Location;
				Interface->Execute_OnAction(ActorSelected);
				UKismetSystemLibrary::PrintString(GetWorld(),"Action");
			}
		}
	}
}

void ARTSPlayerController::ClearSelection()
{
	const IRTSInteractable* Interface = Cast<IRTSInteractable>(ActorSelected);
	
	if(Interface)
	{
		Interface->Execute_OnDeselect(ActorSelected);
	}
	ActorSelected = nullptr;
}

FVector ARTSPlayerController::GetTargetLocationAI() const
{
	return TargetLocation;
}

void ARTSPlayerController::Wheel(float AxisValue) const
{
	if(PlayerCam)
	{
		PlayerCam->ZoomingCamera(AxisValue);
	}
}


void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Zooming",this,FInputAxisHandlerSignature::TUObjectMethodDelegate<ARTSPlayerController>::FMethodPtr(&ARTSPlayerController::Wheel));

	InputComponent->BindAction("Selection",EInputEvent::IE_Pressed,this,&ARTSPlayerController::Selection);
	InputComponent->BindAction("Action",EInputEvent::IE_Pressed,this,&ARTSPlayerController::Action);
}
