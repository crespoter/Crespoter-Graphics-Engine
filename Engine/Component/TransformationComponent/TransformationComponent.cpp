#include "TransformationComponent.h"
#include <glm/gtx/matrix_decompose.hpp>



CTransformationComponent::CTransformationComponent() : IComponent(TRANSFORMATION_COMPONENT_NAME)
{
}

void CTransformationComponent::Update(float DeltaTime)
{
	IComponent::Update(DeltaTime);
	TransformationCalculationStates.reset();
}

glm::mat4 CTransformationComponent::GetModelMatrix()
{
	return TransformationMatrix;
}

void CTransformationComponent::MoveTo(const glm::vec3 &InNewPosition)
{
	TransformationMatrix[3] = glm::vec4(InNewPosition, 1.0f);
}

void CTransformationComponent::Translate(const glm::vec3 &InTranslationVector)
{
	TransformationMatrix = glm::translate(TransformationMatrix, InTranslationVector);
}

void CTransformationComponent::Scale(const glm::vec3 &InScaleVector)
{
	TransformationMatrix = glm::scale(TransformationMatrix, InScaleVector);
}


void CTransformationComponent::Rotate(const glm::vec3& InRotationAxis, float Angle)
{
	TransformationMatrix = glm::rotate(TransformationMatrix, glm::radians(Angle), InRotationAxis);
}




glm::vec3 CTransformationComponent::GetPosition()
{
	if (TransformationCalculationStates[TRANSFORMATION_STATE::POSITION_INDEX])
	{
		return Position;
	}
	Position = glm::vec3(TransformationMatrix[3]);
	TransformationCalculationStates[TRANSFORMATION_STATE::POSITION_INDEX] = true;
	return Position;
}

glm::quat CTransformationComponent::GetOrientation()
{
	if (TransformationCalculationStates[TRANSFORMATION_STATE::OTHER_INDEX])
	{
		return Orientation;
	}
	CalculateRotationAndScale();
	TransformationCalculationStates[TRANSFORMATION_STATE::OTHER_INDEX] = true;
	return Orientation;
}

glm::vec3 CTransformationComponent::GetScale()
{
	if (TransformationCalculationStates[TRANSFORMATION_STATE::OTHER_INDEX])
	{
		return ScaleVector;
	}
	CalculateRotationAndScale();
	TransformationCalculationStates[TRANSFORMATION_STATE::OTHER_INDEX] = true;
	return ScaleVector;
}

void CTransformationComponent::CalculateRotationAndScale()
{
	glm::vec3 Skew;
	glm::vec4 Perspective;
	glm::decompose(TransformationMatrix, ScaleVector, Orientation, Position, Skew, Perspective);
	Orientation = glm::conjugate(Orientation);
}