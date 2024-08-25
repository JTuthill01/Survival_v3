#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemCollectedWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceTextBlockChange, int32, NewInt, FText, NewText);

UCLASS()
class SURVIVAL_V3_API UItemCollectedWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UItemCollectedWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void SetVariables(const TObjectPtr<UTexture2D>& InIcon, const int32 InResourceQuantity, const FText& InResourceName);
#pragma region Functions
	UFUNCTION()
	void SetResourceText(int32 NewQuantity, FText NewResource);

	UFUNCTION()
	void DestroySelf();
#pragma endregion
	UPROPERTY(BlueprintAssignable)
	FOnResourceTextBlockChange OnResourceTextBlockChange;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> ResourceIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ResourceTextBlock;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeOut;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	TObjectPtr<UTexture2D> ResourceImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	int32 ResourceQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	FText ResourceName;
};
