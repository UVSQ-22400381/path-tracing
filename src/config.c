#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#define CONFIG_FILE "config.ini"

enum RCField {
  RCF_CAMPOS,
  RCF_TARGET,
  RCF_FOV,
  RCF_HEIGHT,
  RCF_WIDTH,
};

static RenderConfig default_config(void) {
  return (RenderConfig){
    .cam_pos  = (Vec3){0.f, 0.f, 0.f},
    .target   = (Vec3){1.f, 0.f, 0.f},
    .fov      = 60.0,
    .height   = 512,
    .width    = 512,
  };
}

Vec3 parse_vec(const char *str) {
  if (!str)
    return (Vec3){NAN, NAN, NAN};
  Vec3 v = {0.f, 0.f, 0.f};
  int n = sscanf(str, "%f;%f;%f", &v.x, &v.y, &v.z);

  return (n != 3) ? (Vec3){NAN, NAN, NAN} : v;
}

float parse_num(const char *str) {
  if (!str) return NAN;
  char *end;
  float f = strtof(str, &end);

  return end != str ? f : NAN;
}

size_t parse_int(const char *str) {
  if (!str) return 0;
  size_t x = strtoull(str, NULL, 10);

  return x;
}

int match_field(char *field) {
  if (!field) return -1;

  if (strcmp(field, "cam_pos") == 0)
    return RCF_CAMPOS;
  else if (strcmp(field, "target") == 0)
    return RCF_TARGET;
  else if (strcmp(field, "fov") == 0)
    return RCF_FOV;
  else if (strcmp(field, "height") == 0)
    return RCF_HEIGHT;
  else if (strcmp(field, "width") == 0)
    return RCF_WIDTH;
  else
    return -1;
}

void assign_config_value(RenderConfig *rc, char *line) {
  char* field = strtok(line, "=");
  char* remaining = strtok(NULL, " ");

  switch (match_field(field)) {
    default:
      return;

    case RCF_CAMPOS: {
      const Vec3 v = parse_vec(remaining);
      if (isnormal(v.x) && isnormal(v.y) && isnormal(v.z))
        rc->cam_pos = v;
      break;
    }

    case RCF_TARGET: {
      const Vec3 v = parse_vec(remaining);
      if (isnormal(v.x) && isnormal(v.y) && isnormal(v.z))
        rc->target = v;
      break;
    }

    case RCF_FOV: {
      const float x = parse_num(remaining);
      if (isnormal(x)) rc->fov = x; 
      break;
    }

    case RCF_HEIGHT: {
      const size_t x = parse_int(remaining);
      if (x != 0) rc->height = x; 
      break;
    }

    case RCF_WIDTH: {
      const size_t x = parse_int(remaining);
      if (x != 0) rc->width = x; 
      break;
    }
  }
}

RenderConfig init_config(void) {
  RenderConfig conf = default_config();

  FILE *f = fopen("./"CONFIG_FILE, "r");
  if (!f) {
    fprintf(stderr, "config file not found, using default configuration\n");
    return conf;
  }

  const size_t LINE_LENGTH = 128;
  char line[LINE_LENGTH];
  while (fgets(line, LINE_LENGTH, f)) {
    assign_config_value(&conf, line);
  }

  return conf;
}
