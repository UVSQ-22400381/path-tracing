#include <stdlib.h>
#include <stdio.h>
#include "../include/scene.h"

int parse_sphere(struct Sphere* s, char* line);
int parse_aabb(struct AABCube* b, char* line);

int load_scene(char* path) {
  FILE *f = fopen(path, "r+");
  FILE *log = fopen("./scene-load.log", "w+");
  if (!f) {
    return -1;
  }
  if (!log) {
    fclose(f);
    return -1;
  }

  char line[256];
  size_t n = 0;
  if (fgets(line, 256, f)) {
    sscanf(line, "%zu", &n);
    fprintf(log, "N = %zu\n", n);
  }

  Vec3 cam_pos = {0};
  float cam_yaw = 0.f, cam_pitch = 0.f;
  if (fgets(line, 256, f)) {
    sscanf(line, "%f %f %f %f %f",
      &cam_pos.x, &cam_pos.y, &cam_pos.z,
      &cam_yaw, &cam_pitch
    );
    fprintf(log,
      "Camera is located at v3(%f, %f, %f) "
      "and is looking towards yaw %f and pitch %f\n",
      cam_pos.x, cam_pos.y, cam_pos.z,
      cam_yaw, cam_pitch
    );
  }

  while (fgets(line, sizeof(line), f)) {
    if (line[0] == '\n' || line[0] == '#') {
      continue;
    }

    union {
      struct Sphere  s;
      struct AABCube b;
    } shape;

    if (line[0] == 'S') {
      struct Sphere s = shape.s;
      sscanf(&line[2], "%f %f %f %f",
        &s.center.x, &s.center.y, &s.center.z,
        &s.radius
      );
      fprintf(log, "Sphere { center: v3(%f, %f, %f), radius: %f }\n",
        s.center.x, s.center.y, s.center.z, s.radius
      );
    } else if (line[0] == 'B') {
      struct AABCube b = shape.b;
      sscanf(&line[2], "%f %f %f %f %f %f",
        &b.low.x,  &b.low.y,  &b.low.z,
        &b.high.x, &b.high.y, &b.high.z
      );
      fprintf(log, "AABCube { low: v3(%f, %f, %f), high: v3(%f, %f, %f) }\n",
        b.low.x,  b.low.y,  b.low.z,
        b.high.x, b.high.y, b.high.z
      );
    }
  }
  fclose(f);
  fclose(log);
  return 0;
}
