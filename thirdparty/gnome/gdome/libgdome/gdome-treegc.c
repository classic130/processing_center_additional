/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/* gdome-treegc.c
 *
 * CopyRight (C) 2001 Paolo Casarini <paolo@casarini.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <glib.h>
#include "gdome.h"
#include "gdome-events.h"
#include "gdome-refdebug.h"
#include <libxml/tree.h>
#include "gdome-xml-util.h"
#include "gdome-xml-xmlutil.h"
#include "gdome-xml-node.h"
#include "gdome-xml-document.h"

/**
 * gdome_treegc_isDetached:
 * @node:  the libxml2 node to test
 *
 * Returns #TRUE if the specified node id detached from the main Document tree.
 */
gboolean
gdome_treegc_isDetached (xmlNode *node)
{
  xmlNode *iter = node;

  while (iter->parent != NULL)
    iter = gdome_xmlGetParent(iter);

  return (iter == (xmlNode *)gdome_xmlGetOwner (node))?FALSE:TRUE;
}

/**
 * gdome_treegc_countLiveNodes:
 * @cur:  the libxml2 node that is the root of the subtree to check
 * @ln:  where to store the recursive result
 *
 * Counts how many nodes are referenced by the user application in the @cur
 * subtree.
 */
void
gdome_treegc_countLiveNodes (xmlNode *cur, int *ln)
{
	xmlNode *next;

	if (cur == NULL)
		return;

	while (cur != NULL) {
    next = cur->next;
		if (cur->children != NULL)
			gdome_treegc_countLiveNodes (cur->children, ln);
		if (cur->type != XML_ATTRIBUTE_NODE && 
				cur->type != XML_ENTITY_DECL && cur->properties != NULL)
			/*		if (cur->type != XML_ATTRIBUTE_NODE && cur->properties != NULL)*/
			gdome_treegc_countLiveNodes ((xmlNode *)cur->properties, ln);
		if (cur->_private != NULL)
			++(*ln);
    cur = next;
	}
}

/**
 * gdome_treegc_addRef:
 * @node:  the node to add to the document
 *
 * Increase the livenodes field if the specified node is attached to the
 * main doc tree or if it is a Notation or a Entity Declaration node.
 */
void
gdome_treegc_addRef (GdomeNode *node)
{
  Gdome_xml_Node *priv = (Gdome_xml_Node *)node;
  Gdome_xml_Document *ownerDoc;

  g_return_if_fail (priv != NULL);
  g_return_if_fail (GDOME_XML_IS_N(priv));

  if (gdome_xmlGetType (priv->n) == XML_NOTATION_NODE ||
      gdome_xmlGetType (priv->n) == XML_ENTITY_DECL ||
      !gdome_treegc_isDetached (priv->n)) {
		ownerDoc =  gdome_xmlGetOwner (priv->n)->_private;
		g_assert (ownerDoc != NULL);
		ownerDoc->livenodes++;
	}
}

/**
 * gdome_treegc_delRef:
 * @node:  the node to remove from the document
 *
 * Decrease the livenodes field if the specified node id attached to the
 * main doc tree or if it is a Notation or a Entity Declaration node.
 */
void
gdome_treegc_delRef (GdomeNode *node)
{
  Gdome_xml_Node *priv = (Gdome_xml_Node *)node;
  Gdome_xml_Document *ownerDoc;

  g_return_if_fail (priv != NULL);
  g_return_if_fail (GDOME_XML_IS_N(priv));

  if (gdome_xmlGetType (priv->n) == XML_NOTATION_NODE ||
      gdome_xmlGetType (priv->n) == XML_ENTITY_DECL ||
      !gdome_treegc_isDetached (priv->n)) {
		ownerDoc =  gdome_xmlGetOwner (priv->n)->_private;
		g_assert (ownerDoc != NULL);
		ownerDoc->livenodes--;

		if (ownerDoc->livenodes == 0) {
			ownerDoc->n->_private = NULL;

#ifdef DEBUG_REFCNT
			gdome_refdbg_delRef ((void *)ownerDoc, GDOME_REFDBG_NODE);
#endif

			xmlFreeDoc (ownerDoc->n);
      g_free (ownerDoc);
		}
  }
}

