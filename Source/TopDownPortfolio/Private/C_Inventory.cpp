#include "C_Inventory.h"

UC_Inventory::UC_Inventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UC_Inventory::BeginPlay()
{
	Super::BeginPlay();
}