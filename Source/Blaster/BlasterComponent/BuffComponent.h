// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UBuffComponent();
	friend class ABlasterCharacter;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Heal(float HealAmount, float HealingTime);
	void ReplenishShield(float ShieldAmount, float ReplenishTime);
	void BuffSpeed(float BuffBaseSpeed,float BuffCrouchSpeed, float BuffTime);
	void BuffJump(float BuffJumpVelocity, float BuffTime);
	void SetInitialSpeeds(float BaseSpeed, float CrouchSpeed);
	void SetInitialJumpVelocity(float BaseJumpVelocity);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void HealRampUp(float DeltaTime);
	void ShieldRampUp(float DeltaTime);
private:
	UPROPERTY()
	class ABlasterCharacter* Character;

	/*
	 *	Health Buff
	 */
	bool bHealing = false;
	float HealingRate = 0.f;
	float AmountToHeal = 0.f;

	/*
	 * Shiel Buff
	 */

	bool bReplenishingShield = false;
	float ShieldReplenishRate = 0.f;
	float ShielReplenishAmount = 0.f;

	/*
	 * Speed Buff
	 */
	FTimerHandle SpeedBuffTimer;
	void ResetSpeeds();
	float InitialBaseSpeed;
	float InitialCrouchSpeed;
	UFUNCTION(NetMulticast,Reliable)
	void MulticastSpeedBuff(float BaseSpeed, float BaseCrouchSpeed);

	/*
	 *	Jump Buff
	 */
	
	FTimerHandle JumpBuffTimer;
	void ResetJump();
	float InitialJumpVelocity;
	UFUNCTION(NetMulticast,Reliable)
	void MulticastJumpBuff(float JumpVelocity);
	
	
public:	
	

		
};
