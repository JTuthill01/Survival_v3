#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Enums/ItemType/ItemType.h"
#include "DraggedItem.generated.h"

UCLASS()
class SURVIVAL_V3_API UDraggedItem : public UCommonButtonBase
{
	GENERATED_BODY()

public:

	UDraggedItem(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

#pragma region Setters
	FORCEINLINE void SetImageIcon(const TObjectPtr<UTexture2D>& InTexture) { ImageIcon = InTexture;}
	FORCEINLINE void SetTextTop(const FText& InText) { TextTop = InText; }
	FORCEINLINE void SetItemType(const EItemType InType) { ItemType = InType; }
	FORCEINLINE void SetQuantity(const FText& QText) { Quantity = QText; }
	FORCEINLINE void SetUsesAmmo(const bool& Val) { bUsesAmmo = Val; }
	FORCEINLINE void SetCurrentAmmo(const int32& NewVal) { CurrentAmmo = NewVal; }
	FORCEINLINE void SetMaxAmmo(const int32& NewMaxVal) { MaxAmmo = NewMaxVal; }
	FORCEINLINE void SetCurrentHP(const int32& NewHPVal) { CurrentHP = NewHPVal; }
	FORCEINLINE void SetMaxHP(const int32& NewMaxHPVal) { MaxHP = NewMaxHPVal; }
	FORCEINLINE void SetWeight(const FText& InTextWeight) { Weight = InTextWeight; }
#pragma endregion

#pragma region Bindings
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> SlotStyle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TopText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BottomText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WeightText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ItemHP;

#pragma endregion

#pragma region Variables
	UPROPERTY()
	TObjectPtr<UTexture2D> ImageIcon;
	
	FText TextTop;
	FText Quantity;
	FText Weight;

	int32 CurrentAmmo;
	int32 MaxAmmo;
	int32 CurrentHP;
	int32 MaxHP;

	EItemType ItemType;

	bool bUsesAmmo;
#pragma endregion

private:
	void SetResourceText();
	void SetEquippableText();
	void SetArmorText();
	void SetConsumableText();
};
