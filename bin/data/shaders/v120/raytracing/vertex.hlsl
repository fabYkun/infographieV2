#version 120
// should work on versions 100 and 120

attribute vec2	a_position;
varying vec2	v_position;

void			main()
{
	gl_Position = vec4(a_position, 0.0, 1.0);
	v_position = a_position;
}