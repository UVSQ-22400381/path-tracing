#include <stdlib.h>
#include <stdio.h>
#include "../include/scene.h"

int parse_sphere(struct Sphere* s, char* line) {
    return sscanf(&line[2], "%f %f %f %f",
                  &s->center.x, &s->center.y, &s->center.z,
                  &s->radius
    );
}

int parse_aabb(struct AABBox* b, char* line) {
    return sscanf(&line[2], "%f %f %f %f %f %f",
                  &b->low.x,  &b->low.y,  &b->low.z,
                  &b->high.x, &b->high.y, &b->high.z
    );
}

int load_scene(struct Scene* sc, char* path) {
    if (!sc) {
        return -1;
    }
    FILE *f = fopen(path, "r+");
    if (!f) {
        return -1;
    }

    const size_t LINE_LENGTH = 256;
    char line[LINE_LENGTH];
    size_t n = 0;
    if (fgets(line, LINE_LENGTH, f)) {
        sscanf(line, "%zu", &n);
    }

    int ok = init_scene(sc, n);
    if (ok < 0) {
        fclose(f);
        return -1;
    }

    size_t i = 0;
    while (fgets(line, LINE_LENGTH, f) && i < sc->n) {
        if (line[0] == '\n' || line[0] == '#') {
            continue;
        }

        int ok = 0;
        if (line[0] == 'S') {
            sc->shapetypes[i] = ST_SPHERE;
            ok = parse_sphere(&sc->shapes[i].sphere, &line[2]);
            ++i;
        } else if (line[0] == 'B') {
            sc->shapetypes[i] = ST_BOX;
            ok = parse_aabb(&sc->shapes[i].box, &line[2]);
            ++i;
        }

        if (ok < 0) {
            fclose(f);
            return -1;
        }
    }

    fclose(f);
    return 0;
}
