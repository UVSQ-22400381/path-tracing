#ifndef RENDERER_H
#define RENDERER_H

typedef unsigned char byte;

struct Pixel {
  byte r, g, b;
};

struct Image {
  size_t width;
  size_t height;
  struct Pixel *pixels;
};

struct Image new_img(size_t width, size_t height);

void free_image(struct Image *img);

int save_img_ascii(struct Image *img, char *path);

// probably won't use this version
int save_img_binary(struct Image *img, char *path);

#endif
