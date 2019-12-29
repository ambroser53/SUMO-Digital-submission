// Ambrose Robinson

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/**
 * Grabber class responsible for the picking up, holding and dropping of physics objects in the game world
 *  Is attached to the player controller
 * 	Private uproperty reach determines the reaching distance of the player
 */
class FINALGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	UPROPERTY(VisibleAnywhere)
		float Reach = 200.f;

	//UPROPERTY(EditDefaultsOnly)
	//	APointLight* TheKeyActor;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	//look for attached physics handler
	void FindPhysHandComponent(FString);

	//Find (assumed) attached input component
	void SetupInputComponent(FString);

	FHitResult GetFirstPhysicsBodyInReach() const;

	//Ray-cast and grab whats in reach
	void Grab();
	//called when grab is released
	void Release();
	
};
