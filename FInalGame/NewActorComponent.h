// Ambrose Robinson

#pragma once

#include "Components/ActorComponent.h"
#include "NewActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/**
 * This class is assigned to the player controller and sets all their powers
 * (i.e. ancient vision) assigning them to input components
 */
class FINALGAME_API UNewActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNewActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void SetupInputComponent(FString);

	void TurnDecalsOn();

	void TurnDecalsOff();




private:
	float Reach = 200.f;
	UInputComponent* InputComponent = nullptr;
	void AncientVision();
	void AncientVisionRelease();
	
};
