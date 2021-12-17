// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "GameFramework/Character.h"
#include "ViveCPlusPlusCharacter.generated.h"

UCLASS(config=Game)
class AViveCPlusPlusCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = Pickup)
		class USceneComponent* StartLineTrace;

	UPROPERTY(VisibleAnywhere, Category = Pickup)
		class USceneComponent* HeldItem;

	UPROPERTY(EditDefaultsOnly, Category = Respawn)
		TSubclassOf<AActor> actorToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = Painball)
		TSubclassOf<ABullet> actorBullet;

public:
	AViveCPlusPlusCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//Speed
	UPROPERTY(EditAnywhere, Category = Speed)
		float walkSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = Speed)
		float runSpeed = 600.f;

	//Health
	UPROPERTY(EditAnywhere, Category = Health)
		int life = 50;

	UPROPERTY(EditAnywhere, Category = Health)
		int maxLife = 100;

	UPROPERTY()
		AActor* objectPick;

	UPROPERTY()
		bool isItemInHand;

	UPROPERTY()
		FTimerHandle respawnTimer;

protected:

	void BeginPlay() override;

	UFUNCTION()
		void OnStartRun();

	UFUNCTION()
		void OnStopRun();


	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
		int GetLife();

	UFUNCTION()
		void SetLife(int changeLife);

	UFUNCTION()
		void PickupItem();

	UFUNCTION()
		void Ragdoll();

	UFUNCTION()
		void Respawn();

	UFUNCTION()
		void FirePaintball();
};

