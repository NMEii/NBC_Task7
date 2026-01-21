#include "TaskPawn.h"
#include "TaskPlayerController.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATaskPawn::ATaskPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneComp);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(SceneComp);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Helicopter"));
	StaticMeshComp->SetupAttachment(SceneComp);

	StaticMeshWingComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing"));
	StaticMeshWingComp->SetupAttachment(StaticMeshComp);

	StaticMeshInnerComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Inner"));
	StaticMeshInnerComp->SetupAttachment(StaticMeshComp);

	StaticMeshWheelComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel"));
	StaticMeshWheelComp->SetupAttachment(StaticMeshComp);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 800.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	BoxCollision->SetSimulatePhysics(false);
	StaticMeshComp->SetSimulatePhysics(false);

	bUseControllerRotationPitch = true; 
	bUseControllerRotationYaw = true;   
	bUseControllerRotationRoll = true;
}

void ATaskPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// IA를 가져오기 위해 현재 소유 중인 Controller를 ASpartaPlayerController로 캐스팅
		if (ATaskPlayerController* PlayerController = Cast<ATaskPlayerController>(GetController()))
		{

			EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ATaskPawn::Move);
			EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ATaskPawn::Look);
			EnhancedInput->BindAction(PlayerController->LookRollAction, ETriggerEvent::Triggered, this, &ATaskPawn::Roll);
		}
	}
}

void ATaskPawn::Move(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>();

	if (Controller != nullptr)
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();

		FVector DeltaLocation = FVector(
			MovementVector.X * MoveSpeed * DeltaTime, // X축 (앞뒤)
			MovementVector.Y * MoveSpeed * DeltaTime, // Y축 (좌우)
			MovementVector.Z * MoveSpeed * DeltaTime  // Z축 (상하)
		);

		AddActorLocalOffset(DeltaLocation, true);
	}
}

void ATaskPawn::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerPitchInput(LookAxisVector.Y);
		AddControllerYawInput(LookAxisVector.X);
	}
}

void ATaskPawn::Roll(const FInputActionValue& Value)
{
	float LookRollAxisVector = Value.Get<float>();

	if (Controller != nullptr)
	{
		AddControllerRollInput(LookRollAxisVector);
	}

}

