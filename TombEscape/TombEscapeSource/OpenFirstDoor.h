// Ambrose Robinson

#pragma once

#include "Components/ActorComponent.h"
#include "OpenFirstDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenFirstDoor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALGAME_API UOpenFirstDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenFirstDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void IsKeyActorInBrick();

	UPROPERTY(BlueprintAssignable)
		FOpenFirstDoor OpenFirstDoor;

private:

	//these member variables are set at the beginning of play
	AActor* KeyActor;
	ATriggerVolume* BrickTrigger;

	//current actor in the brick trigger
	FString ActorInBrickTrigger;
};

