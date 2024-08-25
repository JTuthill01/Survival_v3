#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CommonButton.generated.h"

UCLASS()
class SURVIVAL_V3_API UCommonButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetUseText(const bool Val) { bUseText = Val; }
	FORCEINLINE void SetButtonText(const FText& NewText) { DisplayText = NewText; }
	
	UCommonButton(const FObjectInitializer& Object);
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ButtonText;

	FText DisplayText;

	bool bUseText;
};
