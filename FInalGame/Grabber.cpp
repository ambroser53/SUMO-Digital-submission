// Ambrose Robinson

#include "FInalGame.h"
#include "Grabber.h"

# define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();

	FindPhysHandComponent(ObjectName);
	SetupInputComponent(ObjectName);
	
}


/// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// Get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	///the World and the PlayerController are both structures 
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	///LineTraceEnd is the point at which the player would be picking up the object
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	/// if their is a physics handle attached (i.e. an object is currently grabbed) 
	if (PhysicsHandle->GrabbedComponent)
	{
		///move held object to LineTraceEnd
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

/// Fetches the physics handler component given the object's name
/// @param ObjectName the string name of the object you want the physics handler of
void UGrabber::FindPhysHandComponent(FString ObjectName)
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		///physics handler couldn't be found and print error
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandler Component found on %s"), *ObjectName);
	};
}

/// Binds input components (set actions bound in UEditor) to functions
void UGrabber::SetupInputComponent(FString ObjectName) {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		///Bind Grab input action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		///Bind Release input action
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No Input Component found on %s"), *ObjectName);
	}
}

/// Called on grab input action
///  Grabs the actor within LINE TRACE range and attaches its physics handler
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

	/// LINE TRACE and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	/// if we hit something
	if (ActorHit)
		/// then attach physics handle
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true //allow rotation
		);
}

/** Releases the currently grabbed object
 *  Called on release input action */
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
	// release physics handle
	PhysicsHandle->ReleaseComponent();
}

/** Gets the first actor with a physics handler that it meets
 *  from the player to the line trace end (the limit of the players reach) 
 *  @return Hit of type FHitResult, a structure with variables like the actor and its location etc.*/
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	/// Get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/// Find positional vector for the line trace end
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	///setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (AKA Ray-Cast) out to reach distance
	FHitResult Hit;

	bool bHit = GetWorld()->LineTraceSingleByObjectType(
		OUT Hit, PlayerViewPointLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	// print hit actors name for debugging
	if (bHit) {
		FString ActorHitName = Hit.Actor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *ActorHitName);
	};
	return Hit;
}
