#include <stdlib.h>
#include "scene.h"

int init_scene(struct Scene* sc, size_t n) {
    if (!sc) {
        return -1;
    }
    sc->n = n;
    sc->shapetypes = malloc(sizeof(int) * n);
    if (!sc->shapetypes) {
        sc->n = 0;
        return -1;
    }
    sc->shapes = malloc(sizeof(*sc->shapes) * n);
    if (!sc->shapes) {
        sc->n = 0;
        free(sc->shapetypes);
        return -1;
    }
    return 0;
}

void free_scene(struct Scene* s) {
    free(s->shapetypes);
    free(s->shapes);
    s->shapetypes = NULL;
    s->shapes = NULL;
}
