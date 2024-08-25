#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MainUILayout.generated.h"

UCLASS()
class SURVIVAL_V3_API UMainUILayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<class UDefaultHUDLayout> DefaultHUDLayout;

	UPROPERTY()
	TObjectPtr<class UGameInventoryLayout> GameInventoryLayout;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCommonActivatableWidgetStack> GameHUDStack;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> GameInventoryStack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables);
	TSubclassOf<class UCommonActivatableWidget> ActivatableWidgetSubclass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables);
	TSubclassOf<UCommonActivatableWidget> GameInventoryWidgetSubclass;

	void PushDefaultHUDLayout();

	void PushGameInventoryLayout();
};
