
#include "collision.h"
#include <math.h>
#include <stddef.h>


/** Calculates the intersection of a ray with a sphere.
 * @param ray The ray to test intersection with
 * @param sphere The sphere to test intersection with
 * @return The parameter t of the intersection point, or -1.0f if no intersection
 */
Vec3 ray_sphere_intersection(const Ray *ray, const struct Sphere *sphere) {
    Vec3 oc = vec3_sub(ray->origin, sphere->center);
    float a = vec3_dot(ray->direction, ray->direction);
    //printf("a: %f\n", a);
    float b = 2.0f * vec3_dot(oc, ray->direction);
    //printf("b: %f\n", b);
    float c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
    //printf("c: %f\n", c);
    float discriminant = b * b - 4 * a * c;
    //printf("discriminant: %f\n", discriminant);

    if (discriminant < 0.0f || a==0.0f ){
       return (Vec3){NAN, NAN, NAN};
    }
    float t=(-b - sqrtf(discriminant)) / (2.0f * a); // Return the nearest intersection point
    if(t<0){
        t=(-b + sqrtf(discriminant)) / (2.0f * a);
    }
    if(t<0){
        return (Vec3){NAN,NAN,NAN};
    }
    return vec3_add(ray->origin, vec3_mul(ray->direction, t));
}



Vec3 ray_box_intersection(const Ray *ray, const struct AABBox *box) {
    float tminx, tmaxx;
    float tminy, tmaxy;
    float tminz, tmaxz;

    float t_close, t_far;
    float tmp = 0.f;

    //Axe x
    if(ray->direction.x == 0.0f){
        if(ray->origin.x < box->low.x || ray->origin.x > box->high.x){
            return (Vec3){NAN, NAN, NAN};
        }
        tminx = -INFINITY;
        tmaxx = INFINITY;
    } else {
        tminx = (box->low.x - ray->origin.x) / ray->direction.x;
        tmaxx = (box->high.x - ray->origin.x) / ray->direction.x;
        if(tminx > tmaxx) {
            tmp   = tminx;
            tminx = tmaxx;
            tmaxx = tmp;
        }
    }

    // Axe y
    if (ray->direction.y == 0.0f) {
        if (ray->origin.y < box->low.y || ray->origin.y > box->high.y)
            return (Vec3){NAN, NAN, NAN};

        tminy = -INFINITY;
        tmaxy = INFINITY;
    } else {
        tminy = (box->low.y - ray->origin.y) / ray->direction.y;
        tmaxy = (box->high.y - ray->origin.y) / ray->direction.y;

        if (tminy > tmaxy) {
            tmp = tminy;
            tminy = tmaxy;
            tmaxy = tmp;
        }
    }

    //Axe z
    if (ray->direction.z == 0.0f) {
        if (ray->origin.z < box->low.z || ray->origin.z > box->high.z)
            return (Vec3){NAN, NAN, NAN};

        tminz = -INFINITY;
        tmaxz = INFINITY;
    } else {
        tminz = (box->low.z - ray->origin.z) / ray->direction.z;
        tmaxz = (box->high.z - ray->origin.z) / ray->direction.z;

        if (tminz > tmaxz) {
            tmp = tminz;
            tminz = tmaxz;
            tmaxz = tmp;
        }
    }

    //Inetersection
    t_close = fmaxf(tminx, fmaxf(tminy, tminz));
    t_far = fminf(tmaxx,fminf(tmaxy,tmaxz));

    //If no intersection
    if(t_close > t_far || t_far < 0.0f){
         return (Vec3){NAN, NAN, NAN};
    }

    if (t_close < 0.0f)
         t_close=t_far;

    return vec3_add(
        ray->origin,
        vec3_mul(ray->direction, t_close)
    );

}

Vec3 get_intersection(const Ray *r, const size_t o, const struct Scene *s) {
    Vec3 intersection;

    if (s->shapetypes[o] == ST_SPHERE)
        intersection = ray_sphere_intersection(r, &s->shapes[o].sphere);
    else if (s->shapetypes[o] == ST_BOX)
        intersection = ray_box_intersection(r, &s->shapes[o].box);
    else
        intersection = (Vec3){NAN, NAN, NAN};

    return intersection;
}

Collision first_scene_collision(const Ray *ray, const struct Scene *scene) {

    // Initialize the result
    Collision result = {
        .object_index = -1,
        .point = {NAN, NAN, NAN}
    };

    float t_min = INFINITY;

    if (ray == NULL || scene == NULL) {
        return result;
    }

    // Iterate through all objects in the scene
    for (size_t i = 0; i < scene->n; i++) {

        Vec3 intersection = get_intersection(ray, i, scene);

        // Skip invalid intersections
        if (!isfinite(intersection.x) ||
            !isfinite(intersection.y) ||
            !isfinite(intersection.z))
        {
            continue;
        }

        Vec3 diff = vec3_sub(intersection, ray->origin);
        float t = vec3_length_squared(diff);

        // Keep the closest intersection
        if (t < t_min) {
            t_min = t;
            result.object_index = i;
            result.point = intersection;
        }
    }

    return result;
}
