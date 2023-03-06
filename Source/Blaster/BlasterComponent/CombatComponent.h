// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/HUD/BlasterHUD.h"
#include "Components/ActorComponent.h"
#include "Blaster/Weapon/WeaponTypes.h"
#include "Blaster/BlasterTypes/CombatState.h"
#include "CombatComponent.generated.h"
#define TRACE_LENGTH 80000.f
class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UCombatComponent();
	friend class ABlasterCharacter;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	void EquipWeapon(AWeapon* WeaponToEquip);
	void Reload();
	UFUNCTION(BlueprintCallable)
	void FinishReloading();
	void FireButtonPressed(bool bPressed);
protected:
	
	virtual void BeginPlay() override;
	void SetAiming(bool bIsAiming);

	UFUNCTION(Server,Reliable)
	void ServerSetAiming(bool bIsAiming);
	
	UFUNCTION()
	void OnRep_EquippedWeapon();
	void Fire();



	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector_NetQuantize& TraceHitTarget);
	
	UFUNCTION(NetMulticast,Reliable)
	void MulticastFire(const FVector_NetQuantize& TraceHitTarget);
	
	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	void SetHUDCrosshairs(float DeltaTime);

	UFUNCTION(Server,Reliable)
	void ServerReload();

	int32 AmountToReload();
	
	
private:
	UPROPERTY()
	class ABlasterCharacter* Character;
	UPROPERTY()
	class ABlasterPlayerController* PlayerController;
	UPROPERTY()
	class ABlasterHUD* HUD;
	UPROPERTY(ReplicatedUsing =  OnRep_EquippedWeapon)
	class AWeapon* EquippedWeapon;

	UPROPERTY(Replicated)
	bool bAiming;

	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed;
	UPROPERTY(EditAnywhere)
	float AimWalkSpeed;

	void UpdateAmmoValues();

	bool bFireButtonPressed;
	// Automatic Fire

	FTimerHandle FireTimer;
	bool bCanFire = true;
	bool CanFire();
	// Carried ammo for the currently equipped weapon
	UPROPERTY(ReplicatedUsing=OnRep_CarriedAmmo)
	int32 CarriedAmmo;
	UFUNCTION()
	void OnRep_CarriedAmmo();

	TMap<EWeaponType,int32> CarriedAmmoMap;

	UPROPERTY(EditAnywhere)
	int32 StartingARAmmo = 30;
	
	UPROPERTY(EditAnywhere)
	int32 StartingRocketAmmo = 0;
	
	UPROPERTY(EditAnywhere)
	int32 StartingPistolAmmo = 0;
	void InitializeCarriedAmmo();
	
	UPROPERTY(ReplicatedUsing=OnRep_CombatState)
	ECombatState CombatState = ECombatState::ECS_Unoccupied;

	UFUNCTION()
	void OnRep_CombatState();

	void HandleReload();
	
	void StartFireTimer();
	void FireTimerFinished();
	//HUD and Crosshairs


	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
	float CrosshairAimFactor;
	float CrosshairFireFactor;

	FVector HitTarget;

	FHUDPackage HUDPackage;

	// Aiming and FOV
	
	float DefaultFOV;

	UPROPERTY(EditAnywhere, Category= Combat)
	float ZoomedFOV = 30.f;
	
	UPROPERTY(EditAnywhere, Category= Combat)
	float ZoomInterpSpeed = 20.f;

	float CurrentFOV;
	
	void InterpFOV(float DeltaTime);
	
	
	
	

	
public:	
		
};
