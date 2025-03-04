#include "W_Store.h"
#include "Components/ScrollBox.h"

UW_Store::UW_Store(const FObjectInitializer& ObjectInitializer) :
	UW_WindowBase{ ObjectInitializer }, pScrollBoxSlot{}
{
}

UScrollBox* UW_Store::E_GetScrollBox()
{
	return pScrollBoxSlot;
}