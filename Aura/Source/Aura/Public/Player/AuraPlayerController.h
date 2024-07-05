// Copyright Jordi Aragon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class UInputAction;
struct FInputActionValue;
class IHighlighter;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


private:
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<class UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> IA_Move;

	void Move(const struct FInputActionValue& InputActionValue);
	
	void CursorTrace();

	TScriptInterface<IHighlighter> LastActor;
	TScriptInterface<IHighlighter> ThisActor;
};
