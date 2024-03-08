#include <stdio.h>
#include <stdlib.h>
#include "skyline.h"
#include <assert.h>

struct _node_t {
    height_t height;
    struct _node_t *next;
};

typedef struct _node_t *node_t;

skyline_t skyline_empty(void) {
    skyline_t result = NULL;
    return(result);
}

skyline_t skyline_destroy(skyline_t skyline) {
    skyline_t aux = NULL;
    while (skyline != NULL) {
        aux = skyline->next;
        free(skyline);
        skyline = aux;
    }
    return (skyline);
}

static node_t new_node(height_t height, node_t next) {
    skyline_t node = NULL;
    node = calloc(1, sizeof(struct _node_t));
    node->height = height;
    node->next = next;
    return node;
}

static skyline_t skyline_add_left(skyline_t skyline,  height_t height) {
    node_t node = new_node(height, skyline);
    return(node);
}

static node_t last_node(skyline_t skyline) {
    assert(skyline != NULL);
    node_t last = skyline;
    while (last->next != NULL) {
        last = last->next;
    }
    return last;
}

static skyline_t skyline_add_right(skyline_t skyline,  height_t height) {
    node_t node = new_node(height, NULL);
    skyline_t result = NULL;    
    if (skyline == NULL) {
        result = node;
    }
    else {
        node_t last = last_node(skyline);
        last->next = node;
        result = skyline;
    }
    return(result);
}

skyline_t skyline_add_building_left(skyline_t skyline, 
width_t width, height_t height){
    unsigned int i = 0;
    for (i = 0; i < width ; i++) {
	skyline = skyline_add_left(skyline, height);
    }
    return skyline;
}

skyline_t skyline_add_building_right(skyline_t skyline,
 width_t width, height_t height){
    unsigned int i = 0;
    for (i = 0; i < width ; i++) {
	skyline = skyline_add_right(skyline, height);
    }
    return skyline;
}

static height_t max_height (height_t h, height_t j) {
    height_t max = h;
    if (h < j) max = j;
    return max;
}

height_t skyline_max_height(skyline_t skyline) {
    assert (skyline != NULL);
    height_t max = 0;
    skyline_t current = skyline;
    while (current != NULL) {
        max = max_height(current->height, max); 
        current = current->next;
    }
    return max;
}


skyline_t skyline_overlay(skyline_t skyline_one , skyline_t skyline_two) {
    skyline_t sl1 = skyline_one;
    skyline_t sl2 = skyline_two;
    skyline_t new_sl = skyline_empty();
    while (sl1 != NULL || sl2 != NULL) {
        if (sl1 != NULL  && sl2 != NULL) {
            height_t height = max_height (sl1->height, sl2->height);
            new_sl = skyline_add_right(new_sl, height);
            sl1 = sl1->next;
            sl2 = sl2->next;
        }
        else if (sl1 != NULL) {
            new_sl = skyline_add_right(new_sl, sl1->height);
            sl1 = sl1->next;
        }
        else {
            new_sl = skyline_add_right(new_sl, sl2->height);
            sl2 = sl2->next;
        }
    }
    return new_sl;
}

skyline_t skyline_from_building(unsigned int start, width_t width, height_t height) {
    skyline_t skyline = skyline_empty();
    unsigned int i = 0;
    for (i=0 ; i < start; i++) {
	skyline = skyline_add_building_left(skyline,1,0);
    }
    skyline = skyline_add_building_right(skyline,width,height);
    return skyline;
}

skyline_t skyline_overlay_building(unsigned int start, width_t width, height_t height, skyline_t skyline) {
    skyline_t single = skyline_from_building(start, width, height);
    skyline_t result = skyline_overlay(skyline, single);
    return result;
}

void skyline_dump(skyline_t skyline) {
    node_t current = NULL;
    current = skyline;
    printf("\n[");
    while (current != NULL) {
        printf("%d ", current->height); 
        current = current->next;
    }
    printf("]\n"); 
}

