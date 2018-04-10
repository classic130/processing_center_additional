/*
 * xnvlist.h
 *
 * List of name-value pairs.
 */

#ifndef XNVLIST_H
#define XNVLIST_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct {
    char *name; 
    char *value;
    int  vlen;
} xnvlist_item_t;

typedef struct {
    long            length; /* number of items in list */
    xnvlist_item_t   *items; /* array of list elements. */
} xnvlist_t;

/*
 * Allocates an xnvlist_t and returns it.  Returns NULL on allocation
 * failure.
 */
xnvlist_t*
xnvlist_malloc(int list_size);

/*
 * Frees an xnvlist_t and any items in the list.
 */
void
xnvlist_free(xnvlist_t *list);

/*
 * Return a pointer pointing to the value of 
 * the specified name in the xnvlist.
 */
int
xnvlist_get(xnvlist_t *list, char *name, char **value, int *vlen);

/*
 * Set the name/value pair to the xnvlist 
 */
int 
xnvlist_set(xnvlist_t *list, char *name, char *value, int vlen);

/*
 * Duplicate the xnvlist.
 */
xnvlist_t *
xnvlist_dup(xnvlist_t *list);

/*
 * Duplicate the items in the nvlist.
 */
xnvlist_item_t *
xnvlist_items_dup(xnvlist_t *list);

#if defined(__cplusplus)
}
#endif

#endif /* end XNVLIST_H */
