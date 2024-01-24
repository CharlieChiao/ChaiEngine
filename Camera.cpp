#include"Common.h"
#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, float CamSpeed)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
	speed = CamSpeed;
	Orientation = glm::vec3(0.0f, 0.0f, 0.0f) - Position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(FOVdeg, (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}



void Camera::Inputs(SDL_Window* Window)
{
	// Handles key inputs
	if (HInput::GetKey(Key_W))
	{
		Position += speed * glm::normalize(Orientation);
		CHARLIE_LOG(Log, "WWW");
	}
	if (HInput::GetKey(Key_A))
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (HInput::GetKey(Key_S))
	{
		Position += speed * -glm::normalize(Orientation);
	}
	if (HInput::GetKey(Key_D))
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (HInput::GetKey(Key_E))
	{
		Position += speed * Up;
	}
	if (HInput::GetKey(Key_Q))
	{
		Position += speed * -Up;
	}
	
	// Handles mouse inputs
	if(HInput::GetMouse(Button_Right))
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		
		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			HInput::SetCursorPosClient(Window, glm::vec2(width / 2.0f, height / 2.0f));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX = HInput::GetMousePosClient().x / width - 0.5;
		double mouseY = HInput::GetMousePosClient().y / height - 0.5;

		CHARLIE_LOG(Log, "Cursor Pos: %f, %f", mouseX, mouseY);

		float rotX = sensitivity * (float)mouseY;
		float rotY = sensitivity * (float)mouseX;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, -rotX, glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}
		Orientation = newOrientation;
		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, -rotY, Up);
		HInput::SetCursorPosClient(Window, glm::vec2(width / 2.0f, height / 2.0f));
	}
	else
	{
		//SDL_ShowCursor();
		SDL_SetRelativeMouseMode(SDL_FALSE);
		firstClick = true;
	}
}