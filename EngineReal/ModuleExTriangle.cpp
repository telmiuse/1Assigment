#include "ModuleExTriangle.h"
#include "MathGeoLib/MathGeoLib.h"
#include "Program.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleCamera.h"
#include "ModuleModelo.h"
#include "ModuleIMGUI.h"
#include <string>

ModuleExTriangle::ModuleExTriangle()
{
}

// Destructor
ModuleExTriangle::~ModuleExTriangle()
{
}

void ModuleExTriangle::DrawMesh(Mesh mesh)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < mesh.textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = mesh.textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(++diffuseNr);
		else if (name == "texture_specular")
			number = std::to_string(++specularNr); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(++normalNr); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(++heightNr); // transfer unsigned int to stream

		glUniform1i(glGetUniformLocation(App->program->ProgramID, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, mesh.textures[i].id);
	}

	// draw mesh
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

void ModuleExTriangle::SetUpMesh(Mesh mesh)
{
	// create buffers/arrays
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &(mesh.vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &(mesh.indices[0]), GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);

}

bool ModuleExTriangle::Init() {
	App->modelo->LoadModel("Models/BakerHouse.fbx");
	for (unsigned int i = 0; i < App->modelo->meshes.size(); i++)
	{
		SetUpMesh(App->modelo->meshes[i]);
	}
	vtx_shader = App->program->CompileShader(GL_VERTEX_SHADER, (App->program->LoadShaderSource("vertex.glsl")));
	frg_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, (App->program->LoadShaderSource("fragment.glsl")));
	App->program->CreateProgram(vtx_shader, frg_shader);
	App->texture->LoadTexture("Textures/Baker_housse.png");
	return true;
}

update_status ModuleExTriangle::PreUpdate()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;
}

update_status ModuleExTriangle::Update()
{
	
	glUseProgram(App->program->ProgramID);
	
	float4x4 proj = App->Camera->GetProjection();
	float4x4 view = App->Camera->GetView();
	float4x4 model = float4x4::identity;




	glUniformMatrix4fv(glGetUniformLocation(App->program->ProgramID, "model"), 1, GL_TRUE, &model[0][0]); //GL_TRUE transpose the matrix
	glUniformMatrix4fv(glGetUniformLocation(App->program->ProgramID, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->ProgramID, "proj"), 1, GL_TRUE, &proj[0][0]);
	/*
	glUniformMatrix4fv(glGetUniformLocation(App->program->ProgramID, "model"), 1, GL_TRUE, &(App->Camera->model[0][0]));
	glUniformMatrix4fv(glGetUniformLocation(App->program->ProgramID, "view"), 1, GL_TRUE, &(App->Camera->view[0][0]));
	glUniformMatrix4fv(glGetUniformLocation(App->program->ProgramID, "proj"), 1, GL_TRUE, &(App->Camera->proj[0][0]));
	*/
	for (unsigned int i = 0; i < App->modelo->meshes.size(); i++)
	{
		DrawMesh(App->modelo->meshes[i]);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleExTriangle::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleExTriangle::CleanUp()
{
	App->imgui->AddLog("Destroying renderer");
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	App->imgui->AddLog("Destroying program");

	//Destroy window
	glDetachShader(App->program->ProgramID,vtx_shader);
	glDetachShader(App->program->ProgramID, frg_shader);
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	glDeleteProgram(App->program->ProgramID);
	//Destroy window
	return true;
}