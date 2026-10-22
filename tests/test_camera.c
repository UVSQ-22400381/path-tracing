#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "raycast.h"

void test_cam_alloc(void){
    Vec3 pos= (Vec3){2,3,2};
    Vec3 t = (Vec3){1,0,0};
    Vec3 v = (Vec3){0,1,0};
    Vec3 b = (Vec3){0,0,1};

    Camera* cam = new_camera(pos);
    TEST_ASSERT_NOT_NULL(cam);
    TEST_ASSERT_EQUAL_FLOAT(pos.x, cam->position.x);
    TEST_ASSERT_EQUAL_FLOAT(pos.y, cam->position.y);
    TEST_ASSERT_EQUAL_FLOAT(pos.z, cam->position.z);
    TEST_ASSERT_EQUAL_FLOAT(t.x, cam->t.x);
    TEST_ASSERT_EQUAL_FLOAT(t.y, cam->t.y);
    TEST_ASSERT_EQUAL_FLOAT(t.z, cam->t.z);
    TEST_ASSERT_EQUAL_FLOAT(v.x, cam->v.x);
    TEST_ASSERT_EQUAL_FLOAT(v.y, cam->v.y);
    TEST_ASSERT_EQUAL_FLOAT(v.z, cam->v.z);
    TEST_ASSERT_EQUAL_FLOAT(b.x, cam->b.x);
    TEST_ASSERT_EQUAL_FLOAT(b.y, cam->b.y);
    TEST_ASSERT_EQUAL_FLOAT(b.z, cam->b.z);
    free(cam);
}
