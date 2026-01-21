#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "TaskPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;

UCLASS()
class TASK07_API ATaskPawn : public APawn
{
	GENERATED_BODY()

public:
	ATaskPawn();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scene");
	USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMesh");
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMesh");
	UStaticMeshComponent* StaticMeshWingComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMesh");
	UStaticMeshComponent* StaticMeshInnerComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMesh");
	UStaticMeshComponent* StaticMeshWheelComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	UCameraComponent* CameraComp;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);  
	void Roll(const FInputActionValue& Value);

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 이동 속도
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 600.0f;

	// 회전 속도 (마우스 감도 역할)
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 100.0f;


};
