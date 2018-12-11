// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBS.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TimerManager.h"
#include "Animation/AnimInstance.h"
#include "PlayerStateBS.h"
#include "iGun.h"
#include "PlayerControllerBS.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "NPCBS.h"

//#include "Kismet/GameplayStatics.h"
// Sets default values
ACharacterBS::ACharacterBS()
	:m_fZoomSpeed(20.0f),
	m_fZoom(65.0f),
	m_bDied(false),
	m_bSprint(false),
	m_bProne(false),
	m_bMove(false),
	m_bFire(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_pSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_pSpring->bUsePawnControlRotation = true;
	m_pSpring->SetupAttachment(RootComponent);
	m_pSpring->bEnableCameraRotationLag = true;
	m_pCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	m_pCam->SetupAttachment(m_pSpring);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Called when the game starts or when spawned
void ACharacterBS::BeginPlay()
{
	Super::BeginPlay();
	m_fZoomDefault = m_pCam->FieldOfView;

	APlayerStateBS* pPs = Cast<APlayerStateBS>(PlayerState);
	if (pPs)
	{
		pPs->Setuphp();
	}
}

void ACharacterBS::MoveForward(float Value)
{
	m_bMove || m_bProne ? NULL : AddMovementInput(GetActorForwardVector()* Value);
}

void ACharacterBS::MoveRight(float Value)
{
	m_bMove || m_bProne ? NULL : AddMovementInput(GetActorRightVector()* Value);
}

void ACharacterBS::AddPitch(float Value)
{
	m_bMove  ? NULL : AddControllerPitchInput(Value);
}

void ACharacterBS::AddYaw(float Value)
{
	m_bMove || m_bProne ? NULL : AddControllerYawInput(Value);
}
void ACharacterBS::BeginCrouch()
{
	m_bCrouch = true;
	Crouch();
	MoveCheck(0.5f);
}

void ACharacterBS::EndCrouch()
{
	m_bCrouch = false;
	UnCrouch();
	MoveCheck(0.5f);
}

void ACharacterBS::ZoomBegin()
{
	if (m_bMove)return;
	m_bWantsToZoom = true;
}

void ACharacterBS::ZoomEnd()
{
	m_bWantsToZoom = false;
}

void ACharacterBS::FireStart()
{
	m_bMove ? NULL : m_bFire = true;

	APlayerControllerBS* pC = Cast<APlayerControllerBS>(Controller);

	if (pC->IsTalk())
	{
		ANPCBS* pNpc = Cast<ANPCBS>(pC->m_FHitresult.Hit.GetActor());
		if (pNpc)
		{
			if (pNpc->Talk())
			{
				m_bMove = false;
			}
			else
			{
				m_bMove = true;
			}
		}
	}
	else
	{
		if (m_pHandle)
		{
			if (m_pHandle)
				m_pHandle->FireStart();
		}
		else
		{
			APlayerStateBS* pPs = Cast<APlayerStateBS>(PlayerState);
			if (pPs)
			{
				m_pHandle = Cast<AiGun>(pPs->m_EQInven[(int)EQment::EQ_GUN]);

				if (m_pHandle)
					m_pHandle->FireStart();
			}
		}
	}
	
}

void ACharacterBS::TalkReset()
{
	APlayerControllerBS* pC = Cast<APlayerControllerBS>(Controller);
	if (pC)
	{
		ANPCBS* pNpc = Cast<ANPCBS>(pC->m_FHitresult.Hit.GetActor());
		if (pNpc)
		{
			pNpc->StoryIndexReset();
		}
	}
	m_bMove = false;
}

void ACharacterBS::FireEnd()
{
	m_bFire = false;
	if (m_pHandle)
		m_pHandle->FireEnd();
}

void ACharacterBS::proneStart()
{
	if (!m_bFire)
	{
		float Speed;  FVector dir;
		GetVelocity().ToDirectionAndLength(dir, Speed);

		Speed <= 10 ? m_bProne ? EndProne() : BeginProne() : NULL;
	}
}

void ACharacterBS::sprintStart()
{
	m_bSprint ? m_bSprint = false : m_bSprint = true;
}

void ACharacterBS::BeginProne()
{
	m_bProne = true;
	Crouch();
	MoveCheck(1.3f);
}

void ACharacterBS::EndProne()
{
	m_bProne = false;
	UnCrouch();
	MoveCheck(1.3f);
}

void ACharacterBS::Jumpkey()
{
	m_bMove ? NULL : Jump();
}

void ACharacterBS::SetMove()
{
	m_bMove = false;
	GetWorldTimerManager().ClearTimer(m_fTimerHandle);
}

void ACharacterBS::SetReload()
{
	m_bProne? MoveCheck(3.333f): MoveCheck(2.167f);
}

void ACharacterBS::MoveCheck(float DelayTime)
{
	m_bMove = true;

	GetWorldTimerManager().SetTimer(m_fTimerHandle, this, &ACharacterBS::SetMove, DelayTime, false);
}

// Called every frame
void ACharacterBS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Current;
	m_bProne ? Current = m_bWantsToZoom ? m_fZoom - 35 : m_fZoomDefault : Current = m_bWantsToZoom ? m_fZoom : m_fZoomDefault;

	float CurrentLerp = FMath::FInterpTo(m_pCam->FieldOfView, Current, DeltaTime, m_fZoomSpeed);
	m_pCam->SetFieldOfView(CurrentLerp);

	float Speed;  FVector dir;

	GetVelocity().ToDirectionAndLength(dir, Speed);

	Speed <= 10 ? m_bSprint = false : NULL;
}

// Called to bind functionality to input
void ACharacterBS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBS::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBS::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterBS::AddPitch);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterBS::AddYaw);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacterBS::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACharacterBS::EndCrouch);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterBS::Jumpkey);

	PlayerInputComponent->BindAction("sprint", IE_Pressed, this, &ACharacterBS::sprintStart);
	PlayerInputComponent->BindAction("sprint", IE_Released, this, &ACharacterBS::sprintStart);

	PlayerInputComponent->BindAction("prone", IE_Pressed, this, &ACharacterBS::proneStart);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACharacterBS::FireStart);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACharacterBS::FireEnd);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ACharacterBS::ZoomBegin);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ACharacterBS::ZoomEnd);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ACharacterBS::SetReload);
}

void ACharacterBS::OnDameged(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	APlayerStateBS* pPs = Cast<APlayerStateBS>(PlayerState);
	if (pPs)
	{
		pPs->SetDamege(Damage);
	}
}