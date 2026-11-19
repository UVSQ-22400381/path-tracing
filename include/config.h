#ifndef CONFIG_H
#define CONFIG_H

#include "vec3.h"
#include "stddef.h"

struct RenderConfig {
  Vec3 cam_pos;
  Vec3 target;
  float fov;
  size_t height;
  size_t width;
};
typedef struct RenderConfig RenderConfig;

RenderConfig init_config(void);

#endif
