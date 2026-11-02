#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/scene.h"

struct TempScene {
    size_t n;
    union Shape *shapes;
    int *shapetypes;

    size_t len;
};

int init_temp(struct TempScene* tsc, size_t n) {
    if (!tsc) {
        return -1;
    }

    if (n == 0) {
        return 0;
    }

    void* mem = NULL;
    mem = malloc(sizeof(int) * n);
    if (!mem) {
        return -1;
    }
    tsc->shapetypes = mem;

    mem = malloc(sizeof(union Shape) * n);
    if (!mem) {
        free(tsc->shapetypes);
        return -1;
    }
    tsc->shapes = mem;

    tsc->n = n;
    tsc->len = 0;
    return 0;
}

void free_temp(struct TempScene* tsc) {
    free(tsc->shapes);
    free(tsc->shapetypes);
    tsc->shapes = NULL;
    tsc->shapetypes = NULL;
    tsc->len = 0;
    tsc->n = 0;
}

int parse_sphere(struct Sphere* s, char* line) {
    return sscanf(line, "%f %f %f %f",
                  &s->center.x, &s->center.y, &s->center.z,
                  &s->radius
    ) == 4 ? 0 : -1;
}

int parse_aabb(struct AABBox* b, char* line) {
    return sscanf(line, "%f %f %f %f %f %f",
                  &b->low.x,  &b->low.y,  &b->low.z,
                  &b->high.x, &b->high.y, &b->high.z
    ) == 6 ? 0 : -1;
}

int add_obj(struct TempScene* tsc, char* obj) {
    int ok = -1;
    if (tsc->len >= tsc->n) {
        return 0;
    }

    if (strlen(obj) < 2) {
        return ok;
    }

    if (obj[0] == 'S') {
        ok = parse_sphere(&tsc->shapes[tsc->len].sphere, obj + 2);
        if (ok == 0) {
            tsc->shapetypes[tsc->len] = ST_SPHERE;
            ++tsc->len;
        }
    } else if (obj[0] == 'B') {
        ok = parse_aabb(&tsc->shapes[tsc->len].box, obj + 2);
        if (ok == 0) {
            tsc->shapetypes[tsc->len] = ST_BOX;
            ++tsc->len;
        }
    }

    return ok;
}

#define EMPTY_SCENE (struct Scene){0, NULL, NULL}

struct Scene load_scene_file(char* path) {
    FILE *f = fopen(path, "r");
    if (!f) {
        return EMPTY_SCENE;
    }

    const size_t LINE_LENGTH = 256;
    char line[LINE_LENGTH];
    size_t n = 0;
    if (fgets(line, LINE_LENGTH, f)) {
        int ok = sscanf(line, "%zu", &n);
        if (ok != 1) {
            fclose(f);
            return EMPTY_SCENE;
        }
    }

    struct TempScene tsc = {0};
    int ok = init_temp(&tsc, n);
    if (ok < 0) {
        fclose(f);
        return EMPTY_SCENE;
    }

    while (fgets(line, LINE_LENGTH, f) && tsc.len < tsc.n) {
        if (line[0] == '\n' || line[0] == '#') {
            continue;
        }

        int ok = add_obj(&tsc, line);

        if (ok < 0) {
            fclose(f);
            free_temp(&tsc);
            return EMPTY_SCENE;
        }
    }

    fclose(f);
    return (struct Scene){
        .n = tsc.len,
        .shapetypes = tsc.shapetypes,
        .shapes = tsc.shapes
    };
}
