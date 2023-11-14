// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ContentSwitcherUserWidget.generated.h"

class UActionMenuUserWidget;
enum class EPickableItemName : uint8;
class UItemDetailUserWidget;
class UItemSlotUserWidget;
class UInvWidgetController;
struct FOwnedItemCategory;
class UWrapBox;
class UIconButtonUserWidget;
class UWidgetSwitcher;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class INVENTORY_API UContentSwitcherUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetInvWidgetController(UInvWidgetController* InWidgetController);
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TSubclassOf<UIconButtonUserWidget> IconButtonWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TSubclassOf<UItemSlotUserWidget> ItemSlotWidgetClass;

	/* This ContentTypeCount Must same with UIconButtonUserWidget Array*/
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	int32 ContentTypeCount = 3;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	int32 ChosenCategoryIndex = 0;

	void UpdateInventoryContainer(const TArray<FOwnedItemCategory>& AllItems);
	
	EPickableItemName ChosenItemID;
	
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> IconGroup;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UItemDetailUserWidget> ItemDetail;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UActionMenuUserWidget> ActionMenu;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWrapBox> WeaponContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWrapBox> ShieldContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWrapBox> EatableContainer;
	
	TArray<UIconButtonUserWidget*> AllIconButtonWidgets;

	UPROPERTY()
	TObjectPtr<UInvWidgetController> InvWC;
	
	void UpdateChosenIndex();
	

};
