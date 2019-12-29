// Ambrose Robinson

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/**
 * This class is for opening the second door and is assigned to the door actor
 */
class FINALGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/// Starts slow opening animation
	void OpenDoor();

	//get the actors in each of the coloured trigger volumes
	FString GetActorInBlueLight();

	FString GetActorInGreenLight();

	FString GetActorInRedLight();

	UPROPERTY(BlueprintAssignable)
		FOnOpenRequest OnOpenRequest;


private:

	UPROPERTY(EditAnywhere)
		FString BlueCrystal = "z_BlueCrystal_82";

	UPROPERTY(EditAnywhere)
		FString RedCrystal = "z_RedCrystal_83";

	UPROPERTY(EditAnywhere)
		FString GreenCrystal = "z_GreenCrystal_87";

	//trigger volume member variables
	ATriggerVolume* RedLight;

	ATriggerVolume* BlueLight;

	ATriggerVolume* GreenLight;
	
};
