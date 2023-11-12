// Copyright Jack Kong.


#include "UI/Widget/UserWidgetBase.h"


void UUserWidgetBase::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
}

void UUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	// Listen Keyboard 
	SetIsFocusable(true);
}
