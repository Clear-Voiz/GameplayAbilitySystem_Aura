// Copyright Jordi Aragon


#include "AbilitySystem/MMC/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
    IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
    IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    IntelligenceDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec & Spec) const
{
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    float IntelligenceMagnitude = 0.f;
    IntelligenceMagnitude = GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, IntelligenceMagnitude);
    IntelligenceMagnitude = FMath::Max<float>(0.f, IntelligenceMagnitude);

    ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
    float Level = CombatInterface->GetPlayerLevel();

    return 50.f + 2.5f *IntelligenceMagnitude + 15.f * Level;
}
