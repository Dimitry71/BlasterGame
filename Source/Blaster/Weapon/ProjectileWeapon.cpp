// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Projectile.h"

void AProjectileWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);
	
	

	
	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
	UWorld* World = GetWorld();
	if(MuzzleFlashSocket && World)
	{
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		FVector ToTarget = HitTarget - SocketTransform.GetLocation();
		FRotator TargetRotation = ToTarget.Rotation();
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();
		SpawnParameters.Instigator = InstigatorPawn;
		AProjectile* SpawnProjectile = nullptr;
		if(bUseServerSideRewind)
		{
			if(InstigatorPawn->HasAuthority()) // server
			{
				if(InstigatorPawn->IsLocallyControlled()) // server host - use replicated
				{
					SpawnProjectile = World->SpawnActor<AProjectile>(ProjectileClass,SocketTransform.GetLocation(),TargetRotation,SpawnParameters);
					SpawnProjectile->bUseServerSideRewind = false;
					SpawnProjectile->Damage = Damage;
					SpawnProjectile->HeadShotDamage = HeadShotDamage;
				}
				else // server, not locally controlled - spawn non-replicated projectile,SSR
				{
					SpawnProjectile = World->SpawnActor<AProjectile>(ServerSideRewindProjectileClass,SocketTransform.GetLocation(),TargetRotation,SpawnParameters);
					SpawnProjectile->bUseServerSideRewind = true;
				}
			}
			else // not server, using SSR
			{
				if(InstigatorPawn->IsLocallyControlled()) // client, locally controlled
				{
					SpawnProjectile = World->SpawnActor<AProjectile>(ServerSideRewindProjectileClass,SocketTransform.GetLocation(),TargetRotation,SpawnParameters);
					SpawnProjectile->bUseServerSideRewind = true;
					SpawnProjectile->TraceStart = SocketTransform.GetLocation();
					SpawnProjectile->InitialVelocity = SpawnProjectile->GetActorForwardVector() * SpawnProjectile->InitialSpeed;
				}
				else // client, not locally controlled - no SSR , non-replicate
				{
					SpawnProjectile = World->SpawnActor<AProjectile>(ServerSideRewindProjectileClass,SocketTransform.GetLocation(),TargetRotation,SpawnParameters);
					SpawnProjectile->bUseServerSideRewind = false;
				}
			}
		}
		else
		{
			if(InstigatorPawn->HasAuthority())
			{
				SpawnProjectile = World->SpawnActor<AProjectile>(ProjectileClass,SocketTransform.GetLocation(),TargetRotation,SpawnParameters);
				SpawnProjectile->bUseServerSideRewind = false;
				SpawnProjectile->Damage = Damage;
				SpawnProjectile->HeadShotDamage = HeadShotDamage;
			}
		}
		
	}
}
