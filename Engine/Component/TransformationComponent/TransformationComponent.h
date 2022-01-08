#pragma once
#include "../Component.h"
#include <bitset>
#include <glm/gtx/vec_swizzle.hpp>
#include <glm/gtc/quaternion.hpp>

namespace
{
	const std::string TRANSFORMATION_COMPONENT_NAME = "Transformation Component";
}

class CTransformationComponent : public IComponent
{
private:
	enum TRANSFORMATION_STATE
	{
		POSITION_INDEX = 0,
		OTHER_INDEX = 1
	};

	// Current position
	glm::vec3 Position = glm::vec3(0.0f);
	

	// Quaternion to represent current orientation
	glm::quat Orientation = glm::quat();

	// x,y,z float values represent scale along the direction of X, Y and Z axises
	glm::vec3 ScaleVector = glm::vec3(1.0f);

	/**
	* TransformationMatrix for the object.
	*/
	glm::mat4 TransformationMatrix = glm::mat4(1.0f);

	/**
	* Bitset used to track whether position, rotation and scale has already been calculated for this frame.
	* Index 0 -> True if position is already calculated for this frame. False otherwise
	* Index 1 -> True if position, rotation and scale have been calculated for this frame. False Otherwise
	*/
	std::bitset<2> TransformationCalculationStates;

	/**
	* Calculates and assigns the rotation and scale to the member variables
	*/
	void CalculateRotationAndScale();

public:
	CTransformationComponent();
	
	void Update(float DeltaTime) override;

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

	/**
	* Rotates around the given axis by Angle degrees
	*/
	void Rotate(const glm::vec3& InRotationAxis, float Angle);

	/**
	 * Returns current position
	*/
	glm::vec3 GetPosition();

	/**
	* Returns Scale
	*/
	glm::vec3 GetScale();

	/**
	* Returns Orientation
	*/
	glm::quat GetOrientation();
};