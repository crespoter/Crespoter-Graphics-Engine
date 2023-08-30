#pragma once
#include "Engine/Component/CameraComponent/CameraComponent.h"


struct FFreeCameraControlInput
{
	int MoveForwardKey = -1, MoveBackwardKey = -1;
	int MoveRightKey = -1, MoveLeftKey = -1;
	int MoveUpKey = -1, MoveDownKey = -1;
	float CameraMoveSpeed = 1.0f;
	float MouseSensitivity = 1.0f;
};

class CFreeCameraComponent : public CCameraComponent
{
public:
	/**
	* Contains camera control keys and their speeds
	*/

	void Update(float DeltaTime) override;
	void Start() override;

	/**
	* Sets up movement for the free camera
	* Keep values as -1 to keys that needs to be disabled
	* Speed values of 0 can be used to disable translation or rotation along that axis
	*/
	void SetupMovementControls(const FFreeCameraControlInput& InCameraControl);

	/**
	 * Sets the movement controls with the default values
	 */
	void SetupMovementControls();

private:
	bool IsKeyPressed(const int key) const;

	IWindowInterface* WindowInterface = nullptr;
	FFreeCameraControlInput CameraControlInput;
	float LastMouseX = 0.0f, LastMouseY = 0.0f;
};