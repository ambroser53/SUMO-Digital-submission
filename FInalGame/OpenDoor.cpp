// Ambrose Robinson

#include "FInalGame.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//iterate through all trigger volumes and set them to member variables
	for (TObjectIterator<ATriggerVolume> Itr; Itr; ++Itr)
	{
		ATriggerVolume *TriggerVolume = *Itr;
		if (TriggerVolume->GetName() == "RedLight")
		{
			RedLight = TriggerVolume;
		}
		if (TriggerVolume->GetName() == "BlueLight")
		{
			BlueLight = TriggerVolume;
		}
		if (TriggerVolume->GetName() == "GreenLight")
		{
			GreenLight = TriggerVolume;
		}
	}
}

void UOpenDoor::OpenDoor()
{
	OnOpenRequest.Broadcast();
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//if all trigger volumes have been set
	if (RedLight && BlueLight && GreenLight) {
		//get the actor inside each light
		FString ActorInBlueLight = GetActorInBlueLight();
		FString ActorInRedLight = GetActorInRedLight();
		FString ActorInGreenLight = GetActorInGreenLight();

		//if all of them are correct - open the door
		if (ActorInBlueLight == GreenCrystal &&
			ActorInRedLight == BlueCrystal &&
			ActorInGreenLight == RedCrystal)
		{
			OpenDoor();
		}
	}
}


/// Each pedestal trigger volume has a large area, when items are placed on the pedestal they are overlapping
/// These functions get the actor currently in each of these spaces

/// Gets the actor in the blue light
/// @return the string name of the actor found
FString UOpenDoor::GetActorInBlueLight()
{
	TArray<AActor*> ActorsInBlueLight;
	BlueLight->GetOverlappingActors(ActorsInBlueLight);  //stores actors in the array

	FString ActorInBlueLight;
	for (auto& Iterator : ActorsInBlueLight) {
		ActorInBlueLight = Iterator->GetName();
	}
	return ActorInBlueLight;
}

/// Gets the actor in the red light
/// @return the string name of the actor found
FString UOpenDoor::GetActorInRedLight()
{
	TArray<AActor*> ActorsInRedLight;
	RedLight->GetOverlappingActors(ActorsInRedLight);	//stores actors in the array

	FString ActorInRedLight;
	for (auto& Iterator : ActorsInRedLight) {
		ActorInRedLight = Iterator->GetName();
	}
	return ActorInRedLight;
}

/// Gets the actor in the green light
/// @return the string name of the actor found
FString UOpenDoor::GetActorInGreenLight()
{
	TArray<AActor*> ActorsInGreenLight;
	GreenLight->GetOverlappingActors(ActorsInGreenLight);		//stores actors in the array

	FString ActorInGreenLight;
	for (auto& Iterator : ActorsInGreenLight) {
		ActorInGreenLight = Iterator->GetName();
	}
	return ActorInGreenLight;
}