#include "Header.h"

Grid::Grid()
{
}

void Grid::render(Shader* shader)
{

	modelMatrix = glm::translate(glm::mat4(1.0), pos);	

	modelMatrix = glm::rotate(modelMatrix, 90.0f, glm::vec3(1,0, 0));

	modelMatrix = Camera::getViewMatrix() * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);

	normalMatrix = glm::inverseTranspose(glm::mat3(modelMatrix));
	glUniformMatrix3fv(glGetUniformLocation(shader->handle(), "NormalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glBindTexture(GL_TEXTURE_2D, texName);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//draw objects
	glBindVertexArray(m_vaoID);		// select VAO
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, numOfTris*3, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Done	
	glBindVertexArray(0); //unbind the vertex array object
	
}

void Grid::constructGeometry(Shader* shader, int width, int dim)
{
	if (!shader->load("BasicView", "glslfiles/basicSpecularFlat.vert", "glslfiles/basicSpecularFlat.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	//create dim x dim grid of vertices
	numOfVerts = dim*dim;
	numOfTris = (dim-1)*(dim-1)*2;
	verts = new float[numOfVerts*3];
	tris = new unsigned int[numOfTris*3];
	normals = new float[numOfVerts*3];

	double step = (double)width/(double)(dim-1);
	for(int i=0; i<dim; i++)
	{
		for(int j=0; j<dim; j++)
		{
			verts[(i*dim+j)*3] = i*step;   verts[(i*dim+j)*3+1] = j*step;  verts[(i*dim+j)*3+2] = 0;
			normals[(i*dim+j)*3] = 0.0;   normals[(i*dim+j)*3+1] = 0.0;  normals[(i*dim+j)*3+2] = 1.0; //set same normal for all
		}
	}

	int tIndex = 0; 
	for(int i=0; i<dim-1; i++)
	{
		for(int j=0; j<dim-1; j++)
		{
			tris[tIndex*3]=i*dim+j; tris[tIndex*3+1]=(i*dim+j)+1; tris[tIndex*3+2]=((i+1)*dim+j);
			tIndex++;
			tris[tIndex*3]=((i+1)*dim+j); tris[tIndex*3+1]=((i+1)*dim+j)+1; tris[tIndex*3+2]=(i*dim+j)+1;
			tIndex++;
		}
	}
	float tex[8];   // texture coordinate array
	tex[0] = 0.0f; tex[1] = 0.0f;
	tex[2] = 0.0f; tex[3] = 2000.0f;
	tex[4] = 2000.0f; tex[5] = 2000.0f;
	tex[6] = 2000.0f; tex[7] = 0.0f;

	/*tex[0] = 0.0f; tex[1] = 1.0f;
	tex[2] = 0.0f; tex[3] = 0.0f;
	tex[4] = 1.0f; tex[5] = 0.0f;
	*/
	// VAO allocation
	glGenVertexArrays(1, &m_vaoID);

	// First VAO setup
	glBindVertexArray(m_vaoID);
	
	glGenBuffers(2, m_vboID);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	//initialises data storage of vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, numOfVerts*3*sizeof(GLfloat), verts, GL_STATIC_DRAW);

	GLint vertexLocation= glGetAttribLocation(shader->handle(), "in_Position");
	GLint texCoordLocation = glGetAttribLocation(shader->handle(), "in_TexCoord");

	//set the uniform variable for the texture map
	glUniform1i(glGetUniformLocation(shader->handle(), "DiffuseMap"), 0);

	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(vertexLocation);

	
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, numOfVerts*3*sizeof(GLfloat), normals, GL_STATIC_DRAW);
	
	GLint normalLocation= glGetAttribLocation(shader->handle(), "in_Normal");
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(normalLocation);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfTris * 3 * sizeof(unsigned int), tris, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//set the texture coordinates
	glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(texCoordLocation);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

GLuint Grid::loadPNG(const char* strFileName)
{
	GLuint myTexture;

	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(strFileName))
	{
		glGenTextures(1, &myTexture);
		glBindTexture(GL_TEXTURE_2D, myTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return myTexture;
}
