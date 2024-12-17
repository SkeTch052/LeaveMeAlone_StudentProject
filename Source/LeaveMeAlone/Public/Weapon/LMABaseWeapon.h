// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

class USkeletalMeshComponent;

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

	FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }

	bool GetIsCurrentClipEmpty() { return IsCurrentClipEmpty(); };
	bool GetIsCurrentClipFull() { return IsCurrentClipFull(); };

	FOnClipEmpty OnClipEmpty;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{30, 0, true};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float FireRate = 0.1f;

	virtual void BeginPlay() override;

	void Shoot();

	void DecrementBullets();
	bool IsCurrentClipEmpty() const;
	bool IsCurrentClipFull() const;

private:
	FAmmoWeapon CurrentAmmoWeapon;
	FTimerHandle FireTimerHandle;
};
