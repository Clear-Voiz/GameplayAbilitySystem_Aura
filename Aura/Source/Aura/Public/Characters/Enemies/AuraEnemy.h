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

	UPROPERTY(EditAnywhere, BlueprintreadOnly)
	bool bHighlighted = false;

	/** Highlighter Interface */
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	/** End Highlighter Interface */

	/** Combat Interface*/
	virtual int32 GetPlayerLevel() override;
	/**End Combat Interface */




protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta=(AllowPrivateAccess="true"))
	int32 Level = 1;

};
