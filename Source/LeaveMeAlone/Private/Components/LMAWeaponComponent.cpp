// LeaveMeAlone Game by Netologiya. All RightsReserved.

#include "Components/LMAWeaponComponent.h"
#include "Player/LMADefaultCharacter.h"
#include "Weapon/LMABaseWeapon.h"
#include "Animations/LMAReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

ULMAWeaponComponent::ULMAWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

//-----HOMEWORK: Shooting in Full Auto Mode
void ULMAWeaponComponent::Fire()
{
	if (Weapon && !AnimReloading && !GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle))
	{
		Weapon->Fire();
	}
}

void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	InitAnimNotify();
}

void ULMAWeaponComponent::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);
	if (Weapon)
	{
		//-----HOMEWORK: Subscribe to the delegate when the weapon spawns
		Weapon->OnClipEmpty.AddUObject(this, &ULMAWeaponComponent::OnClipEmpty);
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_Weapon_Socket");
		}
	}
}

void ULMAWeaponComponent::InitAnimNotify()
{
	if (!ReloadMontage)
		return;

	const auto NotifiesEvents = ReloadMontage->Notifies;
	for (auto NotifyEvent : NotifiesEvents)
	{
		auto ReloadFinish = Cast<ULMAReloadFinishedAnimNotify>(NotifyEvent.Notify);
		if (ReloadFinish)
		{
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &ULMAWeaponComponent::OnNotifyReloadFinished);
			break;
		}
	}
}

void ULMAWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
	}
}

//-----HOMEWORK: Can't reload with a full clip
bool ULMAWeaponComponent::CanReload() const
{
	return !AnimReloading && !Weapon->GetIsCurrentClipFull();
}

//-----HOMEWORK: the new reload function
void ULMAWeaponComponent::EnhancedReload()
{
	if (!CanReload())
		return;
	//-----HOMEWORK: Can't reload and shooting at the same time
	StopFire();
	Weapon->ChangeClip();
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
}

//-----HOMEWORK: call the new function in Reload()
void ULMAWeaponComponent::Reload()
{
	EnhancedReload();
}

//-----HOMEWORK: when releasing the Fire button
void ULMAWeaponComponent::StopFire()
{
	Weapon->StopFire();
}

//-----HOMEWORK: call the new function in the delegate callback function
void ULMAWeaponComponent::OnClipEmpty()
{
	EnhancedReload();
}
