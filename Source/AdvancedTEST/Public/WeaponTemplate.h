#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponTemplate.generated.h"

UCLASS()
class ADVANCEDTEST_API ATemplateWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	virtual void Fire() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();

protected:

	UFUNCTION(BlueprintNativeEvent)
	bool CheckAmmo();

	UFUNCTION(BlueprintImplementableEvent)
	void ProcessFiring();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayEffects();

	UFUNCTION(BlueprintNativeEvent)
	void UpdateAmmo();
};