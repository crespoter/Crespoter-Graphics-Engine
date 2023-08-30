#include "TransformationComponent.h"
#include <glm/gtx/matrix_decompose.hpp>



CTransformationComponent::CTransformationComponent() : IComponent(TRANSFORMATION_COMPONENT_NAME)
{
}

void CTransformationComponent::Update(float DeltaTime)
{
	IComponent::Update(DeltaTime);
}

void CTransformationComponent::GetModelMatrix(glm::mat4& outModelMatrix) const
{
	outModelMatrix = TransformationMatrix;
}

void CTransformationComponent::MoveTo(const glm::vec3 &InNewPosition)
{
	/*
	*	[][][][x]
	*	[][][][y]
	*	[][][][z]
	*	[][][][1.0f]
	*/
	TransformationMatrix[3] = glm::vec4(InNewPosition, 1.0f);
}

void CTransformationComponent::Translate(const glm::vec3 &InTranslationVector)
{
	/*
	*	[][][][x1 + x2]
	*	[][][][y1 + y1]
	*	[][][][z1 + z2]
	*	[][][][1.0f]
	*/
	TransformationMatrix = glm::translate(TransformationMatrix, InTranslationVector);
}

void CTransformationComponent::Scale(const glm::vec3 &InScaleVector)
{
	// TODO: Move the object to origin with no rotation before applying scaling.
	// currently, scaling, translation and rotations should be done in a very specific order
	// which makes changing these values during a run loop cumbersome.
	TransformationMatrix = glm::scale(TransformationMatrix, InScaleVector);
}


void CTransformationComponent::Rotate(const glm::vec3& InRotationAxis, float Angle)
{
	TransformationMatrix = glm::rotate(TransformationMatrix, glm::radians(Angle), InRotationAxis);
}



glm::vec3 CTransformationComponent::GetPosition()
{
	return glm::vec3(TransformationMatrix[3]);
}

// TODO: Find a way around calculating orientation and scale everytime they are required.

glm::quat CTransformationComponent::GetOrientation()
{
	CalculateRotationAndScale();
	return Orientation;
}

glm::vec3 CTransformationComponent::GetScale()
{
	CalculateRotationAndScale();
	return ScaleVector;
}

void CTransformationComponent::CalculateRotationAndScale()
{
	glm::vec3 Skew;
	glm::vec4 Perspective;
	glm::vec3 Position = GetPosition();
	glm::decompose(TransformationMatrix, ScaleVector, Orientation, Position, Skew, Perspective);
	Orientation = glm::conjugate(Orientation);
}