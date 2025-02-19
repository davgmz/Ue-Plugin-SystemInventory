//Copyright(c) 2022, Viktor.F.P
#pragma once
#include "InventoryUMG/InventoryPanelSlot.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "InventoryUMG/InventoryPanel.h"

UInventoryPanelSlot::UInventoryPanelSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
	,ParentPanel(nullptr)
	,IndexItem(-1)
	,ZOrder(0)
{
}

void UInventoryPanelSlot::SetMargin(FMargin NewMargin) {
	
	Transform.Offsets = NewMargin;

	if (Slot) 
		Slot->Offset(Transform.Offsets);
}

void UInventoryPanelSlot::ChangeSlot(FInventorySlot NewData) {

	OnChangedSlot.Broadcast(IndexItem, NewData);
}

void UInventoryPanelSlot::BuildSlot(TSharedRef<SConstraintCanvas> GridPanel)
{
	ParentPanel = Cast<UInventoryPanel>(Parent);

	GridPanel->AddSlot()
		.Alignment(FVector2D(0.0f))
		.AutoSize(false)
		.Anchors(FAnchors(0.0f))
		.Expose(Slot)
		[
			Content == nullptr ? SNullWidget::NullWidget : Content->TakeWidget()
		];
}

void UInventoryPanelSlot::SetZOrder(int32 InZOrder)
{
	ZOrder = InZOrder;

	if (Slot)
		Slot->ZOrder(InZOrder);
}

void UInventoryPanelSlot::SetAnchors(FAnchors Anchors)
{
	Transform.Anchors = Anchors;

	if (Slot)
		Slot->Anchors(Transform.Anchors);
}

void UInventoryPanelSlot::SetIndexItem(int32 NewIndex)
{
	if (NewIndex == INDEX_NONE || !Slot) return;

	IndexItem = NewIndex;

	OnChangedSlot.Broadcast(IndexItem, ParentPanel->Inventory->Items[IndexItem]);
}

void UInventoryPanelSlot::SynchronizeProperties() {

	if (IndexItem == INDEX_NONE || !Slot) return;

	FInventorySlot L_Slot = ParentPanel->Inventory->Items[IndexItem];
	FIntPoint L_SlotSize = L_Slot.GetSize();
	OnChangedSlot.Broadcast(IndexItem, ParentPanel->Inventory->Items[IndexItem]);
}