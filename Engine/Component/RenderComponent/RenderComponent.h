#pragma once
#include "../Component.h"

class CModel;

namespace
{
	std::string DEFAULT_NAME = "RenderComponent";
}
class CRenderComponent : public IComponent
{
public:
	CRenderComponent(const std::string& ComponentName = DEFAULT_NAME);
	
	~CRenderComponent();

	// Sets the model path and loads the model
	void SetModel(const std::string& ModelPath);

	void Render();
private:
	CModel* ModelObject = nullptr;
};