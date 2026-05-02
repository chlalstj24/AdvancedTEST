#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyShotgun.generated.h"

UCLASS()
class ADVANCEDTEST_API AMyShotgun : public AActor
{
	GENERATED_BODY()

public:
	AMyShotgun();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	int32 PelletCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float SpreadAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float RecoilPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float RecoilYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	TSubclassOf<class UDamageType> DamageTypeClass;
};