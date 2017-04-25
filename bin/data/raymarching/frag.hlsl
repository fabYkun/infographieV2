#version 120

const float			M_PI = 3.14159265358979323846;
const int			RAY_MARCHING_IT = 64;

varying vec2		v_position;
uniform float		u_aspect_ratio;

uniform vec3		sphere_position;
uniform float		rotation;
uniform vec3		O;

mat4				Rot4X(float a)
{
	float			c = cos(a);
	float			s = sin(a);

	return mat4(	1, 0, 0, 0,
					0, c, -s, 0,
					0, s, c, 0,
					0, 0, 0, 1);
}

mat4				transposeM4(in mat4 m)
{
	vec4			r0 = m[0];
	vec4			r1 = m[1];
	vec4			r2 = m[2];
	vec4			r3 = m[3];

	mat4 t = mat4(
		vec4(r0.x, r1.x, r2.x, r3.x),
		vec4(r0.y, r1.y, r2.y, r3.y),
		vec4(r0.z, r1.z, r2.z, r3.z),
		vec4(r0.w, r1.w, r2.w, r3.w)
	);
	return t;
}

vec3				opTx(vec3 p, mat4 m)
{
	return (transposeM4(m)*vec4(p, 1.0)).xyz;
}

vec3				opTrans(vec3 p, vec3 d)
{
	return p - d;
}

float				torus(vec3 p)
{
	vec2 t = vec2(0.50, 0.1);
	vec2 q = vec2(length(p.xz) - t.x, p.y);
	return length(q) - t.y;
}

float				sphere(vec3 p, float r)
{
	return length(p) - r;
}

// O: origin R: ray
float				trace(vec3 O, vec3 R)
{
	float			t = 0.0;
	float			d;
	float			angle = M_PI / (4.0) * rotation; // 45 degrees when rotation == 1 (default)
	vec3			trans;

	for (int i = 0; i < RAY_MARCHING_IT; ++i)
	{
		vec3		p = O + R * t;

		trans = opTx(p, Rot4X(angle));
		d = torus(trans);

		trans = opTrans(p, sphere_position);
		d = min(d, sphere(trans, 0.1));
		t += d * 0.5;
	}
	return t;
}

/*
** pixel(x, y)
*/
vec3				run(float x, float y)
{
	vec3			rayO = O;
	vec3			rayD = normalize(vec3(x, y, 0.) - O);

	float t = trace(rayO, rayD);
	float fog = 1.0 / (1.0 + t * t * t); // adds depth
	return (vec3(fog));
}

void				main()
{
	gl_FragColor = vec4(run(v_position.x * u_aspect_ratio, v_position.y), 1);
}
