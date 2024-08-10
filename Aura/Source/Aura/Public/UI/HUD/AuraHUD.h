// Copyright Jordi Aragon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UOverlayWidgetController;
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class APlayerState;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<class UAuraUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(FWidgetControllerParams&& WCParams);

	void InitOverlay(UAbilitySystemComponent*&& ASC, UAttributeSet*&& AS, APlayerController*&& PC, APlayerState*&& PS);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
};
