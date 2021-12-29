#pragma once
#include <iostream>

class CGameObject;
class IComponent
{
protected:
	IComponent(const std::string InComponentName);
	CGameObject* ParentGameObject = nullptr;
	std::string ComponentName = "";
	bool bShouldUpdate = false;
public:
	virtual void Start() {};
	virtual void Update(float DeltaTime) {};
	void UpdateParent(CGameObject* InParentGameObject);
	std::string GetName() const;
};