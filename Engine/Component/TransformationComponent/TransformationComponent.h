#pragma once
#include "Engine/Component/Component.h"
#include <bitset>
#include <glm/gtx/vec_swizzle.hpp>
#include <glm/gtc/quaternion.hpp>

namespace
{
	const std::string TRANSFORMATION_COMPONENT_NAME = "Transformation Component";
}

class CTransformationComponent : public IComponent
{

public:
	CTransformationComponent();

	virtual void Update(float DeltaTime) override;

	void GetModelMatrix(glm::mat4& outModelMatrix) const;

	void MoveTo(const glm::vec3& InNewPosition);

	void Translate(const glm::vec3& InTranslationVector);

	void Scale(const glm::vec3& InScaleVector);

	void Rotate(const glm::vec3& InRotationAxis, float Angle);

	glm::vec3 GetPosition();

	glm::vec3 GetScale();

	glm::quat GetOrientation();

private:
	// Quaternion to represent current orientation
	glm::quat Orientation = glm::quat();

	// x,y,z float values represent scale along the direction of X, Y and Z axises
	glm::vec3 ScaleVector = glm::vec3(1.0f);

	/**
	* TransformationMatrix for the object.
	*/
	glm::mat4 TransformationMatrix = glm::mat4(1.0f);

	/**
	* Calculates and assigns the rotation and scale to the member variables
	*/
	void CalculateRotationAndScale();
};