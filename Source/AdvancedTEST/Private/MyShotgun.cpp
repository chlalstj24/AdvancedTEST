#include "MyShotgun.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DamageEvents.h"

AMyShotgun::AMyShotgun()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(Root);

	GunMesh->SetCollisionProfileName(TEXT("NoCollision"));

	GunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GunMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	PelletCount = 8;
	SpreadAngle = 15.0f;
	RecoilPitch = -2.0f;
	RecoilYaw = 1.0f;
	BaseDamage = 10.0f;
}

void AMyShotgun::Fire()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController());
	if (!PC) return;

	FVector CamLoc;
	FRotator CamRot;
	PC->GetPlayerViewPoint(CamLoc, CamRot);

	PC->AddPitchInput(RecoilPitch);
	PC->AddYawInput(FMath::RandRange(-RecoilYaw, RecoilYaw));

	float HalfAngleRadians = FMath::DegreesToRadians(SpreadAngle / 2.0f);
	FVector ShootDir = CamRot.Vector();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(OwnerPawn);

	for (int32 i = 0; i < PelletCount; ++i)
	{
		FVector RandomDir = FMath::VRandCone(ShootDir, HalfAngleRadians);
		FVector EndLocation = CamLoc + (RandomDir * 5000.0f);

		FHitResult HitResult;

		bool bHit = UKismetSystemLibrary::LineTraceSingle(
			GetWorld(),
			CamLoc,
			EndLocation,
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false,
			ActorsToIgnore,
			EDrawDebugTrace::ForDuration,
			HitResult,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			2.0f
		);

		if (bHit && HitResult.GetActor())
		{
			UGameplayStatics::ApplyPointDamage(
				HitResult.GetActor(),
				BaseDamage,
				RandomDir,
				HitResult,
				PC,
				this,
				DamageTypeClass
			);
		}
	}
}