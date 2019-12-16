#include "Header.h"


int Rect::numOfTris = 12;
int Rect::numOfVerts = 8;

Rect::Rect()
{
	cx = cy = cz = 0.0;
	dim = 1;
}

Rect::Rect(glm::vec3 p, int d)
{
	pos = p;
	cx = pos.x;
	cy = pos.y;
	cz = pos.z;
	
	dim = d;

	width = d;
	height = d;
	depth = d;
}

Rect::Rect(glm::vec3 p, int w, int h, int d)
{
	cx = pos.x;
	cy = pos.y;
	cz = pos.z;
	pos = p;

	width = w;
	height = h;
	depth = d;

	dim = w;

}

void Rect::render(Shader* shader, bool polygonMode)
{
	   	
	rectMatrix = glm::translate(glm::mat4(1.0), pos);	//viewing is simple translate
	rectMatrix = glm::rotate(rectMatrix, tiltAngleY, glm::vec3(0, 1, 0));
	

	rectMatrix = Camera::getViewMatrix() * rectMatrix;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &rectMatrix[0][0]);

	normalMatrix = glm::inverseTranspose(glm::mat3(rectMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));


	//draw objects
	glBindVertexArray(m_vaoID);		// select VAO

	if(polygonMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, numOfTris * 3, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Done	
	glBindVertexArray(0); //unbind the vertex array object


}

void Rect::constructGeometry(Shader* shader)
{
	if (!shader->load("BasicView", "glslfiles/basic.vert", "glslfiles/basic.frag"))
	{
		cout << "failed to load shader" << endl;
	}

	verts[0] = -width;		verts[1] =  -height;	verts[2] =  -depth;
	verts[3] =  -width;		verts[4] =  height;		verts[5] =  -depth;
	verts[6] =  width;		verts[7] =  height;		verts[8] =  -depth;
	verts[9] =  width;		verts[10] =  -height;	verts[11] =  -depth;

	verts[12] =  -width;   verts[13] = -height;  verts[14] =  depth;
	verts[15] =  -width;   verts[16] = height;  verts[17] =  depth;
	verts[18] =  width;   verts[19] = height;  verts[20] =  depth;
	verts[21] =  width;   verts[22] = -height;  verts[23] =  depth;

	cols[0] = 0.0;   cols[1] = 0.0;  cols[2] = 0.0;
	cols[3] = 0.0;   cols[4] = 1.0;  cols[5] = 0.0;
	cols[6] = 0.0;   cols[7] = 0.0;  cols[8] = 1.0;
	cols[9] = 1.0;   cols[10] = 1.0;  cols[11] = 1.0;

	cols[12] = 1.0;   cols[13] = 0.0;  cols[14] = 0.0;
	cols[15] = 0.0;   cols[16] = 1.0;  cols[17] = 0.0;
	cols[18] = 0.0;   cols[19] = 0.0;  cols[20] = 1.0;
	cols[21] = 1.0;   cols[22] = 1.0;  cols[23] = 0.0;

	tris[0] = 0; tris[1] = 1; tris[2] = 2;
	tris[3] = 0; tris[4] = 2; tris[5] = 3;
	tris[6] = 4; tris[7] = 6; tris[8] = 5;
	tris[9] = 4; tris[10] = 7; tris[11] = 6;
	tris[12] = 1; tris[13] = 5; tris[14] = 6;
	tris[15] = 1; tris[16] = 6; tris[17] = 2;
	tris[18] = 0; tris[19] = 7; tris[20] = 4;
	tris[21] = 0; tris[22] = 3; tris[23] = 7;
	tris[24] = 0; tris[25] = 5; tris[26] = 1;
	tris[27] = 0; tris[28] = 4; tris[29] = 5;
	tris[30] = 3; tris[31] = 2; tris[32] = 7;
	tris[33] = 2; tris[34] = 6; tris[35] = 7;

	// VAO allocation
	glGenVertexArrays(1, &m_vaoID);

	// First VAO setup
	glBindVertexArray(m_vaoID);

	glGenBuffers(2, m_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	//initialises data storage of vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, numOfVerts * 3 * sizeof(GLfloat), verts, GL_STATIC_DRAW);
	GLint vertexLocation = glGetAttribLocation(shader->handle(), "in_Position");
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexLocation);


	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, numOfVerts * 3 * sizeof(GLfloat), cols, GL_STATIC_DRAW);
	GLint colorLocation = glGetAttribLocation(shader->handle(), "in_Color");
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorLocation);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfTris * 3 * sizeof(unsigned int), tris, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);


	calcMinMax();
}


//calclulate min and max values of the rectangle
void Rect::calcMinMax() {

	minX = cx - width;
	maxX = cx + width;

	minY = cy - height;
	maxY = cy + height;

	minZ = cz - depth;
	maxZ = cz + depth;

	/*cout << "Rec:   x:" << minX << "|" << maxX
	<< "  y:" << minY << "|" << maxY
	<< "  z:" << minZ << "|" << maxZ << endl;*/
}
