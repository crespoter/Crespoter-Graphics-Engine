#pragma once
#include "../Component.h"
#include <glm/gtx/vec_swizzle.hpp>

namespace
{
	const std::string TRANSFORMATION_COMPONENT_NAME = "Transformation Component";
}

class CTransformationComponent : public IComponent
{
private:

	// Current position
	glm::vec3 Position;
	
	// x,y,z float values represent rotation around x,y and z around the object center
	glm::vec3 Rotation = glm::vec3(0.0f);

	// x,y,z float values represent scale along the direction of X, Y and Z axises
	glm::vec3 ScaleVector = glm::vec3(1.0f);

public:
	CTransformationComponent();
	
	/**
	 * Returns the model matrix for the current configuration of position, rotation and Scale
	 */
	glm::mat4 GetModelMatrix();

	/**
	 * Moves to the provided position in the world space 
	*/
	void MoveTo(const glm::vec3 &InNewPosition);
	
	/**
	 * Translate the object by the translation vector
	 */
	void Translate(const glm::vec3 &InTranslationVector);

	/**
	 * Scales along x,y and z axises as per x,y,z coordinate of the vec3
	*/
	void Scale(const glm::vec3 &InScaleVector);

	// TODO: Handle Rotations


	/**
	 * Returns current position
	*/
	glm::vec3 GetPosition() const;
};