// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RTSCityBuilderGM.h"


void ARTSCityBuilderGM::AddResources_Implementation(EResourceType ResourceType, int Amount)
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
