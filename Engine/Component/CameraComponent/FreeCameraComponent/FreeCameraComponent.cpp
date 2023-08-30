#include "FreeCameraComponent.h"
#include "Engine/Window/WindowInterface.h"
#include "Engine/Component/TransformationComponent//TransformationComponent.h"
#include <GLFW/glfw3.h>
#include "Engine/ServiceLocator/ServiceLocator.h"

// TODO: Input handler with observers for each key type that can be used for these kind of updates
// here as well as in other use cases in game.

void CFreeCameraComponent::Update(float DeltaTime)
{
	CCameraComponent::Update(DeltaTime);

	assert(ParentTransformationComponent != nullptr);
	glm::vec3 CameraRight = GetCameraRight();

	glm::vec3 CameraMovementDirection{ 0.0f };
	
	if (IsKeyPressed(CameraControlInput.MoveForwardKey))
	{
		CameraMovementDirection += CameraForward;
	}
	if (IsKeyPressed(CameraControlInput.MoveBackwardKey))
	{
		CameraMovementDirection -= CameraForward;
	}
	if (IsKeyPressed(CameraControlInput.MoveLeftKey))
	{
		CameraMovementDirection -= CameraRight;
	}
	if (IsKeyPressed(CameraControlInput.MoveRightKey))
	{
		CameraMovementDirection += CameraRight;
	}
	if (IsKeyPressed(CameraControlInput.MoveUpKey))
	{
		CameraMovementDirection += CameraUp;
	}
	if (IsKeyPressed(CameraControlInput.MoveDownKey))
	{
		CameraMovementDirection -= CameraUp;
	}

	ParentTransformationComponent->Translate(CameraControlInput.CameraMoveSpeed * CameraMovementDirection * DeltaTime);

	IWindowInterface::FMousePosition CurrentMousePosition = WindowInterface->GetMousePosition();
	float xOffset = CameraControlInput.MouseSensitivity * (CurrentMousePosition.PosX - LastMouseX) * DeltaTime;
	float yOffset = CameraControlInput.MouseSensitivity * (LastMouseY - CurrentMousePosition.PosY) * DeltaTime;
	
	LastMouseX = CurrentMousePosition.PosX;
	LastMouseY = CurrentMousePosition.PosY;
	IncrementRotationEulerAngles(xOffset, yOffset);
}

void CFreeCameraComponent::Start()
{
	WindowInterface = ServiceLocator::GetWindow();
	assert(WindowInterface != nullptr);
	CCameraComponent::Start();
	IWindowInterface::FMousePosition CurrentMousePosition = WindowInterface->GetMousePosition();
	LastMouseX = CurrentMousePosition.PosX;
	LastMouseY = CurrentMousePosition.PosY;
	SetupMovementControls();
}

void CFreeCameraComponent::SetupMovementControls(const FFreeCameraControlInput& InCameraControl)
{
	CameraControlInput = InCameraControl;
}

void CFreeCameraComponent::SetupMovementControls()
{
	CameraControlInput.CameraMoveSpeed = 4.0f;
	CameraControlInput.MouseSensitivity = 5.0f;
	CameraControlInput.MoveBackwardKey = GLFW_KEY_S;
	CameraControlInput.MoveForwardKey = GLFW_KEY_W;
	CameraControlInput.MoveDownKey = GLFW_KEY_Q;
	CameraControlInput.MoveUpKey = GLFW_KEY_E;
	CameraControlInput.MoveLeftKey = GLFW_KEY_A;
	CameraControlInput.MoveRightKey = GLFW_KEY_D;
}

bool CFreeCameraComponent::IsKeyPressed(const int Key) const
{
	return Key != -1 && WindowInterface->IsKeyPressed(Key);
}
