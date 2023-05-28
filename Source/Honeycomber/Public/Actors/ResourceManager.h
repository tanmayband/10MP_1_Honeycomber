// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums.h"
#include "ResourceManager.generated.h"

class ABeehive;
class AResourceStorage;
class AMoneyStorage;

DECLARE_DELEGATE_TwoParams(FUpdatedResourceSignature, EResourceType resourceType, int32 resourceAmount)

UCLASS()
class HONEYCOMBER_API AResourceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceManager();
	int32 TryAddingResources(EResourceType resourceType, int32 numResources);
	bool HaveEnoughResources(EResourceType resourceType, int32 numResources);
	void AddMoney(int32 numMoney);
	TMap<EResourceType, uint8> GetResourcesData() { return ResourcesData; };
	FUpdatedResourceSignature OnUpdatedResourceDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TArray<ABeehive*> Beehives;
	UPROPERTY(EditAnywhere)
		TArray<AResourceStorage*> HoneyStores;
	UPROPERTY(EditAnywhere)
		TArray<AResourceStorage*> WaxStores;
	UPROPERTY(EditAnywhere)
		AMoneyStorage* MoneyStore;

	TMap<EResourceType, uint8> ResourcesData = {
		{EResourceType::HONEY, 0},
		{EResourceType::WAX, 0},
		{EResourceType::ITEM, 0}
	};
};