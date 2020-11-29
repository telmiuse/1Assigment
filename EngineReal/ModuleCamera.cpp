#include "ModuleExTriangle.h"
#include "ModuleModel.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "ModuleIMGUI.h"
#include "MathGeoLib/Math/float3x3.h"
#include "ModuleInput.h"
#include <GL/glew.h>
#include <time.h>    
#include "Leaks.h"
#include <iostream>

using namespace std;

ModuleCamera::ModuleCamera()
{
	pitch_angle = 2.0f;

}

// Destructor
ModuleCamera::~ModuleCamera()
{

}

// Called before render is available
bool ModuleCamera::Init()
{
	NOW = SDL_GetTicks();
	LAST = 0;
	deltaTime = 0;

	camera_position = float3(0, 1, 10);
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD(1) * 90.0f, 1.3f);
	frustum.SetPos(camera_position);
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);

	unsigned int lastTime = 0;
	return true;
}




update_status ModuleCamera::PreUpdate()
{

	float4x4 projectionGL = frustum.ProjectionMatrix().Transposed(); //<-- Important to transpose!
	LAST = NOW;
	NOW = SDL_GetTicks();

	deltaTime = (double)((NOW - LAST) / 1000);
	double aux = deltaTime;
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*(projectionGL.v));

	MoveForward();
	MoveRight();
	MouseRotate();
	RotateArrows();

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) {
		Speed = 16.0f;
	}
	else {
		Speed = 8.0;
	}


	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButtonDown(SDL_BUTTON(SDL_BUTTON_LEFT)))
	{

		App->imgui->AddLogInput("Input: Left ALT Keyboard & Left Mouse\n");
		float2 move = App->input->GetMouseMotion();
		OrbitCam(40, 40);

	}
	if (App->input->GetKey(SDL_SCANCODE_F))
	{
		App->imgui->AddLogInput("Input: F Keyboard\n");
		Focus();
	}

	frustum.SetPos(camera_position);
	float4x4 viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*(viewMatrix.v));

	return UPDATE_CONTINUE;
}

void ModuleCamera::MouseRotate() {

	if (App->input->GetMouseButtonDown(3) == KEY_REPEAT) {
		int aux = App->input->GetMouseMotion().x;
		int mousexoldNow = App->input->GetMousePosition().x;
		int mouseXnow = aux + mousexoldNow;
		if ((mousexoldNow - mouseXnow) < 0) {
			Rotate(frustum.WorldMatrix().RotatePart().RotateY(-pitch_angle * deltaTime));
		}
		if ((mousexoldNow - mouseXnow) > 0) {
			Rotate(frustum.WorldMatrix().RotatePart().RotateY(+pitch_angle * deltaTime));
		}

		int auxy = App->input->GetMouseMotion().y;
		int mouseyoldNow = App->input->GetMousePosition().y;
		int mouseynow = auxy + mouseyoldNow;
		if ((mouseyoldNow - mouseynow) > 0) {

			float radians_angle = DEGTORAD(80.0f) * deltaTime;
			float3 lookAtVector = frustum.Front() * cos(radians_angle) + frustum.Up() * sin(radians_angle);
			lookAtVector.Normalize();

			float3 upVector = frustum.WorldRight().Cross(lookAtVector);
			frustum.SetFront(lookAtVector);
			frustum.SetUp(upVector);
		}
		if ((mouseyoldNow - mouseynow) < 0) {

			float radians_angle = DEGTORAD(80.0f) * deltaTime;
			float3 lookAtVector = frustum.Front() * cos(-radians_angle) + frustum.Up() * sin(-radians_angle);
			lookAtVector.Normalize();

			float3 upVector = frustum.WorldRight().Cross(lookAtVector);
			frustum.SetFront(lookAtVector);
			frustum.SetUp(upVector);
		}
	}
}



void ModuleCamera::RotateCam(const float xAxis, const float yAxis)
{
	if (xAxis != 0.0f)
	{
		float3x3 rotY = float3x3::RotateY(xAxis);
		frustum.front = rotY.Transform(frustum.front).Normalized();
		frustum.up = rotY.Transform(frustum.up).Normalized();
	}
	if (yAxis != 0.0f)
	{
		float3x3 rotX = float3x3::RotateAxisAngle(frustum.WorldRight(), yAxis);
		frustum.up = rotX.Transform(frustum.up).Normalized();
		frustum.front = rotX.Transform(frustum.front).Normalized();
	}
}

