// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));

	ATank* PossessedTank = GetControlledTank();
	if (GetControlledTank() == nullptr)
	{
		PossessedTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Tank not possessed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank possessed: %s"), *PossessedTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("TICK TOCK"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector OutHitLocation; // Out parameter
	if (GetSightRayHitLocation(OutHitLocation)) // Has "side-effect", is going to ray/line trace
	{
		// UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *OutHitLocation.ToString());
        // TODO Tell controlled tank to aim at this point 
		GetControlledTank()->AimAt(OutHitLocation);
	}

}

// get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	// UE_LOG(LogTemp, Warning, TEXT("Screen location: %s"), *ScreenLocation.ToString());

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
	    // Line/ray trace along that look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		// 		UE_LOG(LogTemp, Warning, TEXT("World direction: %s"), *LookDirection.ToString());
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{	
	FVector CameraWorldLocation;
	return (DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	));
//UE_LOG(LogTemp, Warning, TEXT("World direction: %s"), *LookDirection.ToString());

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		) // Line trace succeeds
	{
		// set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0); // may be firing off into empty space/sky
	return false; // Line trace did not succeed

}