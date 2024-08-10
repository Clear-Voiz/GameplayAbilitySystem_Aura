// Copyright Jordi Aragon


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(FWidgetControllerParams&& WCParams)
{
	WidgetControllerParams = MoveTemp(WCParams);
}

void UAuraWidgetController::BroadcastInitialValues()
{

}

void UAuraWidgetController::BindCallbacksToDependencies()
{
	
}
