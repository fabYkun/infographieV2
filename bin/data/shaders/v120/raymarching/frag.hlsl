#version 120
// should work on versions 100 and 120

const float			M_PI = 3.14159265358979323846;
const int			RAY_MARCHING_IT = 64;
const float			EPSILON = 0.0001;
const int			FAR_PLANE = 1000;

varying vec2		v_position;
uniform float		u_aspect_ratio;

uniform vec3		sphere_position;
uniform float		torus_rotation;

uniform vec3		light_position;
uniform vec3		light_color;

uniform float		reflexion;
uniform samplerCube	envMap;

uniform vec3		O;
uniform float		time;

vec3				rotate(vec3 p, float theta)
{
	return vec3(p.x * cos(theta) + p.z * sin(theta), p.y,
		p.z * cos(theta) - p.x * sin(theta));
}

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

float				calc_distance(vec3 p)
{
	float			d;
	float			angle = M_PI / (4.0) * torus_rotation; // 45 degrees when rotation == 1 (default)
	vec3			trans;


	trans = opTx(p, Rot4X(angle));
	d = torus(trans);

	trans = opTrans(p, sphere_position);
	d = min(d, sphere(trans, 0.1));
	return d;
}

vec3				calc_normal(vec3 p)
{
	float			h = EPSILON;

	float grad_x = calc_distance(p + vec3(h, 0, 0)) - calc_distance(p - vec3(h, 0, 0));
	float grad_y = calc_distance(p + vec3(0, h, 0)) - calc_distance(p - vec3(0, h, 0));
	float grad_z = calc_distance(p + vec3(0, 0, h)) - calc_distance(p - vec3(0, 0, h));

	vec3 gradient = vec3(grad_x, grad_y, grad_z);
	return normalize(gradient);
}

// O: origin R: ray
float				trace(vec3 O, vec3 R)
{
	float			t = 0.0;

	for (int i = 0; i < RAY_MARCHING_IT; ++i)
	{
		vec3		p = O + R * t;

		t += calc_distance(p) * 0.5;
	}
	return t;
}

vec3				shade(vec3 O, vec3 rayD, float t)
{
	vec3			p = O + rayD * t;
	vec3			normal = calc_normal(p);
	vec3			light_dir = normalize(light_position - p);
	float			intensity = dot(normal, light_dir);
	vec3			diffuse = intensity * light_color;
	vec3			specular = pow(textureCube(envMap, reflect(rayD, normal)).rgb, vec3(2.2));
	float			costheta = -dot(normal, rayD);
	return			mix(specular, diffuse, clamp(costheta, 0.0, 1.0) * reflexion);
}

/*
** pixel(x, y)
*/
vec3				run(float x, float y)
{
	vec3			rayO = O;
	vec3			rayD = normalize(vec3(x, y, 0.) - O);

	// camera
	rayD = rotate(rayD, time);
	rayO = rotate(rayO, time);

	float t = trace(rayO, rayD);
	if (t > FAR_PLANE)
		return textureCube(envMap, rayD).rgb;
	return (shade(rayO, rayD, t));
}

void				main()
{
	vec3			color;

	#if 1 // antialiasing
		color = vec3(0.0);

		for (float x = 0.0; x < 0.001; x += 0.0005)
			for (float y = 0.0; y < 0.001; y += 0.0005)
				color += run((v_position.x + x) * u_aspect_ratio, v_position.y + y) * 0.25;
	#else
		color = run(v_position.x * u_aspect_ratio, v_position.y)
	#endif

	gl_FragColor = vec4(color, 1);
}
