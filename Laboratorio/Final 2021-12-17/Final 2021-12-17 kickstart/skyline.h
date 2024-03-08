#ifndef SKYLINE_H
#define SKYLINE_H

typedef struct _node_t *skyline_t;
typedef unsigned int height_t;
typedef unsigned int width_t;

skyline_t skyline_empty();
skyline_t skyline_add_building(width_t width, height_t height, skyline_t skyline);
skyline_t skyline_overlay(skyline_t skyline_one , skyline_t skyline_two);
skyline_t skyline_from_building(unsigned int start, width_t width, height_t height);
skyline_t skyline_overlay_building(unsigned int start, width_t width, height_t height, skyline_t skyline);
height_t skyline_max_height(skyline_t skyline);
int skyline_area(skyline_t skyline);
void skyline_dump(skyline_t skyline);
skyline_t skyline_destroy(skyline_t skyline);

#endif
