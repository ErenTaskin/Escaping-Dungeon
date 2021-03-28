// Eren Taskin 2021

#include "ViewpointLoc_Rot.h"
#define OUT

// Sets default values for this component's properties
UViewpointLoc_Rot::UViewpointLoc_Rot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UViewpointLoc_Rot::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UViewpointLoc_Rot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Logging to UE_LOG
	UE_LOG(LogTemp, Warning, TEXT("Viewpoint location is: %s Viewpoint rotation is: %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	);
}