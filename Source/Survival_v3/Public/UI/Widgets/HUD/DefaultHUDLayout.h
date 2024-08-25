#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "DefaultHUDLayout.generated.h"

class UVerticalBox;

UCLASS()
class SURVIVAL_V3_API UDefaultHUDLayout : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE TObjectPtr<class UItemCollectedWidget> GetItemCollectedWidget() const { return ItemCollectedWidget; }
	
	void AddResources(UTexture2D* Icon, int32 Quantity, const FText& Name);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHotbarWidget> WBP_Hotbar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> ResourcesCollected;

private:
	UPROPERTY()
	TObjectPtr<UItemCollectedWidget> ItemCollectedWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemCollectedWidget> ItemCollectedClassRef;
};
