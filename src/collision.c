
#include "collision.h"
#include <math.h>



float ray_sphere_intersection(const Ray *ray, const struct Sphere *sphere) {
    Vec3 oc = vec3_sub(ray->origin, sphere->center);
    float a = vec3_dot(ray->direction, ray->direction);
    float b = 2.0f * vec3_dot(oc, ray->direction);
    float c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0f; // No intersection
    } else {
        return (-b - sqrtf(discriminant)) / (2.0f * a); // Return the nearest intersection point
    } 
}
