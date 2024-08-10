// Copyright Jordi Aragon
#include "Characters/AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "UI/HUD/AuraHUD.h"


AAuraCharacter::AAuraCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm Component");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");

	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);


	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->RotationRate = FRotator(0.f, 400.f, 0.f);
		MovementComponent->bConstrainToPlane = true;
		MovementComponent->bSnapToPlaneAtStart = true;
	}

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init AbilitySystemComponent for the server
	AAuraPlayerState* AuraPlayerState = NewController->GetPlayerState<AAuraPlayerState>();
	if (!AuraPlayerState)
	{
		return;
	}

	InitAbilitySystemComponentAndAttributeSet(AuraPlayerState->GetAbilitySystemComponent(), AuraPlayerState->GetAttributeSet());
	InitAbilityActorInfo(AuraPlayerState, this);
}

void AAuraCharacter::OnRep_PlayerState()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC)
	{
		return;
	}

	AAuraPlayerState* AuraPlayerState = PC->GetPlayerState<AAuraPlayerState>();
	if (!AuraPlayerState)
	{
		return;
	}
	AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>();
	if (!AuraHUD)
	{
		return;
	}

	InitAbilitySystemComponentAndAttributeSet(AuraPlayerState->GetAbilitySystemComponent(), AuraPlayerState->GetAttributeSet());
	InitAbilityActorInfo(AuraPlayerState, this);
}

void AAuraCharacter::InitAbilitySystemComponentAndAttributeSet(UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet)
{
	AbilitySystemComponent = InAbilitySystemComponent;
	AttributeSet = InAttributeSet;
}

void AAuraCharacter::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) 
	{
		return;
	}

	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	if (!PS)
	{
		return;
	}
	AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>();
	AuraHUD->InitOverlay(GetAbilitySystemComponent(),GetAttributeSet(),MoveTemp(PC),MoveTemp(PS));
}
