// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankyTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankyTurret* TurretoSet)
{
	if (!TurretoSet) { return; }
	Turret = TurretoSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Barrel object not found!!!"));
		UE_LOG(LogTemp, Error, TEXT("Barrel object not found!!!"));
		UE_LOG(LogTemp, Error, TEXT("Barrel object not found!!!"));
		UE_LOG(LogTemp, Error, TEXT("Barrel object not found!!!"));
		UE_LOG(LogTemp, Error, TEXT("Barrel object not found!!!"));
		return; 
	}
	if (!Turret)
	{
		UE_LOG(LogTemp, Error, TEXT("Turret object not found!!!"));
		UE_LOG(LogTemp, Error, TEXT("Turret object not found!!!"));
		UE_LOG(LogTemp, Error, TEXT("Turret object not found!!!"));
		UE_LOG(LogTemp, Error, TEXT("Turret object not found!!!"));
		UE_LOG(LogTemp, Error, TEXT("Turret object not found!!!"));
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
//		FString TankName = GetOwner()->GetName();
//		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		//auto Time = GetWorld()->GetTimeSeconds();
	//	UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
	}
	// If no solution found do nothing
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	// Work out the difference between current turret rotation and aim direction
	FRotator TurretRotator = Turret->GetForwardVector().Rotation(); // the direction the turret is pointing
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - TurretRotator;

	// Rotate turret
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work out the difference between current barrel rotation and aim direction
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation(); // the direction the barrel is pointing
	FRotator AimAsRotator = AimDirection.Rotation();
	// UE_LOG(LogTemp, Warning, TEXT("AimAsRotator at %s"), *AimAsRotator.ToString());
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	//Turret->Rotate(DeltaRotator.Yaw);
    // Elavate barrel
	Barrel->Elevate(DeltaRotator.Pitch); // TODO remove magic number
}
