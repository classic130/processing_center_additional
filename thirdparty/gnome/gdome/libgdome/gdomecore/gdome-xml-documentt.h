/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/* gdome-xml-documentt.h
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


/* ----------------------------------------------------------------------- */
/* ---------------------------  DOCUMENT_TYPE  --------------------------- */
/* ----------------------------------------------------------------------- */


#ifndef GDOME_DOCUMENT_TYPE_FILE
#define GDOME_DOCUMENT_TYPE_FILE

struct _GdomeDocumentTypeVtab {
  GdomeNodeVtab super;
  GdomeDOMString *(*name) (GdomeDocumentType *self, GdomeException *exc);
  GdomeNamedNodeMap *(*entities) (GdomeDocumentType *self, GdomeException *exc);
  GdomeNamedNodeMap *(*notations) (GdomeDocumentType *self, GdomeException *exc);
  GdomeDOMString *(*publicId) (GdomeDocumentType *self, GdomeException *exc);
  GdomeDOMString *(*systemId) (GdomeDocumentType *self, GdomeException *exc);
  GdomeDOMString *(*internalSubset) (GdomeDocumentType *self, GdomeException *exc);
};

typedef struct _Gdome_xml_DocumentType Gdome_xml_DocumentType;
struct _Gdome_xml_DocumentType {
  GdomeDocumentType super;
	const GdomeDocumentTypeVtab *vtab;
  int refcnt;
  xmlDtd *n;
  GdomeAccessType accessType;
  Gdome_xml_ListenerList *ll;
  xmlHashTable *entities;
  xmlHashTable *notations;
};

GdomeDocumentType   * gdome_xml_dt_mkref            (xmlDtd *n);
void                  gdome_xml_dt_unref            (GdomeNode *self,
                                                     GdomeException *exc);
gpointer              gdome_xml_dt_query_interface  (GdomeNode *self,
                                                     const char *interface,
                                                     GdomeException *exc);
GdomeDOMString      * gdome_xml_dt_name             (GdomeDocumentType *self,
																										 GdomeException *exc);
GdomeNamedNodeMap   * gdome_xml_dt_entities         (GdomeDocumentType *self, 
																										 GdomeException *exc);
GdomeNamedNodeMap   * gdome_xml_dt_notations        (GdomeDocumentType *self, 
																										 GdomeException *exc);
GdomeDOMString      * gdome_xml_dt_publicId         (GdomeDocumentType *self, 
																										 GdomeException *exc);
GdomeDOMString      * gdome_xml_dt_systemId         (GdomeDocumentType *self, 
																										 GdomeException *exc);
GdomeDOMString      * gdome_xml_dt_internalSubset   (GdomeDocumentType *self, 
																										 GdomeException *exc);
extern const GdomeDocumentTypeVtab gdome_xml_dt_vtab;

#endif /* GDOME_DOCUMENT_TYPE_FILE */






