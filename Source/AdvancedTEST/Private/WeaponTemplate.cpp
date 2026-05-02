#include "WeaponTemplate.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"

void ATemplateWeaponBase::Fire()
{
	if (!CanFire) return;

	if (CheckAmmo())
	{
		PlayEffects();
		ProcessFiring();
		UpdateAmmo();
		Super::Fire();
		return;
	}

	Reload();
}

void ATemplateWeaponBase::Reload_Implementation()
{
	CurrentAmmo = MaxAmmo;
	HandleFireDelay();
}

bool ATemplateWeaponBase::CheckAmmo_Implementation()
{
	return AmmoPerFire <= CurrentAmmo;
}

void ATemplateWeaponBase::UpdateAmmo_Implementation()
{
	CurrentAmmo -= AmmoPerFire;
}