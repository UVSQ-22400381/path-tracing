#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "raycast.h"

void test_cam_alloc(void){
    const Vec3 pos    = { 2.f, 3.f, 2.f };
    const Vec3 target = vec3_add(pos, (Vec3){ 1.f, 0.f, 0.f });
    const Vec3 t = { 1.f, 0.f, 0.f };
    const Vec3 v = { 0.f, 1.f, 0.f };
    const Vec3 b = { 0.f, 0.f, 1.f };

    Camera* cam = new_camera(pos, target);
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
