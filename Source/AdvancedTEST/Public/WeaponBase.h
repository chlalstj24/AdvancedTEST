#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class ADVANCEDTEST_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UArrowComponent> FirePoint;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Fire();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AmmoPerFire;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RoF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamagePerHit;


	UPROPERTY(BlueprintReadWrite)
	bool CanFire;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle TimerFireDelay;

	UFUNCTION()
	void HandleFireDelay();
};