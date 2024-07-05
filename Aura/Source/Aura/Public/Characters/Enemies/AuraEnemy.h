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
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;

	UPROPERTY(EditAnywhere, BlueprintreadOnly)
	bool bHighlighted = false;
};
