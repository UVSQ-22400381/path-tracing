#ifndef RENDERER_H
#define RENDERER_H

typedef unsigned char byte;

struct Pixel {
  byte r, g, b;
}

struct Image {
  size_t width;
  size_t height;
  struct Pixel *pixels;
};

struct Image new_img(int width, int height);

void free_image(struct Image *img);

bool save_img_ascii(struct Image *img, char *path);

bool save_img_binary(struct Image *img, char *path);

#endif
