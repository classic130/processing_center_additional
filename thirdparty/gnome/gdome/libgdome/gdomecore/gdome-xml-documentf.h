/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/* gdome-xml-documentf.h
 *
 * Copyright (C) 1999 Raph Levien <raph@acm.org>
 * Copyright (C) 2000 Mathieu Lacage <mathieu@gnu.org>
 * Copyright (C) 2001 Paolo Casarini <paolo@casarini.org>
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


/* --------------------------------------------------------------------------- */
/* ---------------------------  Document Fragment  --------------------------- */
/* --------------------------------------------------------------------------- */


#ifndef GDOME_DOCUMENT_FRAGMENT_FILE
#define GDOME_DOCUMENT_FRAGMENT_FILE

struct _GdomeDocumentFragmentVtab {
  GdomeNodeVtab super;
};

typedef struct _Gdome_xml_DocumentFragment Gdome_xml_DocumentFragment;
struct _Gdome_xml_DocumentFragment {
  GdomeDocumentFragment super;
	const GdomeDocumentFragmentVtab *vtab;
  int refcnt;
  xmlNode *n;
  GdomeAccessType accessType;
  Gdome_xml_ListenerList *ll;
};

gpointer   gdome_xml_df_query_interface (GdomeNode *self,
                                         const char *interface,
                                         GdomeException *exc);

extern const GdomeDocumentFragmentVtab gdome_xml_df_vtab;



#endif /* GDOME_DOCUMENT_FRAGMENT_FILE */



