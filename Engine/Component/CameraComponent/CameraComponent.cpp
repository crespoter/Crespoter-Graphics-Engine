#include "CameraComponent.h"
#include "../Component.h"
#include "../../GameObject/GameObject.h"
#include "../TransformationComponent/TransformationComponent.h"

CCameraComponent::CCameraComponent() : IComponent(CAMERA_COMPONENT_NAME)
{
	
}

glm::mat4 CCameraComponent::GetViewMatrix() const
{
	glm::vec3 Position = ParentTransformationComponent->GetPosition();
	return glm::lookAt(Position, Position + CameraForward, CameraUp);
}

void CCameraComponent::Start()
{
	assert(ParentGameObject != nullptr);
	CTransformationComponent* TransformationComponent = ParentGameObject->GetComponent<CTransformationComponent>();
	assert(TransformationComponent != nullptr);
	ParentTransformationComponent = TransformationComponent;
	std::cout << ParentTransformationComponent->GetName();
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

	if (Pitch > 89.0f)
	{
		Pitch = 89.0f;
	}
	if (Pitch < -89.0f)
	{
		Pitch = -89.0f;
	}
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

