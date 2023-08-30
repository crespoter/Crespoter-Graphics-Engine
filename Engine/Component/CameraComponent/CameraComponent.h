#pragma once
#include <glm/glm.hpp>
#include "Engine/Component/Component.h"

class CTransformationComponent;
class IWindowInterface;

namespace
{
	const std::string CAMERA_COMPONENT_NAME = "Camera Component";
}


class CCameraComponent : public IComponent
{
public:
	CCameraComponent();

	void GetViewMatrix(glm::mat4& outViewMatrix) const;

	glm::mat4 GetProjectionMatrix(const IWindowInterface* InWindow) const;

	virtual void Start() override;

	virtual void Update(float DeltaTime) override;

	void SetWorldUp(const glm::vec3 &InWorldUp);


	void UpdateRotationEulerAngles(const float NewYaw, const float NewPitch);

	/**
	 * Increments pitch and yaw by values provided. Pitch is locked at 90 degrees.
	 */
	void IncrementRotationEulerAngles(const float YawIncrement, const float PitchIncrement);

	const glm::vec3& GetCameraForward() const;

	const glm::vec3& GetCameraUp() const;

	glm::vec3 GetCameraRight() const;

	// TODO: Should be const after updating to new transformation logic
	CTransformationComponent* GetParentTransformationComponent() const;

	/**
	 * Sets the new fov of the camera
	*/
	void SetFov(float NewFov);

	void SetMinAndMaxDistance(float InMinDistance, float InMaxDistance);

protected:

	// TODO: Transformation component is not const because getting position requires 
	// a lazy loading of position from the transformation matrix. Update the transformation
	// component code to update position whenever the transformation is updated.

	CTransformationComponent* ParentTransformationComponent = nullptr;
	glm::vec3 CameraForward = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float Yaw = 0;
	float Pitch = 0;
	float Fov = 90.0f;
	float MinDistance = 0.1f;
	float MaxDistance = 100.0f;
};