/**
 * gdome_treegc_removeSubtree:
 * @node:  the root node of the subtree to remove from the document
 *
 * Decrease the livenodes field of the Document main tree with the number of
 * live nodes present in the specifed subtree.
 */
void
gdome_treegc_removeSubtree (GdomeNode *node)
{
  Gdome_xml_Node *priv = (Gdome_xml_Node *)node;
	Gdome_xml_Document *ownerDoc;
	int ln = 0;

  g_return_if_fail (priv != NULL);
  g_return_if_fail (GDOME_XML_IS_N(priv));

	ownerDoc =  gdome_xmlGetOwner (priv->n)->_private;
	g_assert (ownerDoc != NULL);

	gdome_treegc_countLiveNodes (priv->n, &ln);

	ownerDoc->livenodes -= ln;
}

/**
 * gdome_treegc_insertSubtree:
 * @node:  the root node of the subtree to insert in the document
 *
 * Increase the livenodes field of the Document main tree with the number of
 * live nodes present in the specified subtree.
 */
void
gdome_treegc_insertSubtree (GdomeNode *node)
{
  Gdome_xml_Node *priv = (Gdome_xml_Node *)node;
	Gdome_xml_Document *ownerDoc;
  xmlNode *next;
	int ln = 0;

  g_return_if_fail (priv != NULL);
  g_return_if_fail (GDOME_XML_IS_N(priv));

	if (!gdome_treegc_isDetached (priv->n)) {
		ownerDoc =  gdome_xmlGetOwner (priv->n)->_private;
		g_assert (ownerDoc != NULL);

		next = gdome_xmlGetNext (priv->n);
		gdome_xmlSetNext(priv->n, NULL);
		gdome_treegc_countLiveNodes (priv->n, &ln);
		gdome_xmlSetNext (priv->n, next);

		ownerDoc->livenodes += ln;
  }
  else if (gdome_xmlGetType (priv->n) == XML_DOCUMENT_FRAG_NODE) {
    xmlNode *iter = NULL;

		ownerDoc =  gdome_xmlGetOwner (priv->n)->_private;
		g_assert (ownerDoc != NULL);

    for (iter = gdome_xmlGetFirstChild (priv->n);
         iter != gdome_xmlGetNext(gdome_xmlGetLastChild (priv->n));
         iter = gdome_xmlGetNext(iter)) {
      ln = 0;
      next = gdome_xmlGetNext (iter);
      gdome_xmlSetNext(iter, NULL);
      gdome_treegc_countLiveNodes (iter, &ln);
      gdome_xmlSetNext (iter, next);

      ownerDoc->livenodes += ln;
    }
  }
}

/**
 * gdome_treegc_livenodes:
 * @node:  a node in the Document main tree
 *
 * Returns the number of live nodes in the Document main tree.
 */
int
gdome_treegc_livenodes (GdomeNode *node)
{
  Gdome_xml_Node *priv = (Gdome_xml_Node *)node;
  Gdome_xml_Document *ownerDoc;

  g_return_val_if_fail (priv != NULL, -1);
  g_return_val_if_fail (GDOME_XML_IS_N(priv), -1);

  ownerDoc =  gdome_xmlGetOwner (priv->n)->_private;
	g_assert (ownerDoc != NULL);

  return ownerDoc->livenodes;
}

/**
 * gdome_treegc_adjust:
 * @node:  a node of the Document main tree
 * @adj:  the number of live node we want to add
 *
 * Adjust the number of live nodes in the Document main tree. If @adj is
 * positive, increases livenodes field else decreases it.
 */
void
gdome_treegc_adjust (GdomeNode *node, int adj)
{
  Gdome_xml_Node *priv = (Gdome_xml_Node *)node;
  Gdome_xml_Document *ownerDoc;

  g_return_if_fail (priv != NULL);
  g_return_if_fail (GDOME_XML_IS_N(priv));

  ownerDoc =  gdome_xmlGetOwner (priv->n)->_private;
  g_assert (ownerDoc != NULL);
  ownerDoc->livenodes += adj;
}
