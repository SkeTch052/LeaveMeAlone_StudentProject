// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class UAnimMontage;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALMADefaultCharacter();

	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinArmLength = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxArmLength = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	// ----------------------- Sprint -----------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 700.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	float Stamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	float SprintStaminaCost = 25.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	float StaminaRecoveryRate = 35.0f;
	// ----------------------- Sprint -----------------------

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float YRotation = -75.0f;
	float ArmLength = 1400.0f;

	float FOV = 55.0f;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void OnDeath();
	void OnHealthChanged(float NewHealth);

	// ----------------------- Sprint -----------------------
	bool bIsSprinting = false;

	float DefaultWalkSpeed;

	void StartSprinting();
	void StopSprinting();
	// ----------------------- Sprint -----------------------

	void RotationPlayerOnCursor();

	void ZoomCamera(float AxisValue);
};
