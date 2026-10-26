#include "unity.h"
#include "ray.h"
#include <math.h>

#define EPSILON 1e-5f
#define FOV 1.04719755f

static Camera test_camera(void)
{
    return (Camera){
        .position = {0.0f, 0.0f, 0.0f},
        .t = {1.0f, 0.0f, 0.0f},
        .v = {0.0f, 1.0f, 0.0f},
        .b = {0.0f, 0.0f, 1.0f}
    };

}


//Test 1 :
void test_ray_center(void)
{
    Camera cam = test_camera();

    Vec3 ray = ray_direction(&cam, 2, 2, 5, 5, FOV);

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0f, ray.x);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0f, ray.y);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0f, ray.z);
    
}

//Test 2 : 
void test_ray_is_normalized(void)
{
    Camera cam = test_camera();

    Vec3 ray = ray_direction(&cam, 0, 0, 5, 5, FOV);

    float norm = vec3_length(ray);

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0f, norm);
}

//Test 3 : 
void test_ray_directions_differ(void)
{
    Camera cam = test_camera();

    Vec3 ray1 = ray_direction(&cam, 0, 0, 5, 5, FOV);
    Vec3 ray2 = ray_direction(&cam, 4, 4, 5, 5, FOV);

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, ray1.z, -ray2.z);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, ray1.y, -ray2.y);
}



