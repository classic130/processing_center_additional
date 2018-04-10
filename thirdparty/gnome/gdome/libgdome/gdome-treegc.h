/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/* gdome-treegc.h
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

#ifndef GDOME_TREEGC_H
#define GDOME_TREEGC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void gdome_treegc_addRef        (GdomeNode *node);
void gdome_treegc_delRef        (GdomeNode *node);
void gdome_treegc_removeSubtree (GdomeNode *node);
void gdome_treegc_insertSubtree (GdomeNode *node);
int  gdome_treegc_livenodes     (GdomeNode *node);
void gdome_treegc_adjust        (GdomeNode *node, int adj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GDOME_TREEGC_H */
