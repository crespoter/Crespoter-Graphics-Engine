#pragma once
#include "../Component.h"
#include <glm/glm.hpp>

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

	glm::mat4 GetModelMatrix();

private:
	std::unique_ptr<CModel> ModelObject{ nullptr };
};