#include "unity.h"
#include "config.h"

void test_config_load(void) {
	RenderConfig rc = init_config();

	TEST_ASSERT_EQUAL_FLOAT(1.0f, rc.cam_pos.x);
	TEST_ASSERT_EQUAL_FLOAT(2.5f, rc.cam_pos.y);
	TEST_ASSERT_EQUAL_FLOAT(3.25f, rc.cam_pos.z);

	TEST_ASSERT_EQUAL_FLOAT(-1.0f, rc.target.x);
	TEST_ASSERT_EQUAL_FLOAT(-2.0f, rc.target.y);
	TEST_ASSERT_EQUAL_FLOAT(-3.0f, rc.target.z);

	TEST_ASSERT_EQUAL_FLOAT(65.0f, rc.fov);

	TEST_ASSERT_EQUAL_INT64(2026, rc.width);
	TEST_ASSERT_EQUAL_INT64(2028, rc.height);
}
