#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

class IComponent;

/**
 * Building block for any program. Components can be attached to game objects for additional functionalities.
 */
class CGameObject
{
protected:
	// Name of the game object
	std::string Name = "";

	// List of all components attached to this game object.
	std::vector<IComponent*> ComponentsList;

	bool bShouldUpdate = false;
	


public:
	CGameObject(const std::string &InName);
	virtual ~CGameObject();
	
	/**
	 * Called once after object creation. Child classes overriding this method need to call parent function for updates to occur properly
	 */
	virtual void Start();
	
	/**
	 * Called every rendering frame. Child classes overriding this method need to call parent function for updates to occur properly
	 * @param(Delta time): Time passed between current frame and last frame.
	 */
	virtual void Update(float DeltaTime);

	/**
	 * Adds a component to the game object.
	 */
	void AddComponent(IComponent* InComponent);

	template<typename T>
	void AddComponent();

	/**
	 * Gets component specified. If no component matches requirement, it returns nullptr
	*/
	template<typename T>
	T* GetComponent();
};

// Template definitions
template<typename T>
void CGameObject::AddComponent()
{
	assert((std::is_base_of<IComponent, T>::value));
	IComponent* Component = new T();
	ComponentsList.push_back(Component);
	Component->UpdateParent(this);
}


template<typename T>
T* CGameObject::GetComponent()
{
	assert((std::is_base_of<IComponent, T>::value));
	for (auto i = ComponentsList.begin(); i != ComponentsList.end(); i++)
	{
		IComponent* Component = *i;
		T* CastedComponent = dynamic_cast<T*>(Component);
		if (CastedComponent)
		{
			return CastedComponent;
		}
	}
	return nullptr;
}

