// Fill out your copyright notice in the Description page of Project Settings.


#include "Step5/InteractableDoor.h"
#include "Net/UnrealNetwork.h"

AInteractableDoor::AInteractableDoor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	HingeComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Hinge"));
	HingeComponent->SetMobility(EComponentMobility::Movable);
	RootComponent = HingeComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetMobility(EComponentMobility::Movable);

}

void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableDoor::Interact_Implementation(AActor* InteractorActor)
{
	if (!HingeComponent) return;

	bIsOpen = !bIsOpen;

	OnRep_IsOpen();

	UE_LOG(LogTemp, Warning, TEXT("Door state changed by player %s. IsOpen: %d"),
		IsValid(InteractorActor) ? *InteractorActor->GetName() : TEXT("Unknown"), bIsOpen);
}

FText AInteractableDoor::GetInteractText_Implementation() const
{
	if (bIsOpen)
	{
		return NSLOCTEXT("InteractionUI", "CloseDoorKey", "Close the door");
	}
	return NSLOCTEXT("InteractionUI", "OpenDoorKey", "Open the door");
}

void AInteractableDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AInteractableDoor, bIsOpen);
}

void AInteractableDoor::OnRep_IsOpen()
{
	float TargetYaw = bIsOpen ? 90.f : 0.f;
	HingeComponent->SetRelativeRotation(FRotator(0.f, TargetYaw, 0.f));
}