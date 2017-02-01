#include "CuadGl.h"

void CuadGl::Create() {
	shaderID = glCreateProgram();

	char *vsSourceP = file2string("VS_tri.glsl");
	char *fsSourceP = file2string("FS_tri.glsl");

	GLuint vshader_id = createShader(GL_VERTEX_SHADER, vsSourceP);
	GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, fsSourceP);

	glAttachShader(shaderID, vshader_id);
	glAttachShader(shaderID, fshader_id);

	glLinkProgram(shaderID);
	glUseProgram(shaderID);

	vertexAttribLoc = glGetAttribLocation(shaderID, "MyVertex");
	colorAttribLoc = glGetAttribLocation(shaderID, "MyColor");

	matUniformLoc = glGetUniformLocation(shaderID, "MyMatrix");
#ifdef USE_VBO
	vertices[0] = { -0.5f,  0.5f, 0.0f , 0.0f, 0.0f, 1.0f };
	vertices[1] = { -0.5f, -0.5f, 0.0f , 0.0f, 1.0f, 0.0f };
	vertices[2] = { 0.5f, -0.5f, 0.0f , 1.0f, 0.0f, 1.0f };
	vertices[3] = { 0.5f,  0.5f, 0.0f , 1.0f, 0.0f, 0.0f };

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(triVertex1), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	indices[0] = 2;
	indices[1] = 1;
	indices[2] = 0;
	indices[3] = 3;
	indices[4] = 2;
	indices[5] = 0;

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#else
#ifdef USE_ARRAY_OF_STRUCTS
	vertices[0] = { -0.5f,  0.5f, 0.0f , 0.0f, 0.0f, 1.0f };
	vertices[1] = { -0.5f, -0.5f, 0.0f , 0.0f, 1.0f, 0.0f };
	vertices[2] = { 0.5f, -0.5f, 0.0f , 1.0f, 0.0f, 0.0f };

	vertices[3] = { -0.5f, 0.5f, 0.0f , 0.0f, 0.0f, 1.0f };
	vertices[4] = { 0.5f,-0.5f, 0.0f , 1.0f, 0.0f, 0.0f };
	vertices[5] = { 0.5f, 0.5f, 0.0f , 1.0f, 0.0f, 0.0f };
#else
	positions[0] = { -0.5f,  0.5f, 0.0f };
	positions[1] = { -0.5f, -0.5f, 0.0f };
	positions[2] = { 0.5f, -0.5f, 0.0f };

	positions[3] = { -0.5f,  0.5f, 0.0f };
	positions[4] = { 0.5f, -0.5f, 0.0f };
	positions[5] = { 0.5f,  0.5f, 0.0f };

	colors[0] = { 0.0f, 0.0f, 1.0f };
	colors[1] = { 0.0f, 1.0f, 0.0f };
	colors[2] = { 1.0f, 0.0f, 0.0f };

	colors[3] = { 0.0f, 0.0f, 1.0f };
	colors[4] = { 1.0f, 0.0f, 0.0f };
	colors[5] = { 1.0f, 0.0f, 0.0f };
#endif
#endif
	D3DXMATRIX aspecRatio;
	D3DXMatrixScaling(&aspecRatio, 1, 1280.0f / 720.0f, 1);
	D3DXMatrixScaling(&transform, .02f, .02f, 1);
	D3DXMatrixMultiply(&transform, &transform, &aspecRatio);
}

void CuadGl::Transform(float *t) {
	transform = t;
}

void CuadGl::Draw(float *t, float *vp) {
	glUseProgram(shaderID);

	if (t)
		transform = t;
	D3DXMATRIX aspecRatio;
	D3DXMATRIX scaleWorld;
	D3DXMatrixScaling(&aspecRatio, 1, 1280.0f / 720.0f, 1);
	D3DXMatrixScaling(&scaleWorld, .02f, .02f, 1);
	transform = scaleWorld * aspecRatio * transform;
	glUniformMatrix4fv(matUniformLoc, 1, GL_FALSE, &transform.m[0][0]);

#ifdef USE_VBO
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glEnableVertexAttribArray(vertexAttribLoc);
	glEnableVertexAttribArray(colorAttribLoc);

	glVertexAttribPointer(vertexAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(triVertex1), (void*)0);
	glVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(triVertex1), (void*)12);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#else
#ifdef USE_ARRAY_OF_STRUCTS
	glEnableVertexAttribArray(vertexAttribLoc);
	float *pos = (float*)&vertices[0].x;
	glVertexAttribPointer(vertexAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(triVertex), pos);

	glEnableVertexAttribArray(colorAttribLoc);
	float *color = (float*)&vertices[0].r;
	glVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(triVertex), color);
#else
	glEnableVertexAttribArray(vertexAttribLoc);
	glVertexAttribPointer(vertexAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(triVertex), positions);
	glEnableVertexAttribArray(colorAttribLoc);
	glVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(triVertex), colors);
#endif
	glUniformMatrix4fv(matUniformLoc, 1, GL_FALSE, &transform.m[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);
#endif
	glDisableVertexAttribArray(vertexAttribLoc);
	glDisableVertexAttribArray(colorAttribLoc);

	glUseProgram(0);
}

void CuadGl::Destroy() {
	glDeleteProgram(shaderID);
}