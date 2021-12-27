#include "TransformationComponent.h"
#include <glm/ext/matrix_transform.inl>

CTransformationComponent::CTransformationComponent() : IComponent(TRANSFORMATION_COMPONENT_NAME)
{
}

glm::mat4 CTransformationComponent::GetModelMatrix()
{
	glm::mat4 TransformationMatrix(1.0f);
	TransformationMatrix = glm::scale(TransformationMatrix, ScaleVector);
	// TODO: Rotation

	TransformationMatrix = glm::translate(TransformationMatrix, Position);

	return TransformationMatrix;
}

void CTransformationComponent::MoveTo(const glm::vec3 &InNewPosition)
{
	Position = InNewPosition;
}

void CTransformationComponent::Translate(const glm::vec3 &InTranslationVector)
{
	Position += InTranslationVector;
}

void CTransformationComponent::Scale(const glm::vec3 &InScaleVector)
{
	ScaleVector = InScaleVector;
}
