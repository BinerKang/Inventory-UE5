// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IconButtonUserWidget.generated.h"

class UInvWidgetController;
enum class EPickableItemCategory : uint8;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnIconButtonClickedSignature, const int32)

class UTextBlock;
class USizeBox;
class UButton;
/**
 * 
 */
UCLASS()
class INVENTORY_API UIconButtonUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetIndex(const int32 NewIndex, const UInvWidgetController* InvWC);
	
	void UpdateChosen(const int32 ChosenIndex) const;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Button;

	FOnIconButtonClickedSignature OnIconButtonClickedDelegate;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	float NormalSize = 50.f;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	float ChosenSize = 56.f;

	/* This Array Must same with UContentSwitcherUserWidget  ContentTypeCount*/
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TArray<EPickableItemCategory> ECategories;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> BoxRoot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextCategory;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	int32 Index;

	void SetBoxSize(const float Size) const;

	UFUNCTION()
	void BroadcastClickEvent();
};
