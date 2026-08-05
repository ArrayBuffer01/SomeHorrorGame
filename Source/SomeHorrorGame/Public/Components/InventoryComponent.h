// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, AItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, AItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSelected, AItem*, Item);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOMEHORRORGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int AddItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SelectNextItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SelectPreviousItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SelectItemByIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int GetFirstItemIndex() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int FindFreeSlot() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool SelectItem(AItem* Item);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<TObjectPtr<AItem>> Items;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int CurrentItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<AItem> CurrentItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int MaxInventorySize;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
