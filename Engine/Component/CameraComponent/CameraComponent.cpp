#include "CameraComponent.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/TransformationComponent/TransformationComponent.h"
#include "Engine/Window/WindowInterface.h"
#include "Engine/ServiceLocator/ServiceLocator.h"
#include <algorithm>

CCameraComponent::CCameraComponent() : IComponent(CAMERA_COMPONENT_NAME)
{
	// If there is no camera already registered, register this as the active camera
	// The current architecture enforces that only one camera can be directly accessed
	// from the service locator. Adding additional cameras would require the game client
	// to keep track of the created camera objects.
	if (ServiceLocator::GetActiveCamera() == nullptr)
	{
		ServiceLocator::Provide(this);
	}
}

void CCameraComponent::GetViewMatrix(glm::mat4& outViewMatrix) const
{
	const glm::vec3 Position = ParentTransformationComponent->GetPosition();
	outViewMatrix = glm::lookAt(Position, Position + CameraForward, CameraUp);
}

glm::mat4 CCameraComponent::GetProjectionMatrix(const IWindowInterface* InWindow) const
{
	return glm::perspective(glm::radians(Fov), InWindow->GetAspectRatio(), MinDistance, MaxDistance);
}

void CCameraComponent::Start()
{
	IComponent::Start();
	assert(ParentGameObject);
	// TODO: Change to const once transformation component is updated.
	CTransformationComponent* TransformationComponent = ParentGameObject->GetComponent<CTransformationComponent>();
	assert(TransformationComponent);
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


void CCameraComponent::UpdateRotationEulerAngles(const float NewYaw, const float NewPitch)
{
	Yaw = NewYaw;
	Pitch = NewPitch;
}

void CCameraComponent::IncrementRotationEulerAngles(const float YawIncrement, const float PitchIncrement)
{
	Yaw += YawIncrement;
	Pitch += PitchIncrement;
	Pitch = std::clamp(Pitch, -89.0f, 89.0f);
}

const glm::vec3& CCameraComponent::GetCameraForward() const
{
	return CameraForward;
}

const glm::vec3& CCameraComponent::GetCameraUp() const
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
	assert(InMaxDistance > InMinDistance);
	MinDistance = InMinDistance;
	MaxDistance = InMaxDistance;
}

