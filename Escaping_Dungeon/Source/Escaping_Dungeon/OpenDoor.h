// Eren Taskin 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPING_DUNGEON_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void FindAudioComponent(); 
	void FindVolume();
	// float TotalMassOfActors() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;
	bool SoundPlayed;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* Volume = nullptr;
	
	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens = nullptr;

	UPROPERTY(EditAnywhere)
		float OpenAngle = -90.f;

	UPROPERTY(EditAnyWhere)
		float DoorOpenSpeed;

	UPROPERTY(EditAnyWhere)
		float DoorCloseSpeed;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.5f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};
