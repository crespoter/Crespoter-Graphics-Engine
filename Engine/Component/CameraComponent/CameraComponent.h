#pragma once
#include <glm/glm.hpp>
#include "../Component.h"

class CTransformationComponent;

namespace
{
	const std::string CAMERA_COMPONENT_NAME = "Camera Component";
}

class CCameraComponent : public IComponent
{
private:
	CTransformationComponent* ParentTransformationComponent = nullptr;
	glm::vec3 CameraForward = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float Yaw = 0;
	float Pitch = 0;

	glm::mat4 ViewMatrix = glm::mat4(1.0f);
public:
	CCameraComponent();
	glm::mat4 GetViewMatrix() const;

	void Start() override;

	void Update(float DeltaTime) override;

	void SetWorldUp(const glm::vec3 &InWorldUp);

	/**
	 * Updates the euler angles of rotation for the camera
	 */
	void UpdateRotationEulerAngles(float NewYaw, float NewPitch);

	/**
	 * Increments pitch and yaw by values provided
	 */
	void IncrementRotationEulerAngles(float YawIncrement, float PitchIncrement);

	glm::vec3 GetCameraForward() const;

	glm::vec3 GetCameraUp() const;

	glm::vec3 GetCameraRight() const;

	CTransformationComponent* GetParentTransformationComponent() const;
};