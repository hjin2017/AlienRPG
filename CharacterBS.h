// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBS.generated.h"

UCLASS()
class ALIENRPG_API ACharacterBS : public ACharacter
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp")
	class UCameraComponent* m_pCam;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp")
	class USpringArmComponent* m_pSpring;
	
	float m_fZoomDefault;
	
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float m_fZoom;
	
	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1f, ClampMax = 100.f))
	float m_fZoomSpeed;
	
	bool m_bWantsToZoom;
	
	UPROPERTY(Category = "Player", BlueprintReadOnly)
	bool m_bDied;
	
	UPROPERTY(Category = "Player", BlueprintReadOnly)
	bool m_bProne;
	
	UPROPERTY(Category = "Player", BlueprintReadOnly)
	bool m_bSprint;
	UPROPERTY(Category = "Player", BlueprintReadOnly)
	bool m_bCrouch;
	
	bool m_bFire;

	FTimerHandle m_fTimerHandle;
	bool m_bMove;

	class AiGun* m_pHandle;
public:
	// Sets default values for this character's properties
	ACharacterBS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void AddPitch(float Value);
	void AddYaw(float Value);

	void BeginCrouch();
	void EndCrouch();

	void ZoomBegin();
	void ZoomEnd();
	void FireStart();
	void FireEnd();

	void proneStart();
	void sprintStart();

	void BeginProne();
	void EndProne();

	void Jumpkey();

	void SetMove();

	void SetReload();

	void MoveCheck(float DelayTime);

	UFUNCTION()
		void OnDameged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION(BlueprintCallable, Category = "PlayerEvent")
	void TalkReset();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
