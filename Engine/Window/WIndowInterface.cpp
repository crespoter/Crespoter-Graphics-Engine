#include "WindowInterface.h"

bool IWindowInterface::IsInitialized() const
{
	return bIsInitialized;
}

IWindowInterface::FMousePosition::FMousePosition(float PosX, float PosY)
{
	this->PosX = PosX;
	this->PosY = PosY;
}
