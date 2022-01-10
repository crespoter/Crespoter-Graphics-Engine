#pragma once
#include <iostream>

class CGameObject;
class IComponent
{
public:
	/**
	* Overridable function that is executed once after actor creation
	*/
	virtual void Start() {};

	/**
	* Updates function that is executed every frame of rendering.
	*/
	virtual void Update(float DeltaTime) {};

	/**
	* Updates the parent game object. Components without a parent may not work as expected.
	*/
	void UpdateParent(CGameObject* InParentGameObject);

	/**
	* Fetches the name of the component
	*/
	std::string GetName() const;

protected:
	IComponent(const std::string InComponentName);
	CGameObject* ParentGameObject = nullptr;
	std::string ComponentName = "";
	bool bShouldUpdate = false;
};