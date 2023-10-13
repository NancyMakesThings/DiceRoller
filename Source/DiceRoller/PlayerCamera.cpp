// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"

// Sets default values
APlayerCamera::APlayerCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerCamera Constructor"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent1"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	// Attach components
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	// Assign variables
	SpringArmComp->SetRelativeLocationAndRotation(StartLocation, StartRotation);
	SpringArmComp->TargetArmLength = StartArmLength;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->bDoCollisionTest = false; // may update to true as camera movement is improved
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;
}

void APlayerCamera::Zoom(const FInputActionValue& Value)
{	
	UE_LOG(LogTemp, Warning, TEXT("APlayerCamera::Zoom started"));

	const float CurrentValue = Value.Get<float>();
	float AddZoom;
	if (CurrentValue > 0 )
	{
		AddZoom = ZoomInterval;
	}
	else
	{
		AddZoom = -ZoomInterval;
	}
	SpringArmComp->TargetArmLength = FMath::Clamp(SpringArmComp->TargetArmLength + AddZoom, ArmClampMin, ArmClampMax);

	UE_LOG(LogTemp, Warning, TEXT("APlayerCamera::Zoom Value: %f"), CurrentValue);
	UE_LOG(LogTemp, Warning, TEXT("APlayerCamera::Zoom TargetZoomDistance: %f"), SpringArmComp->TargetArmLength);

}

void APlayerCamera::Rotate(const FInputActionValue& Value)
{
	const FVector CurrentValue = Value.Get<FVector>();
	AddControllerPitchInput(CurrentValue.Y);
	AddControllerYawInput(CurrentValue.X);
}

// Updates mouse location for camera panning. Actual pan operation occurs in Tick.
void APlayerCamera::PanStart()
{
	bEnablePan = true;
	PreviousPanPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
}

void APlayerCamera::PanStop()
{
	if (bEnablePan)
	{
		bEnablePan = false;
	}
}

void APlayerCamera::Center(FVector TargetLocation)
{
	SetActorLocation(TargetLocation, true);
}

void APlayerCamera::Home()
{
	SetActorLocation(HomeLocation);
	GetController()->SetControlRotation(FRotator(0.0f));
	SpringArmComp->TargetArmLength = StartArmLength;
}

// Called when the game starts or when spawned
void APlayerCamera::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerCamera Begin Play"))
	Super::BeginPlay();
}

// Called every frame
void APlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	
	// Pan operation
	if (bEnablePan)
	{
		FVector2D NewPanPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());		
		FVector2D AddOffset = NewPanPosition - PreviousPanPosition;
		AddActorLocalOffset(FVector(AddOffset.Y, -AddOffset.X, 0.0f)); // X-Y flipped due to Viewport to UE 3D-axis conversion

		// Undo offset if camera out of bounds
		FVector CurrentLocation = GetActorLocation();
		if (CurrentLocation.X >= MaxX || CurrentLocation.X <= MinX || CurrentLocation.Y >= MaxY || CurrentLocation.Y <= MinY 
			|| CurrentLocation.Z >= MaxZ || CurrentLocation.Z <= MinZ)
		{
			AddActorLocalOffset(FVector(-AddOffset.Y, AddOffset.X, 0.0f));
		}
		PreviousPanPosition = NewPanPosition;
	}
	
}

// Called to bind functionality to input
void APlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

