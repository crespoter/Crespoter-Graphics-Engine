#pragma once
#include "Engine/Component/Component.h"
#include <glm/glm.hpp>

class CModel;
class CTransformationComponent;

namespace
{
	std::string DEFAULT_NAME = "RenderComponent";
}

class CRenderComponent : public IComponent
{
public:
	explicit CRenderComponent(const std::string& ComponentName = DEFAULT_NAME);
	
	virtual ~CRenderComponent();

	virtual void Start() override;

	// Sets and loads the model
	void SetModel(const std::string& ModelPath);

	void Render();

	void GetModelMatrix(glm::mat4& outModelMatrix);

private:
	std::unique_ptr<CModel> ModelObject{ nullptr };
	
	CTransformationComponent* ParentTransformationComponent{ nullptr };
};