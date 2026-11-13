#include <stdlib.h>
#include "scene.h"

void free_scene(struct Scene* s) {
    free(s->shapetypes);
    free(s->colors);
    free(s->shapes);
    s->n = 0;
    s->shapetypes = NULL;
    s->colors = NULL;
    s->shapes = NULL;
}
