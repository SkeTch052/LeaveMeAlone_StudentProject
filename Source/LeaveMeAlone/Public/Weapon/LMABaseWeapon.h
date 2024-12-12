// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

class USkeletalMeshComponent;
//-----HOMEWORK: Declare the delegate
DECLARE_MULTICAST_DELEGATE(FOnClipEmpty);

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ALMABaseWeapon();

	void Fire();
	void StopFire();
	void ChangeClip();

	//-----HOMEWORK: Get the necessary booleans
	bool GetIsCurrentClipEmpty() { return IsCurrentClipEmpty(); };
	bool GetIsCurrentClipFull() { return IsCurrentClipFull(); };

	// -----HOMEWORK: Declare the delegate
	FOnClipEmpty OnClipEmpty;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{30, 0, true};

	//-----HOMEWORK: Fire Rate for Full Auto Mode
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float FireRate = 0.1f;

	virtual void BeginPlay() override;

	void Shoot();

	void DecrementBullets();
	bool IsCurrentClipEmpty() const;
	//-----HOMEWORK: check if the current clip is full
	bool IsCurrentClipFull() const;

private:
	FAmmoWeapon CurrentAmmoWeapon;
	//-----HOMEWORK: The firing event will now be triggered by a timer
	FTimerHandle FireTimerHandle;
};
