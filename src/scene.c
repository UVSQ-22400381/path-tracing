#include <stdlib.h>
#include "scene.h"

struct Scene create_scene(size_t n) {
    struct Scene new = {NULL, NULL, n};
    new.shapetypes = malloc(sizeof(int) * n);
    if (!new.shapetypes) {
        new.n = 0;
        return new;
    }
    new.shapes = malloc(sizeof(*new.shapes) * n);
    if (!new.shapes) {
        new.n = 0;
        free(new.shapetypes);
        return new;
    }
    return new;
}

void free_scene(struct Scene* s) {
    free(s->shapetypes);
    free(s->shapes);
    s->shapetypes = NULL;
    s->shapes = NULL;
}
