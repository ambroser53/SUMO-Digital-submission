// Ambrose Robinson

#include "FInalGame.h"
#include "OpenFirstDoor.h"


// Sets default values for this component's properties
UOpenFirstDoor::UOpenFirstDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenFirstDoor::BeginPlay()
{
	Super::BeginPlay();

	//iterate through actors and get the key actor
	for (TObjectIterator<AActor> Itr; Itr; ++Itr)
	{
		AActor *TheKeyActor = *Itr;
		if (TheKeyActor->GetName() == "KeyActor")
		{
			//set the member variable
			KeyActor = TheKeyActor;
		}
	}

	//iterate through all the trigger volumes and get the brick trigger
	for (TObjectIterator<ATriggerVolume> Itr; Itr; ++Itr)
	{
		ATriggerVolume *TriggerVolume = *Itr;
		if (TriggerVolume->GetName() == "BrickTrigger")
		{
			//set the member variable
			BrickTrigger = TriggerVolume;
		}
	}
	
}


// Called every frame
void UOpenFirstDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	IsKeyActorInBrick();
}

/// Called every frame and iterates through the actors in the brick trigger
/// and sees if any of them are the key actor (in which case it will open the door)
void UOpenFirstDoor::IsKeyActorInBrick()
{

	TArray<AActor*> ActorsInBrickTrigger;
	BrickTrigger->GetOverlappingActors(ActorsInBrickTrigger);		//stores actors in the array

	for (auto& Iterator : ActorsInBrickTrigger)
	{
		ActorInBrickTrigger = Iterator->GetName();
	}

	// if the line trace end object is inside the button trigger volume
	if (ActorInBrickTrigger == KeyActor->GetName()) {
		//activate the open door event
		OpenFirstDoor.Broadcast();
	}
}
