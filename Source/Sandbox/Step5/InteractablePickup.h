// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "InteractablePickup.generated.h"

UCLASS()
class SANDBOX_API AInteractablePickup : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AInteractablePickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	FText ItemName = NSLOCTEXT("InteractionUI", "DefaultItemName", "Item");;

	// InteractableInterface
	virtual void Interact_Implementation(AActor* InteractorActor) override;
	virtual FText GetInteractText_Implementation() const override;
};
