// Fragment Shader

#version 150

in  vec3 ex_Color;  //colour arriving from the vertex
out vec4 out_Color; //colour for the pixel

in vec3 ex_Normal;  //normal arriving from the vertex shader

void main(void)
{
	out_Color = vec4(1.0,0.0,0.0,1.0); //vec4(ex_Normal,1.0);

}