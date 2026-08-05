// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	MaxInventorySize = 4;

	Items.SetNum(MaxInventorySize);
}

int UInventoryComponent::AddItem(AItem* Item)
{
	const int FreeSlotIndex = FindFreeSlot();

	if (FreeSlotIndex != INDEX_NONE)
	{
		Items[FreeSlotIndex] = Item;
	}

	return FreeSlotIndex;
}

void UInventoryComponent::RemoveItem(AItem* Item)
{
	const int ItemIndex = Items.Find(Item);

	if (ItemIndex != INDEX_NONE)
	{
		Items[ItemIndex] = nullptr;

		if (CurrentItem == Item)
		{
			CurrentItem = nullptr;
		}
	}
}

void UInventoryComponent::SelectNextItem()
{
	if (Items.Num() == 0) return;
	SelectItemByIndex((CurrentItemIndex + 1) % Items.Num());
}

void UInventoryComponent::SelectPreviousItem()
{
	if (Items.Num() == 0) return;
	SelectItemByIndex((CurrentItemIndex - 1 + Items.Num()) % Items.Num());
}

void UInventoryComponent::SelectItemByIndex(int Index)
{
	if (Items.IsValidIndex(Index))
	{
		CurrentItemIndex = Index;
		CurrentItem = Items[CurrentItemIndex];
	}
}

int UInventoryComponent::GetFirstItemIndex() const
{
	for (int i = 0; i < Items.Num(); ++i)
	{
		if (Items[i])
		{
			return i;
		}
	}

	return 0;
}

bool UInventoryComponent::SelectItem(AItem* Item)
{
	const int ItemIndex = Items.Find(Item);
	if (ItemIndex != INDEX_NONE)
	{
		SelectItemByIndex(ItemIndex);
		return true;
	}
	return false;
}

int UInventoryComponent::FindFreeSlot() const
{
	for (int i = 0; i < Items.Num(); ++i)
	{
		if (!Items[i])
		{
			return i;
		}
	}

	return INDEX_NONE;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

