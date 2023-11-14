// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interface/PickupInterface.h"
#include "Inventory/Inventory.h"
#include "HeroCharacter.generated.h"

class URectLightComponent;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class INVENTORY_API AHeroCharacter : public ACharacterBase, public IPickupInterface
{
	GENERATED_BODY()

public:
	AHeroCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRep_PlayerState() override;
	
	/* PickupInterface  */
	virtual void AddMoney(const int32 InAmount) override;
	virtual void SetOverlappingItem(AItem* Item) override;
	FORCEINLINE virtual AItem* GetOverlappingItem() override { return OverlappingItem; }
	virtual void AddToInventory() override;
	/* End PickupInterface  */

	void OpenLight();
	void CloseLight();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneCaptureComponent2D> SceneCapture;

	/* Light For RenderCapture  */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URectLightComponent> MainLight;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URectLightComponent> FillLight;
	
private:

	void InitHUD()  const;

	UPROPERTY(ReplicatedUsing=OnRep_OverlappingItem)
	TObjectPtr<AItem> OverlappingItem = nullptr;

	UFUNCTION()
	void OnRep_OverlappingItem(AItem* LastOverlappingItem);

	void ChangePickupWidgetVisibility() const;
	void SetPickupWidgetVisibility(bool bIsShow, EPickableItemName EItemID = EPickableItemName::EPIN_Empty) const;
};
