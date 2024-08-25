#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HotbarWidget.generated.h"

UCLASS()
class SURVIVAL_V3_API UHotbarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UHotbarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UItemContainerGrid> ItemContainerGrid;
};
