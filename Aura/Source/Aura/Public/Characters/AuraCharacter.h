// Copyright Jordi Aragon

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;

	/**Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/**End Combat Interface */


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	virtual void OnRep_PlayerState() override;

	void InitAbilitySystemComponentAndAttributeSet(class UAbilitySystemComponent* InAbilitySystemComponent, class UAttributeSet* InAttributeSet);
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	
};
