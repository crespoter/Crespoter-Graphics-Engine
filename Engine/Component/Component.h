#pragma once
#include <iostream>

class CGameObject;
class IComponent
{
private:
	// Disables initialization without parameters
	IComponent() {};
protected:
	IComponent(const std::string InComponentName);
	CGameObject* ParentGameObject = nullptr;
	std::string ComponentName = "";
	bool bShouldUpdate = false;
public:
	virtual void Start() {};
	virtual void Update(float DeltaTime) {};
	void UpdateParent(CGameObject* InParentGameObject);
};