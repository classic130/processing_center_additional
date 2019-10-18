/*
 * xattr.h
 *
 * External attributes utility functions
 */

#ifndef XATTR_H
#define XATTR_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct {
    char *name;
    char *value;
} xattr_list_item_t;

typedef struct {
    long               length;
    xattr_list_item_t  *items;
} xattr_list_t;


/*
 * Allocates an xattr_list_t and returns it.  Returns NULL on allocation
 * failure.
 */
xattr_list_t*
xattr_malloc(int list_size);

/*
 * Frees an xattr_list_t and any items in the list.
 */
void
xattr_free(xattr_list_t *list);

/*
 * Return a pointer pointing to the value of 
 * the specified name in the xattr.
 */
int
xattr_get(xattr_list_t *list, char *name, char **value);

/*
 * Set the name/value pair to the xattr.
 */
int 
xattr_set(xattr_list_t *list, char *name, char *value);

/*
 * Duplicate the xnvlist.
 */
xattr_list_t *
xattr_dup(xattr_list_t *list);

/*
 * Duplicate the items in the xattr.
 */
xattr_list_item_t *
xattr_items_dup(xattr_list_t *list);

#if defined(__cplusplus)
}
#endif

#endif /* end XATTR_H */
