#pragma once

class IWindowInterface;

class Core
{
public:
	Core(IWindowInterface* InWindow);
	void StartEngine();
private:
	float LastTime = 0.0f;
	IWindowInterface* InWindow;
};