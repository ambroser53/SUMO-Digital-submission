// Ambrose Robinson

#include "FInalGame.h"
#include "NewActorComponent.h"


// Sets default values for this component's properties
UNewActorComponent::UNewActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNewActorComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TObjectIterator<UDecalComponent> Itr; Itr; ++Itr)
	{
		UDecalComponent *Actor = *Itr;
		UE_LOG(LogTemp, Warning, TEXT("found decal: %s"), *Actor->GetName());
		Actor->SetHiddenInGame(true);			//sets found Decals as Hidden
	}

	FString ObjectName = GetOwner()->GetName();

	SetupInputComponent(ObjectName);
	
}


// Called every frame
void UNewActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

/// This sets up all the input components binding the actions to the functions
/// @param ObjectName is a string of the object, used in error
void UNewActorComponent::SetupInputComponent(FString ObjectName) {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		///Bind input action
		InputComponent->BindAction("AncientVision", IE_Pressed, this, &UNewActorComponent::AncientVision);
		///Bind Release input action
		InputComponent->BindAction("AncientVision", IE_Released, this, &UNewActorComponent::AncientVisionRelease);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No Input Component found on %s"), *ObjectName);
	}
}

// Ancient vision works by, when a button is pressed, all decals can be seen
// But when the button is released the decals are made invisible again

/// Called when the ancient vision button is pressed
void UNewActorComponent::AncientVision()
{
	UE_LOG(LogTemp, Warning, TEXT("Ancient vision activated"));

	TurnDecalsOn();
}

/// Called when the ancient vision button is released
void UNewActorComponent::AncientVisionRelease()
{
	UE_LOG(LogTemp, Warning, TEXT("Ancient vision off"));

	TurnDecalsOff();
}

/// Iterates through all the decals in the level and turns them on
void UNewActorComponent::TurnDecalsOn()
{
	for (TObjectIterator<UDecalComponent> Itr; Itr; ++Itr)
	{
		UDecalComponent *Actor = *Itr;
		UE_LOG(LogTemp, Warning, TEXT("found decal: %s"), *Actor->GetName());

		Actor->SetHiddenInGame(false);			//sets found Decals as NOT Hidden
	}
}

/// Iterates through all the decals in the level and turns them off
void UNewActorComponent::TurnDecalsOff()
{
	for (TObjectIterator<UDecalComponent> Itr; Itr; ++Itr)
	{
		UDecalComponent *Actor = *Itr;
		UE_LOG(LogTemp, Warning, TEXT("found decal: %s"), *Actor->GetName());
		Actor->SetHiddenInGame(true);			//sets found Decals as Hidden
	}
}