void ModuleCamera::OrbitCam(const float xAxis, const float yAxis)
{
	if (xAxis != 0.0f)
	{
		float3x3 rot = float3x3::RotateY(xAxis);
		frustum.pos = rot.Transform(frustum.pos - App->model->centerPoint) + App->model->centerPoint;

	}
	if (yAxis != 0.0f)
	{
		float3x3 rot = float3x3::RotateX(yAxis);
		frustum.pos = rot.Transform(frustum.pos - App->model->centerPoint) + App->model->centerPoint;
	}
	LookAt(frustum.pos, App->model->centerPoint, frustum.up);

}

void ModuleCamera::RotateArrows() {

	if (App->input->GetKey(SDL_SCANCODE_UP)) {
		float radians_angle = DEGTORAD(40.0f * deltaTime);
		float3 lookAtVector = frustum.Front() * cos(radians_angle) + frustum.Up() * sin(radians_angle);
		lookAtVector.Normalize();

		float3 upVector = frustum.WorldRight().Cross(lookAtVector);
		frustum.SetFront(lookAtVector);
		frustum.SetUp(upVector);
		LOG("Up");
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN)) {
		float radians_angle = DEGTORAD(40.0f * deltaTime);
		float3 lookAtVector = frustum.Front() * cos(-radians_angle) + frustum.Up() * sin(-radians_angle);
		float aux = lookAtVector.Normalize();

		float3 upVector = frustum.WorldRight().Cross(lookAtVector);
		frustum.SetFront(lookAtVector);
		frustum.SetUp(upVector);
		LOG("Down");
	}




	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		Rotate(frustum.WorldMatrix().RotatePart().RotateY(pitch_angle * Speed * deltaTime));
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		Rotate(frustum.WorldMatrix().RotatePart().RotateY(-pitch_angle * Speed * deltaTime));
	}

}

void ModuleCamera::MoveRight() {



	if (App->input->GetKey(SDL_SCANCODE_D)) {
		frustum.Translate(frustum.WorldRight() * Speed * deltaTime);
		camera_position = frustum.Pos();
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		frustum.Translate(frustum.WorldRight() * -Speed * deltaTime);
		camera_position = frustum.Pos();
	}
	else {
		RotateCam(0.0f, 0.0f);
	}
}

void ModuleCamera::MoveForward() {

	/**Rendering**/

	if (App->input->GetScrool() == SCROOL_UP) {
		frustum.Translate(frustum.Front() * -Speed * deltaTime);
		camera_position = frustum.Pos();
	}
	if (App->input->GetScrool() == SCROOL_DOWN) {
		frustum.Translate(frustum.Front() * Speed * deltaTime);
		camera_position = frustum.Pos();
	}


	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		frustum.Translate(frustum.Front() * Speed * deltaTime);
		camera_position = frustum.Pos();
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		frustum.Translate(frustum.Front() * -Speed * deltaTime);
		camera_position = frustum.Pos();
	}


}

// Called every draw update
update_status ModuleCamera::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{



	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCamera::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(App->window->window);

	return true;
}


void ModuleCamera::Rotate(const float3x3 rotation_matrix)
{
	vec oldFront = frustum.Front().Normalized();
	frustum.SetFront(rotation_matrix.MulDir(oldFront));
	vec oldUp = frustum.Up().Normalized();
	frustum.SetUp(rotation_matrix.MulDir(oldUp));
}

void ModuleCamera::SetFOV(float fov)
{
	frustum.horizontalFov = fov;
	frustum.verticalFov = fov;
	SetAspectRatio();
	proj = frustum.ProjectionMatrix();
}
void ModuleCamera::SetAspectRatio()
{
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov * 0.5f) * ((float)App->window->width / App->window->height));
}

void ModuleCamera::Focus()
{
	frustum.pos = App->model->boundingBox.CenterPoint() - App->model->boundingBox.Size().Normalize() * frustum.front;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	App->Camera->view = frustum.ViewMatrix();
}

float4x4 ModuleCamera::LookAt(float3 eye, float3 target, float3 up) {
	math::float3 f(target - eye);
	f.Normalize();
	math::float3 s(f.Cross(up));
	s.Normalize();
	math::float3 u(s.Cross(f));
	float4x4 matrix;
	matrix[0][0] = s.x;
	matrix[0][1] = s.y;
	matrix[0][2] = s.z;
	matrix[1][0] = u.x;
	matrix[1][1] = u.y;
	matrix[1][2] = u.z;
	matrix[2][0] = -f.x;
	matrix[2][1] = -f.y;
	matrix[2][2] = -f.z;
	matrix[0][3] = -s.Dot(eye);
	matrix[1][3] = -u.Dot(eye);
	matrix[2][3] = f.Dot(eye);
	matrix[3][0] = 0.0f;
	matrix[3][1] = 0.0f;
	matrix[3][2] = 0.0f;
	matrix[3][3] = 1.0f;

	return matrix;
}