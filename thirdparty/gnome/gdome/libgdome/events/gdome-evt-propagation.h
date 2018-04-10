/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/* gdome-evt-propagation.h
 *
 * Copyright (C) 1999 Raph Levien <raph@acm.org>
 * Copyright (C) 2000 Mathieu Lacage <mathieu@gnu.org>
 * Copyright (C) 2000 Anders Carlsson <andersca@gnu.org>
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

#ifndef GDOME_EVT_PROPUTIL_H
#define GDOME_XML_PROPUTIL_H

void      gdome_evt_invokeListeners (xmlNode *target,
                                     const char *type,
                                     GdomeEvent *event,
                                     GdomeBoolean useCapture);
void      gdome_evt_fireEvent       (GdomeEvent *event);

#endif /* GDOME_EVT_PROPUTIL_H */
