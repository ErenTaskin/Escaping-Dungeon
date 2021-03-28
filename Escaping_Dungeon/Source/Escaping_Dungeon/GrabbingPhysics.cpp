// Eren Taskin 2021

#include "GrabbingPhysics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UGrabbingPhysics::UGrabbingPhysics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabbingPhysics::BeginPlay()
{
	Super::BeginPlay();

	UGrabbingPhysics::CheckPhysicsHandle();
	UGrabbingPhysics::SetupInputComponent();
}

// Called every frame
void UGrabbingPhysics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	PhysicsHandle->SetTargetLocation(LineTraceEnd);
}

void UGrabbingPhysics::CheckPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("The %s do not have any \"PhysicsHandleComponent\" in it. Add PhysicsHandleComponent."), *GetOwner()->GetName());
	};
}

void UGrabbingPhysics::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabbingPhysics::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabbingPhysics::Release);
	}
}

void UGrabbingPhysics::Grab()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	FHitResult HitResult = UGrabbingPhysics::GetObjectInReach();
	UE_LOG(LogTemp, Warning, TEXT("Grabber is pressed."));
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd
		);
	}
}

void UGrabbingPhysics::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber is released."));
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabbingPhysics::GetObjectInReach()
{
	// Get player viewport
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Getting the intersection with physics objects
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// Checking if we hit any physics objects
	if (Hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.GetActor()->GetName());
	};

	return Hit;
};