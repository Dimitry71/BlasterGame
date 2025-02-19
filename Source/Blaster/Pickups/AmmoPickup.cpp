// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/BlasterComponent/CombatComponent.h"

void AAmmoPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweetResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweetResult);

	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor) ;
	if(BlasterCharacter)
	{
		UCombatComponent* Combat = BlasterCharacter->GetCombat();
		if(Combat)
		{
			Combat->PickupAmmo(WeaponType,AmmoAmount);
		}
	}
	Destroy();
}
