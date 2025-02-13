// Copyright Jordi Aragon


#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "Interaction/CombatInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
    VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
    VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    VigorDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec & Spec) const
{
    //Gather tags from source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    float VigorMagnitude = 0.f;
    GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, VigorMagnitude);

    VigorMagnitude = FMath::Max<float>(VigorMagnitude, 0.f);

    ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
    const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

    return 80.f + 2.5f * VigorMagnitude + 10 * PlayerLevel;
}
