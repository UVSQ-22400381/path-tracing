#include <stdlib.h>
#include "scene.h"

void free_scene(struct Scene* s) {
    free(s->shapetypes);
    free(s->shapes);
    s->n = 0;
    s->shapetypes = NULL;
    s->shapes = NULL;
}
