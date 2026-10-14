#ifndef RENDERER_H
#define RENDERER_H

struct Image {
  int width;
  int height;
  char *pixel[3];
};

struct Image new_img(int width, int height);

void free_image(struct Image *img);

bool save_img_ascii(struct Image *img, char *path);

bool save_img_binary(struct Image *img, char *path);

void viewport_to_img(float *src, struct Image *dest);

#endif
