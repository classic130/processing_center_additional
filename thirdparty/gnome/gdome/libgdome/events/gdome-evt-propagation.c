/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/* gdome-evt-propagation.c
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

/********************************************************************
 **  Helper functions for the Implementation of Event Propagation  **
 ********************************************************************/

#include <glib.h>
#include <string.h>
#include <libxml/tree.h>
#include "gdome.h"
#include "gdome-events.h"
#include "gdome-xml-node.h"
#include "gdome-evt-event.h"
#include "gdome-evt-eventl.h"
#include "gdome-evt-propagation.h"

static void
add_timestamp (GdomeEvent *event)
{
	Gdome_evt_Event *priv = (Gdome_evt_Event *)event;
  GTimeVal tv;

	g_get_current_time (&tv);

	if (priv->timestamp == 0)
#ifdef WINNT
		priv->timestamp = (tv.tv_sec * (__int64)1000) + tv.tv_usec / 1000;
#else
		priv->timestamp = (tv.tv_sec * (long long)1000) + tv.tv_usec / 1000;
#endif
}

void
gdome_evt_invokeListeners (xmlNode *target,
                           const char *type,
                           GdomeEvent *event,
                           GdomeBoolean useCapture)
{
  Gdome_xml_Node *node = target->_private;
	Gdome_xml_ListenerList *ll, *prev = NULL;
  GdomeException exc = 0;

  g_return_if_fail (node != NULL);

	add_timestamp (event);
	ll = node->ll;
	while (ll) {
    if ((useCapture == ll->useCapture) && !strcmp (type, ll->type)) {
			g_assert (!ll->toRemove);
			ll->processing = TRUE;
			gdome_evntl_handleEvent (ll->listener, event, &exc);
			/* todo: handle exceptions */
			ll->processing = FALSE;
		}

    /* remove the listener if marked to be removed */
		if (ll->toRemove) {
      g_assert (!ll->processing);
			if (prev)
				prev->next = ll->next;
			else {
				g_assert (node->ll == ll);
				node->ll = node->ll->next;
			}
			ll->next = NULL;
      gdome_evt_evntl_unref ((GdomeEventListener *)ll, &exc);
			g_free (ll);

			if (prev)
				ll = prev->next;
			else
        ll = node->ll;
		}
		else {
			prev = ll;
			ll = ll->next;
		}
	}
}

void
gdome_evt_fireEvent (GdomeEvent *event)
{
	xmlNode *path_stat[256];
	xmlNode **path;
	int n_path, n_path_max;
	int i;
	xmlNode *p;
	Gdome_evt_Event *ev_priv = (Gdome_evt_Event *)event;
	Gdome_xml_Node *priv = (Gdome_xml_Node *)ev_priv->target;
	const GdomeBoolean do_capture = TRUE;

	add_timestamp (event);

	path = path_stat;

	p = priv->n;
	for (i = 0; i < sizeof(path_stat) / sizeof(path_stat[0]); i++) {
    if (p == NULL)
      break;
    path[i] = p;
    p = p->parent;
  }

	if (p != NULL) {
    n_path_max = i << 1;
    path = g_new (xmlNode *, n_path_max);
    memcpy (path, path_stat, sizeof(path_stat));
    do {
      if (i == n_path_max)
        path = g_renew (xmlNode *, path, (n_path_max <<= 1));
      i++;
      p = p->parent;
    } while (p != NULL);
  }

	n_path = i;

  ev_priv->default_prevented = FALSE;
	ev_priv->propagation_stopped = FALSE;

	if (do_capture) {
    ev_priv->eventPhase = GDOME_CAPTURING_PHASE;
    for (i = n_path - 1; i > 0; i--) {
      /* Set currentTarget on the event before invoking listeners */
      if (path[i]->_private != NULL) {
        ev_priv->currentTarget = path[i];
        gdome_evt_invokeListeners (path[i], ev_priv->type, event, TRUE);
      }
      if (ev_priv->propagation_stopped)
        break;
    }
  }

  if (!ev_priv->propagation_stopped) {
    ev_priv->eventPhase = GDOME_AT_TARGET;
    ev_priv->currentTarget = path[0];
    gdome_evt_invokeListeners (path[0], ev_priv->type, event, FALSE);

    if (!ev_priv->propagation_stopped && ev_priv->bubbles) {
      ev_priv->eventPhase = GDOME_BUBBLING_PHASE;
      for (i = 1; i < n_path; i++) {
        /* Set currentTarget on the event after invoking listeners */
        if (path[i]->_private != NULL) {
          ev_priv->currentTarget = path[i];
          gdome_evt_invokeListeners (path[i], ev_priv->type, event, FALSE);
        }
        if (ev_priv->propagation_stopped)
          break;
      }
    }
  }

  if (path != path_stat)
    g_free (path);
}
