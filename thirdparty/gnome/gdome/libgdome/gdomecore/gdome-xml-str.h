/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/* gdome-xml-str.h
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


#ifndef GDOME_STR_FILE
#define GDOME_STR_FILE

GdomeDOMString     *gdome_xml_str_mkref           (const gchar *str);
GdomeDOMString     *gdome_xml_str_mkref_own       (gchar *str);
GdomeDOMString     *gdome_xml_str_mkref_xml       (xmlChar *str);
GdomeDOMString     *gdome_xml_str_mkref_dup       (const gchar *str);

void                gdome_xml_str_ref             (GdomeDOMString *self);
void                gdome_xml_str_unref           (GdomeDOMString *self);

GdomeBoolean        gdome_xml_str_equal           (GdomeDOMString *self,
                                                   GdomeDOMString *str);
GdomeBoolean        gdome_xml_str_equalIgnoreCase (GdomeDOMString *self,
                                                   GdomeDOMString *str);
gchar               gdome_xml_str_charAt          (GdomeDOMString *self,
                                                   int index);
GdomeDOMString *    gdome_xml_str_concat          (GdomeDOMString *self,
                                                   GdomeDOMString *str);
GdomeBoolean        gdome_xml_str_endsWith        (GdomeDOMString *self,
                                                   GdomeDOMString *suffix);
GdomeBoolean        gdome_xml_str_isEmpty         (GdomeDOMString *self);
int                 gdome_xml_str_length          (GdomeDOMString *self);
GdomeBoolean        gdome_xml_str_startsWith      (GdomeDOMString *self,
                                                   GdomeDOMString *prefix);

#endif /* GDOME_STR_FILE */
