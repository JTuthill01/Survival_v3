#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftingWindow.generated.h"

UCLASS()
class SURVIVAL_V3_API UCraftingWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UCraftingWindow(const FObjectInitializer& Object);
};
