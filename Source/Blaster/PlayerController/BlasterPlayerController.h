// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/PlayerState/BlasterPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHightPingDelegate,bool,bPingTooHigh);
/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	
	
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDShield(float Shield, float MaxShield);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int32 Defeats);
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDMatchCountdown(float CountdownTime);
	void SetHUDAnnouncementCountdown(float CountdownTime);
	void SetHUDGrenades(int32 Grenades);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
	virtual float GetServerTime(); // Synced with server world clock
	virtual void ReceivedPlayer() override;
	void OnMatchStateSet(FName State, bool bTeamsMatch = false);
	void HandleMatchHasStarted(bool bTeamsMatch= false);
	void HandleCooldown();
	void HideTeamScores();
	void InitTeamScores();
	void SetHUDRedTeamScore(int32 RedScore);
	void SetHUDBlueTeamScore(int32 BlueScore);

	float SingleTripTime = 0,f;
	FHightPingDelegate HightPingDelegate;

	void BroadcastElim(APlayerState* Attacker, APlayerState* Victim);

	FString GetInfoText(const TArray<ABlasterPlayerState*>& Players);
	FString GetTeamsInfoText(class ABlasterGameState* BlasterGameState);
	
protected:
	virtual void BeginPlay() override;
	void SetHUDTime();
	void PollInit();
	/*
	 * Sync time between client and server
	 */

	// Request the current server time, passing in the clients time when the request was sent 
	UFUNCTION(Server,Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);

	// Reports the current server time to rhe client in response to ServerRequestServerTime
	UFUNCTION(Client,Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);
	// differences between client and server time
	float ClientServerDelta = 0.f;
	UPROPERTY(EditAnywhere,Category=Time)
	float TimeSyncFrequency = 5.f;
	float TimeSyncRunningTime = 0.f;
	void CheckTimeSync(float DeltaSeconds);


	UFUNCTION(Server,Reliable)
	void ServerCheckMatchState();

	UFUNCTION(Client,Reliable)
	void ClientJoinMidGame(FName StateOfMatch,float Warmup,float Match,float Cooldown,float StartingTime);

	// Functions for high ping gamers
	void HighPingWarning();
	void StopHighPingWarning();
	void CheckPing(float DeltaSeconds);

	virtual void SetupInputComponent() override;

	void ShowReturnToMainMenu();

	UFUNCTION(Client,Reliable)
	void Client_ElimAnnouncement(APlayerState* Attacker, APlayerState* Victim);

	UPROPERTY(ReplicatedUsing= OnRep_ShowTeamScores)
	bool bShowTeamScores = false;
	UFUNCTION()
	void OnRep_ShowTeamScores();

private:
	UPROPERTY()
	class ABlasterHUD* BlasterHUD;

	UPROPERTY(EditAnywhere, Category= HUD)
	TSubclassOf<class UUserWidget> ReturnToMainMenuWidget;
	
	UPROPERTY()
	class UReturnToMainMenu* ReturnToMainMenu;
	bool bReturnToMainMenuOpen = false;

	UPROPERTY()
	class ABlasterGameMode* BlasterGameMode;
	float MatchTime = 0.f;
	float WarmupTime = 0.f;
	float LevelStartingTime = 0.f;
	float CooldownTime = 0.f;
	uint32 CountdownInt = 0;
	UPROPERTY(ReplicatedUsing=OnRep_MatchState)
	FName MatchState;
	
	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;

	bool bInitializeHealth = false;
	bool bInitializeShield = false;
	bool bInitializeScore = false;
	bool bInitializeDefeats = false;
	bool bInitializeGrenades = false;
	bool bInitializeCarriedAmmo = false;
	bool bInitializeWeaponAmmo = false;
	
	float HUDHealth;
	float HUDMaxHealth;
	float HUDScore;
	int32 HUDDefeats;
	int32 HUDGrenades;
	float HUDShield;
	float HUDMaxShield;
	float HUDCarriedAmmo;
	float HUDWeaponAmmo;

	
	float HighPingRunningTime = 0.f;
	
	UPROPERTY(EditAnywhere)
	float HighPingDuration = 5.f;
	
	float PingAnimationRunningTime = 0.f;

	UPROPERTY(EditAnywhere)
	float CheckPingFrequency = 20.f;

	UFUNCTION(Server,Reliable)
	void ServerReportPingStatus(bool bHighPing);
	
	UPROPERTY(EditAnywhere)
	float HighPingThreshold = 60.f;
	
};

