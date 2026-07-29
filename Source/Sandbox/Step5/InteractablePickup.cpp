// Fill out your copyright notice in the Description page of Project Settings.

#include "Step5/InteractablePickup.h"

AInteractablePickup::AInteractablePickup()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = MeshComponent;

}

void AInteractablePickup::Interact_Implementation(AActor* InteractorActor)
{
	// apply effect
	UE_LOG(LogTemp, Log, TEXT("Player %s picked up %s"),
		IsValid(InteractorActor) ? *InteractorActor->GetName() : TEXT("Unknown"),
		*ItemName.ToString());

	// end of lifecycle
	Destroy();
}

FText AInteractablePickup::GetInteractText_Implementation() const
{
	return FText::Format(NSLOCTEXT("InteractionUI", "PickupKeyFormat", "Pick up {0}"), ItemName);
}