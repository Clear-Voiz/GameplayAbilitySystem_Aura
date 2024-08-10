// Copyright Jordi Aragon

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interaction/Highlighter.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IHighlighter
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();

	/** Highlighter Interface */
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	/** End Highlighter Interface */

	UPROPERTY(EditAnywhere, BlueprintreadOnly)
	bool bHighlighted = false;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

};
