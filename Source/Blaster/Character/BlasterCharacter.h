// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/BlasterComponent/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Blaster/TurnInPlace.h"
#include "Blaster/Interfaces/InteractWithCrosshairsInterface.h"
#include "Components/TimelineComponent.h"
#include "Sound/SoundCue.h"
#include "Blaster/BlasterTypes/CombatState.h"
#include "BlasterCharacter.generated.h"

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter , public IInteractWithCrosshairsInterface
{
	GENERATED_BODY()
	

public:
	// Sets default values for this character's properties
	ABlasterCharacter();
// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	void PlayFireMontage(bool bAiming);
	void PLayReloadMontage();
	void PlayElimMontage();

	virtual void OnRep_ReplicatedMovement() override;
	void Elim();
	UFUNCTION(NetMulticast,Reliable)
	void MulticastElim();
	virtual void Destroyed() override;
	UPROPERTY(Replicated)
	bool bDisableGameplay = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void ReloadButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void CalculateAO_Pitch();
	void AimOffset(float DeltaTime);
	void SimProxiesTurn();
	virtual void Jump() override;
	void FireButtonPressed();
	void FireButtonReleased();
	void PlayHitReactMontage();

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor,float Damage,const UDamageType* DamageType,class AController* InstigatorController,AActor* DamageCauser);
	void UpdateHUDHealth();
	// Poll for any relevant classes and initialize our HUD
	void PollInit();
	void RotateInPlace(float DeltaTime);
	
	

private:
	UPROPERTY(VisibleAnywhere, Category= Camera)
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category= Camera)
	class UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	class AWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* Combat; 

	UFUNCTION(Server,Reliable)
	void ServerEquipButtonPressed();

	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);


	/*
	 *Animation montages
	 */
	UPROPERTY(EditAnywhere,Category= Combat)
	class UAnimMontage* FireWeaponMontage;

	UPROPERTY(EditAnywhere,Category= Combat)
	UAnimMontage* ReloadMontage;
	
	UPROPERTY(EditAnywhere,Category= Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere,Category= Combat)
	UAnimMontage* ElimMontage;

	

	void HideCameraIfCharacterClose();

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

	bool bRotateRootBone;
	float TurnThreshold = 0.5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;
	float TimeSinceLastMovementReplication;
	float CalculateSpeed();

	// Player Health

	UPROPERTY(EditAnywhere, Category= "PLayer Stats")
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere ,Category= "PLayer Stats")
	float Health = 100.f;

	UFUNCTION()
	void OnRep_Health();

	bool bElimmed = false;
	UPROPERTY()
	class ABlasterPlayerController* BlasterPlayerController;

	FTimerHandle ElimTimer;
	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;
	void ElimTimerFinished();
	
	// Dissolve Effect

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DissolveTimeline;
	
	FOnTimelineFloat DissolveTrack;

	UFUNCTION()
	void UpdateDissolveMaterial(float DissolveValue);
	void StartDissolve();

	UPROPERTY(EditAnywhere)
	UCurveFloat* DissolveCurve;

	// Dynamic instance that we can change at runtime
	UPROPERTY(VisibleAnywhere, Category= Elim)
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;

	// Material instance set on Blueprint, used with the dynamic material instance 
	UPROPERTY(EditAnywhere, Category=Elim)
	UMaterialInstance* DissolveMaterialInstance;
	
	// Elim Bot
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* ElimBotEffect;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ElimBotComponent;

	UPROPERTY(EditAnywhere)
	USoundCue* ElimBotSound;

	UPROPERTY()
	class ABlasterPlayerState* BlasterPlayerState;
	
public:	
	void SetOverlappingWeapon(AWeapon* Weapon);
	bool IsWeaponEquipped();
	bool IsAiming();
	FORCEINLINE float GetAO_Yaw() const {return AO_Yaw;} 
	FORCEINLINE float GetAO_Pitch() const {return AO_Pitch;}
	AWeapon* GetEquippedWeapon() const;
	FORCEINLINE ETurningInPlace GetTurningInPlace() const  {return TurningInPlace;}
	FVector GetHitTarget() const;
	FORCEINLINE UCameraComponent* GetFollowCamera() const {return FollowCamera;}
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone;}
	FORCEINLINE bool IsElimmed() const { return bElimmed;}
	FORCEINLINE float GetHealth() const {return Health;}
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;}
	ECombatState GetCombatState() const;
	FORCEINLINE UCombatComponent* GetCombat() const { return Combat;}
	FORCEINLINE bool GetDisableGameplay() const {return bDisableGameplay;}
};
