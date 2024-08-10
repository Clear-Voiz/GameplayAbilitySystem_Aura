// Copyright Jordi Aragon


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController *AAuraHUD::GetOverlayWidgetController(FWidgetControllerParams &&WCParams)
{
	if (OverlayWidgetController)
	{
		return OverlayWidgetController;
	}

	else
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(MoveTemp(WCParams));
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
		
	}
}

void AAuraHUD::InitOverlay(UAbilitySystemComponent *&&ASC, UAttributeSet *&&AS, APlayerController *&&PC, APlayerState *&&PS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_Aura_HUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_Aura_HUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	FWidgetControllerParams WidgetControllerParams(MoveTemp(ASC), MoveTemp(AS), MoveTemp(PC), MoveTemp(PS));
	UOverlayWidgetController* TempOverlayWidgetController = GetOverlayWidgetController(MoveTemp(WidgetControllerParams));
	OverlayWidget->SetWidgetController(TempOverlayWidgetController);
	TempOverlayWidgetController->BroadcastInitialValues();

	Widget->AddToViewport();

}
