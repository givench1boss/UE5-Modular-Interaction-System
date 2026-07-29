// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"


UInteractorComponent::UInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}


void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			TraceTimerHandle,
			this,
			&UInteractorComponent::PerformTrace,
			TraceInterval,
			true
		);
	}

	PerformTrace();
}


void UInteractorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TraceTimerHandle);
	}

	Super::EndPlay(EndPlayReason);
}


void UInteractorComponent::PerformTrace()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!IsValid(OwnerPawn)) return;

	AController* Controller = OwnerPawn->GetController();
	if (!IsValid(Controller)) return;

	if (!Controller->IsLocalController()) return;

	// I implemented this for an FPS project; for a TPS project, the ray needs to be cast from the character
	FVector TraceStart;
	FRotator TraceRotation;
	OwnerPawn->GetActorEyesViewPoint(TraceStart, TraceRotation);
	
	FVector TraceDirection = TraceRotation.Vector();
	FVector TraceEnd = TraceStart + (TraceDirection * TraceDistance);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	QueryParams.bTraceComplex = false;

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		TraceStart, 
		TraceEnd, 
		TraceChannel, 
		QueryParams
	);
	
	AActor* HitActor = HitResult.GetActor();
	if (bHit && HitActor && HitActor->Implements<UInteractableInterface>())
	{
		if (HitActor != CurrentInteractable)
		{
			CurrentInteractable = HitActor;
			OnInteractableTargetChanged.Broadcast(CurrentInteractable);
		}
	}
	else
	{
		if (CurrentInteractable != nullptr)
		{
			CurrentInteractable = nullptr;
			OnInteractableTargetChanged.Broadcast(nullptr);
		}
	}
}


void UInteractorComponent::TryInteract()
{

	if (!IsValid(CurrentInteractable)) return;

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!IsValid(OwnerPawn)) return;

	AActor* Target = CurrentInteractable;

	if (OwnerPawn->HasAuthority())
	{
		// BlueprintNativeEvent = Execute_NameOfFunction (instead of CurrentInteractable->Interact())
		IInteractableInterface::Execute_Interact(CurrentInteractable, OwnerPawn);

		// if object died (Pickup)
		if (!IsValid(Target))
		{
			CurrentInteractable = nullptr;
			OnInteractableTargetChanged.Broadcast(nullptr);
		}
	}
	else
	{
		ServerTryInteract(CurrentInteractable);

		CurrentInteractable = nullptr;
		OnInteractableTargetChanged.Broadcast(nullptr);
	}
}


void UInteractorComponent::ServerTryInteract_Implementation(AActor* TargetActor)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (IsValid(OwnerPawn) && IsValid(TargetActor) && TargetActor->Implements<UInteractableInterface>())
	{
		float DistanceSq = FVector::DistSquared(OwnerPawn->GetActorLocation(), TargetActor->GetActorLocation());
		float MaxAllowableDistance = TraceDistance + 50.f;

		if (DistanceSq <= (MaxAllowableDistance * MaxAllowableDistance))
		{
			IInteractableInterface::Execute_Interact(TargetActor, OwnerPawn);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Interaction rejected: Player %s is too far from %s"), *OwnerPawn->GetName(), *TargetActor->GetName());
		}
	}
}