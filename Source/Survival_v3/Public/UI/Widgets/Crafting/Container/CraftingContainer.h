#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "Structs/Recipes/ItemRecipes.h"
#include "CraftingContainer.generated.h"

UCLASS()
class SURVIVAL_V3_API UCraftingContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	UCraftingContainer(const FObjectInitializer& Object);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	EContainerType ContainerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	ECraftingType CraftingType;

	void InitSlots();
};
