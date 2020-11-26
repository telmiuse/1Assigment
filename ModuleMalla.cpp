#include "ModuleMalla.h"
#include "ModuleExTriangle.h"
#include "GL/glew.h"
#include "Application.h"
#include "program.h"
#include "ModuleTexture.h"
#include "IL/il.h"
#include "MathGeoLib/Math/float4x4.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"



ModuleMalla::ModuleMalla()
{

}

// Destructor
ModuleMalla::~ModuleMalla()
{

}
void ModuleMalla::LoadEBO(const aiMesh* mesh)
{
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces * 3;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	unsigned* indices = (unsigned*)(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, index_size, GL_MAP_WRITE_BIT));
	for (unsigned i = 0; i < mesh->mNumFaces; ++i)
	{
		assert(mesh->mFaces[i].mNumIndices == 3); // note: assume triangles = 3 indices per face
		*(indices++) = mesh->mFaces[i].mIndices[0];
		*(indices++) = mesh->mFaces[i].mIndices[1];
		*(indices++) = mesh->mFaces[i].mIndices[2];
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	num_indices = mesh->mNumFaces * 3 ;
}


void ModuleMalla::CreateVAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3 + sizeof(float) *2 , (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)(sizeof(float) * 3));

	glBindVertexArray(0);
}

void ModuleMalla::LoadVBO(const aiMesh* mesh)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned buffer_size = vertex_size * mesh->mNumVertices;
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);
	
	/*unsigned position_size = sizeof(float) * 3 * mesh->mNumVertices;
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, mesh->mVertices);
	unsigned uv_offset = position_size;
	unsigned uv_size = sizeof(float) * 2 * mesh->mNumVertices;
	
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));
	*/
	float* uvs = (float*)(glMapBufferRange(GL_ARRAY_BUFFER, 0 , buffer_size, GL_MAP_WRITE_BIT));

	for (unsigned i = 0, position = 0 ; i < mesh->mNumVertices; ++i)
	{
		//uvs[i] = float(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		uvs[position++] = mesh->mVertices[i].x;
		uvs[position++] = mesh->mVertices[i].y;
		uvs[position++] = mesh->mVertices[i].z;

		uvs[position++] = mesh->mTextureCoords[0][i].x;
		uvs[position++] = mesh->mTextureCoords[0][i].y;

	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	num_vertices = mesh->mNumVertices;
}

void ModuleMalla::Draw(const std::vector<unsigned>& model_textures)
{
	unsigned program = App->Triangle->program;

	const float4x4& view = App->Camera->GetView();
	const float4x4& proj = App->Camera->GetProjection();
	float4x4 model = float4x4::identity;

	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, (const float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, (const float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, (const float*)&proj);

	glUniform1i(glGetUniformLocation(program, "mytexture"), 0);
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model_textures[0]);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
