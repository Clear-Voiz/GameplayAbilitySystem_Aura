// Copyright Jordi Aragon

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"



class UAbilitySystemComponent;
class UAttributeSet;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}

	FWidgetControllerParams(UAbilitySystemComponent*&& InAbilitySystemComponent, UAttributeSet*&& InAttributeSet, APlayerController*&& InPlayerController, APlayerState*&& InPlayerState)
		: AbilitySystemComponent(MoveTemp(InAbilitySystemComponent)), AttributeSet(MoveTemp(InAttributeSet)), PlayerController(MoveTemp(InPlayerController)), PlayerState(MoveTemp(InPlayerState))
	{	
		InAbilitySystemComponent = nullptr;

		InAttributeSet = nullptr;

		InPlayerController = nullptr;
		
		InPlayerState = nullptr;

		UE_LOG(LogTemp, Warning, TEXT("Move Constructor called for WidgetControllerParams"));}

	FWidgetControllerParams(const FWidgetControllerParams& Other) = default;

	FWidgetControllerParams(FWidgetControllerParams&& Other) noexcept //can probably be used with default
	: AbilitySystemComponent(MoveTemp(Other.AbilitySystemComponent)), AttributeSet(MoveTemp(Other.AttributeSet)), PlayerController(MoveTemp(Other.PlayerController)), PlayerState(MoveTemp(Other.PlayerState))
	{
		Other.AbilitySystemComponent = nullptr;

		Other.AttributeSet = nullptr;

		Other.PlayerController = nullptr;

		Other.PlayerState = nullptr;

		UE_LOG(LogTemp, Warning, TEXT("Move Constructor called for WidgetControllerParams"));
	}

	FWidgetControllerParams& operator=(const FWidgetControllerParams& Other) = default;

	FWidgetControllerParams& operator=(FWidgetControllerParams&& Other) noexcept
	{
		if (this == &Other) return *this;
		this->AbilitySystemComponent = Other.AbilitySystemComponent;
		Other.AbilitySystemComponent = nullptr;

		this->AttributeSet = Other.AttributeSet;
		Other.AttributeSet = nullptr;

		this->PlayerController = Other.PlayerController;
		Other.PlayerController = nullptr;

		this->PlayerState = Other.PlayerState;
		Other.PlayerState = nullptr;

		UE_LOG(LogTemp, Warning, TEXT("MOVED! (From move assignment)"));
		
		return *this;

	}


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;



};

/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(FWidgetControllerParams&& WCParams);
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();

protected:
	FWidgetControllerParams WidgetControllerParams;

};
