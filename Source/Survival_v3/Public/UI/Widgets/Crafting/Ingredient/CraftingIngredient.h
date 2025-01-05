#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftingIngredient.generated.h"

UCLASS()
class SURVIVAL_V3_API UCraftingIngredient : public UUserWidget
{
	GENERATED_BODY()

public:
	UCraftingIngredient(const FObjectInitializer& Object);

	virtual void NativeConstruct() override;

#pragma region Getters

	TObjectPtr<UTexture2D> GetResourceIcon() const { return ResourceIcon; }

	FText GetResourceText() const { return ResourceText; }

	int32 GetResourceQuantity() const { return ResourceQuantity; }

#pragma endregion

#pragma region Setters

	void SetResourceName();

	void SetResourceText(const FText& InResourceText) { ResourceText = InResourceText; }
	
	void SetResourceIcon(const TObjectPtr<UTexture2D>& InIcon) { ResourceIcon = InIcon; }
	
	void SetResourceQuantity(const int32& InQuantity) { ResourceQuantity = InQuantity; }

#pragma endregion

#pragma region Bindings

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> ResourceImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ResourceName;

#pragma endregion

private:
	UPROPERTY()
	TObjectPtr<UTexture2D> ResourceIcon;
	
	FText ResourceText;

	int32 ResourceQuantity;
};
