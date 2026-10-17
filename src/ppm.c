#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "renderer.h"

struct Image new_img(size_t width, size_t height) {
  const size_t size = sizeof(struct Pixel) * width * height;
  void *data = malloc(size);
  memset(data, 0, size);
  struct Image new = {.width = width, .height = height, .pixels = NULL};
  new.pixels = (struct Pixel*)data;
  return new;
}

void free_image(struct Image *img) {
  free(img->pixels);
  img->pixels = NULL;
}

void format_pixel_ascii(struct Pixel p, FILE *f, bool new_line) {
  fprintf(f, new_line ? "%d %d %d\n" : "%d %d %d   ", p.r, p.g, p.b);
}

int save_img_ascii(struct Image *img, char *path) {
  FILE *f = fopen(path, "w+");
  if (!f) {
    return -1;
  }

  fprintf(f, "P3\n%d %d\n255\n", img->width, img->height);

  const size_t len = img->width * img->height;
  for (size_t i = 0; i < len; i++) {
    format_pixel_ascii(img->pixels[i], f, (i % img->width == (img->width - 1)));
  }

  return 0;
}
