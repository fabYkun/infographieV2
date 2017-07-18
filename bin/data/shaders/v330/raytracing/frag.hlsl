#version 330

/*
** really not the best idea to write a raytracer inside a fragment shader but yay...
*/

const float			M_PI = 3.14159265358979323846;
const float			INFINITY = 1000000000.;

in vec2				v_position;
out vec4			fragColor;

uniform float		u_aspect_ratio;

uniform vec3		sphere_position;
uniform float		sphere_radius;
uniform float		sphere_reflexion;
uniform vec3		sphere_color;

uniform vec3		cube_position;
uniform float		cube_size;
uniform float		cube_reflexion;
uniform vec3		cube_color;

uniform vec3		plane_position;
uniform vec3		plane_normal;
uniform float		plane_reflexion;

uniform float		light_intensity;
uniform vec2		light_specular;
uniform vec3		light_position;
uniform vec3		light_color;

uniform float		ambient;
uniform vec3		O;

/*
** O : centre
** D : vecteur de direction
** S : origine du rayon
** R : rayon
*/
float				intersect_sphere(vec3 O, vec3 D, vec3 S, float R)
{
	float			a = dot(D, D);
	vec3			OS = O - S;
	float			b = 2. * dot(D, OS);
	float			c = dot(OS, OS) - R * R;
	float			disc = b * b - 4. * a * c;

	if (disc > 0.)
	{
		float distSqrt = sqrt(disc);
		float q = (-b - distSqrt) / 2.0;
		if (b >= 0.)
			q = (-b + distSqrt) / 2.0;
		float t0 = q / a;
		float t1 = c / q;
		t0 = min(t0, t1);
		t1 = max(t0, t1);
		if (t1 >= 0.)
		{
			if (t0 < 0.) return t1;
			else return t0;
		}
	}
	return INFINITY;
}

float				intersect_cube(vec3 O, vec3 D)
{
	float			tmp;
	float			tmin = (cube_position.x - cube_size - O.x) / D.x;
	float			tmax = (cube_position.x + cube_size - O.x) / D.x;

	if (tmin > tmax)
	{
		tmp = tmin;
		tmin = tmax;
		tmax = tmp;
	}

	float tymin = (cube_position.y - cube_size - O.y) / D.y;
	float tymax = (cube_position.y + cube_size - O.y) / D.y;
	if (tymin > tymax)
	{
		tmp = tymin;
		tymin = tymax;
		tymax = tmp;
	}
	if ((tmin > tymax) || (tymin > tmax))
		return INFINITY;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (cube_position.z - cube_size - O.z) / D.z;
	float tzmax = (cube_position.z + cube_size - O.z) / D.z;

	if (tzmin > tzmax)
	{
		tmp = tzmin;
		tzmin = tzmax;
		tzmax = tmp;
	}
	if ((tmin > tzmax) || (tzmin > tmax))
		return INFINITY;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	if (tmin < 0)
		return tmax;
	return tmin;
}

/*
** O : centre
** D : vecteur de direction
** P : position plan
** N : normale du plan
*/
float				intersect_plane(vec3 O, vec3 D, vec3 P, vec3 N)
{
	float			denom = dot(D, N);

	if (abs(denom) < 1e-6)
		return INFINITY;
	float			d = dot(P - O, N) / denom;
	if (d < 0.) return INFINITY;
	return d;
}

bool				darkPoint(vec3 O, vec3 D)
{
	float			t_plane, t0, t1;

	O = O + D * .0001; // peut occasionner des auto-detections sinon
	t_plane = intersect_plane(O, D, plane_position, plane_normal);
	t0 = intersect_sphere(O, D, sphere_position, sphere_radius);
	t1 = intersect_cube(O, D);
	if (min(t_plane, min(t0, t1)) < INFINITY - 1)
		return true;
	return false;
}

/*
** pixel(x, y)
*/
vec3				run(float x, float y)
{
	int				depth = 0;
	float			t0, t1, t2;
	vec3			rayO = O;
	vec3			rayD = normalize(vec3(x, y, 0.) - O);
	vec3			color = vec3(0.0, 0.0, 0.0);
	vec3			col_ray;
	float			reflection = 1.;

	vec3			object_color;
	vec3			object_normal;
	float			object_reflection;
	vec3			intersection_pt;
	vec3			toL;

	while (depth < 5)
	{
		t0 = intersect_plane(rayO, rayD, plane_position, plane_normal);
		t1 = intersect_sphere(rayO, rayD, sphere_position, sphere_radius);
		t2 = intersect_cube(rayO, rayD);

		if (t0 < min(t1, t2)) {
			intersection_pt = rayO + rayD * t0;
			object_normal = plane_normal;
			object_color = vec3(0., 0.546, 1.);
			object_reflection = plane_reflexion;
		}
		else if (t1 < t2) {
			intersection_pt = rayO + rayD * t1;
			object_normal = normalize(intersection_pt - sphere_position);
			object_color = sphere_color;
			object_reflection = sphere_reflexion;;
		}
		else if (t2 < t1) {
			intersection_pt = rayO + rayD * t2;
			object_normal = normalize(intersection_pt - cube_position);
			object_color = cube_color;
			object_reflection = cube_reflexion;;
		}
		toL = normalize(light_position - intersection_pt);

		if (min(min(t0, t1), t2) == INFINITY || darkPoint(intersection_pt, toL))
		{
			col_ray = vec3(0, 0, 0);
			depth = 5;
		}
		else
		{
			col_ray = vec3(ambient, ambient, ambient);
			col_ray += light_intensity * max(dot(object_normal, toL), 0.) * object_color;
			col_ray += light_specular.x * light_color * pow(max(dot(object_normal, normalize(toL + normalize(O - intersection_pt))), 0.), light_specular.y);
		}

		rayO = intersection_pt + object_normal * .0001;
		rayD = normalize(rayD - 2. * dot(rayD, object_normal) * object_normal);
		color += reflection * col_ray;
		reflection *= object_reflection;
		++depth;
	}

	return clamp(color, 0., 1.);
}

void				main()
{
	fragColor = vec4(run(v_position.x * u_aspect_ratio, v_position.y), 1);
}
