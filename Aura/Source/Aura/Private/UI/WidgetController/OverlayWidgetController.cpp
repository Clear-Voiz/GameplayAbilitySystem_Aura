// Copyright Jordi Aragon


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
    const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(WidgetControllerParams.AttributeSet);
    const float Health = AuraAttributeSet->GetHealth();
    OnHealthChanged.Broadcast(Health);
    OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
    OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
    OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());

}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
    const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(WidgetControllerParams.AttributeSet);
    WidgetControllerParams.AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
        AuraAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data ){OnHealthChanged.Broadcast(Data.NewValue);});

    WidgetControllerParams.AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
        AuraAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnMaxHealthChanged.Broadcast(Data.NewValue);});

    WidgetControllerParams.AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
        AuraAttributeSet->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnManaChanged.Broadcast(Data.NewValue);});

    WidgetControllerParams.AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
        AuraAttributeSet->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnMaxManaChanged.Broadcast(Data.NewValue);});

    Cast<UAuraAbilitySystemComponent>(WidgetControllerParams.AbilitySystemComponent)->EffectAssetTags.AddLambda(
        [this](const FGameplayTagContainer& AssetTags)
        {
            for (const FGameplayTag& Tag : AssetTags)
            {

                FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
                if (Tag.MatchesTag(MessageTag))
                {
                    const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable.Get(), Tag);
                    MessageWidgetRowDelegate.Broadcast(*Row);

                }

            }
        }

    );


}