// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPickup.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/BlasterComponent/BuffComponent.h"

void ASpeedPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweetResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweetResult);
	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
   	if(BlasterCharacter)
   	{
    	UBuffComponent* Buff = BlasterCharacter->GetBuffComponent();
    	if(Buff)
    	{
    		Buff->BuffSpeed(BaseSpeedBuff,CrouchSpeedBuff,SpeedBuffTime);
    	}
   	}
	Destroy();
}
