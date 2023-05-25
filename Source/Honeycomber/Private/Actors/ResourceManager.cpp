// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ResourceManager.h"
#include "Actors/Interactables//Beehive.h"
#include "Actors/ResourceStorage.h"

// Sets default values
AResourceManager::AResourceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AResourceManager::BeginPlay()
{
	Super::BeginPlay();
	for (ABeehive* beehive : Beehives)
	{
		beehive->ExtractedResourceDelegate.BindUObject(this, &AResourceManager::TryAddingResources);
	}
}

int32 AResourceManager::TryAddingResources(EResourceType resourceType, int32 numResources)
{
	int32 resourcesToAdd = numResources;
	TArray<AResourceStorage*> resourcesToCheck;
	switch (resourceType)
	{
		case EResourceType::HONEY:
		{
			resourcesToCheck = HoneyStores;
			break;
		}
		case EResourceType::WAX:
		{
			resourcesToCheck = WaxStores;
			break;
		}
	}

	for (AResourceStorage* storage : resourcesToCheck)
	{
		int32 spaceAvailable = storage->GetAvailableSpace();
		int32 resourcesCanBeFit = FMath::Min(spaceAvailable, numResources);
		storage->ModifyResourceAmount(resourcesCanBeFit);
		numResources -= resourcesCanBeFit;
	}

	// how many added eventually?
	return resourcesToAdd - numResources;
}
