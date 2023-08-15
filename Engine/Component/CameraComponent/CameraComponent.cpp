#include "CameraComponent.h"
#include "../Component.h"
#include "../../GameObject/GameObject.h"
#include "../TransformationComponent/TransformationComponent.h"
#include "../../Window/WindowInterface.h"
#include "../../ServiceLocator/ServiceLocator.h"

#include <algorithm>

CCameraComponent::CCameraComponent() : IComponent(CAMERA_COMPONENT_NAME)
{	
	// If there is no camera registered, register this as the active camera
	if (ServiceLocator::GetActiveCamera() == nullptr)
	{
		ServiceLocator::Provide(this);
	}
}

glm::mat4 CCameraComponent::GetViewMatrix() const
{
	const glm::vec3 Position = ParentTransformationComponent->GetPosition();
	return glm::lookAt(Position, Position + CameraForward, CameraUp);
}

glm::mat4 CCameraComponent::GetProjectionMatrix(const IWindowInterface* InWindow) const
{
	return glm::perspective(glm::radians(Fov), InWindow->GetAspectRatio(), MinDistance, MaxDistance);
}

void CCameraComponent::Start()
{
	IComponent::Start();
	assert(ParentGameObject != nullptr);
	CTransformationComponent* TransformationComponent = ParentGameObject->GetComponent<CTransformationComponent>();
	assert(TransformationComponent != nullptr);
	ParentTransformationComponent = TransformationComponent;
}

void CCameraComponent::Update(float DeltaTime)
{
	IComponent::Update(DeltaTime);
	CameraForward.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	CameraForward.y = sin(glm::radians(Pitch));
	CameraForward.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	glm::vec3 CameraRight = glm::normalize(glm::cross(CameraForward, WorldUp));
	CameraUp = glm::normalize(glm::cross(CameraRight, CameraForward));
}

void CCameraComponent::SetWorldUp(const glm::vec3& InWorldUp)
{
	WorldUp = InWorldUp;
}


void CCameraComponent::UpdateRotationEulerAngles(float NewYaw, float NewPitch)
{
	Yaw = NewYaw;
	Pitch = NewPitch;
}

void CCameraComponent::IncrementRotationEulerAngles(float YawIncrement, float PitchIncrement)
{
	Yaw += YawIncrement;
	Pitch += PitchIncrement;
	Pitch = std::clamp(Pitch, -89.0f, 89.0f);
}

glm::vec3 CCameraComponent::GetCameraForward() const
{
	return CameraForward;
}

glm::vec3 CCameraComponent::GetCameraUp() const
{
	return CameraUp;
}

glm::vec3 CCameraComponent::GetCameraRight() const
{
	return glm::normalize(glm::cross(CameraForward, WorldUp));
}

CTransformationComponent* CCameraComponent::GetParentTransformationComponent() const
{
	return ParentTransformationComponent;
}

void CCameraComponent::SetFov(float NewFov)
{
	Fov = NewFov;
}

void CCameraComponent::SetMinAndMaxDistance(float InMinDistance, float InMaxDistance)
{
	MinDistance = InMinDistance;
	MaxDistance = InMaxDistance;
}

