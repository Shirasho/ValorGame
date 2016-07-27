// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorMainInterfaceWidget.h"

#include "ValorPlayerController.h"

void UValorMainInterfaceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		
	}
}


void UValorMainInterfaceWidget::OnAbilityAction1Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilityAction1Pressed();
	}
}


void UValorMainInterfaceWidget::OnAbilityAction1Released()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilityAction1Released();
	}
}


void UValorMainInterfaceWidget::OnAbilityAction2Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilityAction2Pressed();
	}
}


void UValorMainInterfaceWidget::OnAbilityAction2Released()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilityAction2Released();
	}
}


void UValorMainInterfaceWidget::OnAbilityAction3Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilityAction3Pressed();
	}
}


void UValorMainInterfaceWidget::OnAbilityAction3Released()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilityAction3Released();
	}
}


void UValorMainInterfaceWidget::OnAbilityAction4Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilityAction4Pressed();
	}
}


void UValorMainInterfaceWidget::OnAbilityAction4Released()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilityAction4Released();
	}
}


void UValorMainInterfaceWidget::OnAbilitySpell1Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilitySpell1Pressed();
	}
}


void UValorMainInterfaceWidget::OnAbilitySpell1Released()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilitySpell1Released();
	}
}


void UValorMainInterfaceWidget::OnAbilitySpell2Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilitySpell2Pressed();
	}
}


void UValorMainInterfaceWidget::OnAbilitySpell2Released()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnAbilitySpell2Released();
	}
}


void UValorMainInterfaceWidget::OnUseItem1Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnUseItem1Pressed();
	}
}


void UValorMainInterfaceWidget::OnUseItem2Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnUseItem2Pressed();
	}
}


void UValorMainInterfaceWidget::OnUseItem3Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnUseItem3Pressed();
	}
}


void UValorMainInterfaceWidget::OnCameraZoomInPressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraZoomInPressed();
	}
}


void UValorMainInterfaceWidget::OnCameraZoomOutPressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraZoomOutPressed();
	}
}


void UValorMainInterfaceWidget::OnCameraCenterPressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraCenterPressed();
	}
}


void UValorMainInterfaceWidget::OnCameraCenterReleased()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraCenterReleased();
	}
}


void UValorMainInterfaceWidget::OnCameraPanLeftPressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraPanLeftPressed();
	}
}


void UValorMainInterfaceWidget::OnCameraPanRightPressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraPanRightPressed();
	}
}


void UValorMainInterfaceWidget::OnCameraPanUpPressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraPanUpPressed();
	}
}


void UValorMainInterfaceWidget::OnCameraPanDownPressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraPanDownPressed();
	}
}


void UValorMainInterfaceWidget::OnCameraPanPrecise1Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraPanPrecise1Pressed();
	}
}


void UValorMainInterfaceWidget::OnCameraPanPrecise2Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraPanPrecise2Pressed();
	}
}


void UValorMainInterfaceWidget::OnCameraPanPrecise3Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraPanPrecise3Pressed();
	}
}


void UValorMainInterfaceWidget::OnCameraPanPrecise4Pressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnCameraPanPrecise4Pressed();
	}
}


void UValorMainInterfaceWidget::OnToggleMenuPressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnToggleMenuPressed();
	}
}


void UValorMainInterfaceWidget::OnToggleScoreboardPressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnToggleScoreboardPressed();
	}
}


void UValorMainInterfaceWidget::OnPushToTalkPressed()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnPushToTalkPressed();
	}
}


void UValorMainInterfaceWidget::OnPushToTalkReleased()
{
	AValorPlayerController* OwnerController = Cast<AValorPlayerController>(GetOwningPlayer());
	if (OwnerController)
	{
		OwnerController->OnPushToTalkReleased();
	}
}