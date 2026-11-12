
#include "collision.h"
#include <math.h>


/** Calculates the intersection of a ray with a sphere.
 * @param ray The ray to test intersection with
 * @param sphere The sphere to test intersection with
 * @return The parameter t of the intersection point, or -1.0f if no intersection
 */
float ray_sphere_intersection(const Ray *ray, const struct Sphere *sphere) {
    Vec3 oc = vec3_sub(ray->origin, sphere->center);
    float a = vec3_dot(ray->direction, ray->direction);
    //printf("a: %f\n", a);
    float b = 2.0f * vec3_dot(oc, ray->direction);
    //printf("b: %f\n", b);
    float c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
    //printf("c: %f\n", c);
    float discriminant = b * b - 4 * a * c;
    //printf("discriminant: %f\n", discriminant);
    if (discriminant < 0){
        return -1.0f; // No intersection
    } else {
        return (-b - sqrtf(discriminant)) / (2.0f * a); // Return the nearest intersection point
    } 
}

float ray_box_intersection(const Ray *ray, const struct AABBox *box) {
    float tminx, tmaxx;
    float tminy, tmaxy;
    float tminz, tmaxz;

    float t_close, t_far;
    float tmp;

    //Axe x
    if(ray->direction.x==0.0f){
        if(ray->origin.x < box->low.x || ray->direction.x > box->high.x){
            return -1.0f;
            tminx = -INFINITY;
            tmaxx = INFINITY;
        }
        else {
            tminx = (box->low.x - ray->origin.x) / ray->direction.x;
            tmaxx = (box->high.x - ray->origin.x) / ray->direction.x;
            if(tminx > tmaxx){
                tminx = tmp;
                tminx = tmaxx;
                tmaxx = tmp;
            }
        }
    }
    // Axe y 
     if (ray->direction.y == 0.0f) {
        if (ray->origin.y < box->low.y || ray->origin.y > box->high.y)
            return -1.0f;
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
            return -1.0f;
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
    t_far = fmaxf(tmaxx,fmaxf(tmaxy,tmaxz));

    //If no intersection
    if(t_close > t_far || t_far <0.0f){
        return -1.0f;
    }

    if (t_close < 0.0f)
        return t_far;

    return t_close;

}


