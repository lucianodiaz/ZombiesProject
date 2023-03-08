// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RTSCityBuilderGM.h"

#include "Kismet/KismetRenderingLibrary.h"


void ARTSCityBuilderGM::ClearFogReveal_Implementation(UTextureRenderTarget2D* FogRevealTexture)
{
	
	UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(),FogRevealTexture);
}

void ARTSCityBuilderGM::AddResources_Implementation(const EResourceType ResourceType,const int Amount)
{
	IRTSGMInterface::AddResources_Implementation(ResourceType, Amount);

	for(auto& Resources : ResourcesArray)
	{
		if(Resources.ResourceType == ResourceType)
		{
			Resources.Count += Amount;
		}
	}
}

void ARTSCityBuilderGM::GetResources_Implementation(TArray<FResourceInfo>& Resources)
{
	IRTSGMInterface::GetResources_Implementation(Resources);

	Resources = ResourcesArray;
}

void ARTSCityBuilderGM::GetCharacterInfo_Implementation(FCharacterInfo& CharacterInfo)
{
	IRTSGMInterface::GetCharacterInfo_Implementation(CharacterInfo);

	const int32 RandomIndex = FMath::RandRange(0,AvatarInfoArray.Num()-1);

	if(!AvatarInfoArray[RandomIndex].bInUse)
	{
		AvatarInfoArray[RandomIndex].bInUse = true;
		CharacterInfo = AvatarInfoArray[RandomIndex];
	}
	else
	{
		GetCharacterInfo_Implementation(CharacterInfo);
	}
	
}
