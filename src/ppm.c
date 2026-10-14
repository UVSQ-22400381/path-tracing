#include "renderer.h"
#include <stdlib.h>

struct Image new_img(int width, int height) {
  char *data = malloc(3 * width * height);
  struct Image new = {.width = width, .height = height, .pixel = NULL};
  *(new.pixel) = data;
  return new;
}

void free_image(struct Image *img) {
  free(*(img->pixel));
}
