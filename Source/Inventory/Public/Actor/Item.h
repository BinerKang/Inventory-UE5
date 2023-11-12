// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/PickableItemDataAsset.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

enum class EPickableItemName : uint8;
class UBoxComponent;

UCLASS()
class INVENTORY_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable)
	FPickableItemInfo GetItemInfo() const;

	FORCEINLINE EPickableItemName GetItemID() const { return EItemID; }
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom")
	EPickableItemName EItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom")
	TObjectPtr<UPickableItemDataAsset> PickableItemDataAsset;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, Category="Custom")
	TObjectPtr<USoundBase> DestroySound;
	
	UPROPERTY(EditAnywhere, Category="Custom")
	bool bDoTick = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|Sine Parameters")
	float TimeConstant = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|Sine Parameters")
	float Amplitude = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float RotationRate = 0.f;

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private:
	float TransformedSin() const;
	float TransformedCos() const;
	float RunningTime = 0.f;
};
