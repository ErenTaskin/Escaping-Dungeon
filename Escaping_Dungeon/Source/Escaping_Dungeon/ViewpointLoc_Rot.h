// Eren Taskin 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViewpointLoc_Rot.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPING_DUNGEON_API UViewpointLoc_Rot : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UViewpointLoc_Rot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
