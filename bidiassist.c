/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 * vim:textwidth=78:tabstop=8:shiftwidth=8:autoindent:cindent
 */

/*
 * bidiassist.c
 * This file is part of gedit
 *
 * Copyright (C) 2005 Behnam Esfahbod <behnam@esfahbod.info>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, 
 * Boston, MA 02111-1307, USA. 
 */

/*
 * See the ChangeLog files for a list of changes. 
 */


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib/gutils.h>
#include <glib/gi18n.h>
#include <libgnomeui/gnome-stock-icons.h>

#include <gedit/gedit-menus.h>
#include <gedit/gedit-plugin.h>
#include <gedit/gedit-debug.h>
#include <gedit/gedit-prefs-manager.h>



G_MODULE_EXPORT GeditPluginState update_ui (GeditPlugin *plugin, BonoboWindow *window);
G_MODULE_EXPORT GeditPluginState activate (GeditPlugin *pd);
G_MODULE_EXPORT GeditPluginState deactivate (GeditPlugin *pd);
G_MODULE_EXPORT GeditPluginState init (GeditPlugin *pd);



/* CONFIGURATION */

#define BIDIASSIST_PARDIR
#define BIDIASSIST_MBDTXT
#define BIDIASSIST_OVRTXT
#define BIDIASSIST_CLRBDC


#define BIDIASSIST_MENUITEMS

#define BIDIASSIST_PARDIR_ACCELS
//#define BIDIASSIST_MBDTXT_ACCELS
//#define BIDIASSIST_OVRTXT_ACCELS
#define BIDIASSIST_CLRBDC_ACCELS

//#define BIDIASSIST_TOOLBARS



/* MENUS */

#ifdef BIDIASSIST_MENUITEMS

#define BIDIASSIST_MENU_PATH	"/menu/Edit/EditOps_5/"

#ifdef BIDIASSIST_PARDIR
	#define PARDIR_SUBMENU_LABEL		N_("Para_graph Direction")
	#define PARDIR_SUBMENU_NAME		"ParagraphDirection"	
	#define PARDIR_SUBMENU_PATH		BIDIASSIST_MENU_PATH PARDIR_SUBMENU_NAME"/"

	#define PARDIR_MENUITEM_LTR_LABEL	N_("_Left to Right")
	#define PARDIR_MENUITEM_LTR_TIP		N_("Change direction of selected paragraphs to Left to right")
	#define PARDIR_MENUITEM_LTR_NAME	"LeftToRightDirection"
	#define PARDIR_MENUITEM_LTR_ACCEL	"*Alt**Shift*L"
	#define PARDIR_MENUITEM_LTR_ICON	GNOME_STOCK_MENU_ALIGN_LEFT

	#define PARDIR_MENUITEM_RTL_LABEL	N_("_Right to Left")
	#define PARDIR_MENUITEM_RTL_TIP		N_("Change direction of selected paragraph to right to left")
	#define PARDIR_MENUITEM_RTL_NAME	"RightToLeftDirection"
	#define PARDIR_MENUITEM_RTL_ACCEL	"*Alt**Shift*R"
	#define PARDIR_MENUITEM_RTL_ICON	GNOME_STOCK_MENU_ALIGN_RIGHT

	#define PARDIR_MENUITEM_CLR_LABEL	N_("_Clear")
	#define PARDIR_MENUITEM_CLR_TIP		N_("Remove direction of paragraph")
	#define PARDIR_MENUITEM_CLR_NAME	"ClearDirection"	
	#define PARDIR_MENUITEM_CLR_ACCEL	"*Alt**Shift*C"
	#define PARDIR_MENUITEM_CLR_ICON	NULL

	gchar *pardir_sensible_verbs[] = {
		"/commands/" PARDIR_MENUITEM_LTR_NAME,
		"/commands/" PARDIR_MENUITEM_RTL_NAME,
		"/commands/" PARDIR_MENUITEM_CLR_NAME,
		NULL
	};
#endif // BIDIASSIST_PARDIR

#ifdef BIDIASSIST_MBDTXT
	#define MBDTXT_SUBMENU_LABEL		N_("Em_bedded Text")
	#define MBDTXT_SUBMENU_NAME		"EmbeddedText"	
	#define MBDTXT_SUBMENU_PATH		BIDIASSIST_MENU_PATH MBDTXT_SUBMENU_NAME"/"

	#define MBDTXT_MENUITEM_LTR_LABEL	N_("_Left to Right")
	#define MBDTXT_MENUITEM_LTR_TIP		N_("Change selected text's direction to embedded left-to-right")
	#define MBDTXT_MENUITEM_LTR_NAME	"LeftToRightEmbedded"
	#define MBDTXT_MENUITEM_LTR_ACCEL	"*Ctrl**Alt**Shift*L"
	#define MBDTXT_MENUITEM_LTR_ICON	GNOME_STOCK_MENU_ALIGN_LEFT

	#define MBDTXT_MENUITEM_RTL_LABEL	N_("_Right to Left")
	#define MBDTXT_MENUITEM_RTL_TIP		N_("Change selected text's direction to embedded right-to-left")
	#define MBDTXT_MENUITEM_RTL_NAME	"RightToLeftEmbedded"
	#define MBDTXT_MENUITEM_RTL_ACCEL	"*Ctrl**Alt**Shift*R"
	#define MBDTXT_MENUITEM_RTL_ICON	GNOME_STOCK_MENU_ALIGN_RIGHT

	gchar *mbdtxt_sensible_verbs[] = {
		"/commands/" MBDTXT_MENUITEM_LTR_NAME,
		"/commands/" MBDTXT_MENUITEM_RTL_NAME,
		NULL
	};
#endif // BIDIASSIST_MBDTXT

#ifdef BIDIASSIST_OVRTXT
	#define OVRTXT_SUBMENU_LABEL		N_("O_verride Text")
	#define OVRTXT_SUBMENU_NAME		"OverrideText"	
	#define OVRTXT_SUBMENU_PATH		BIDIASSIST_MENU_PATH OVRTXT_SUBMENU_NAME"/"

	#define OVRTXT_MENUITEM_LTR_LABEL	N_("_Left to Right")
	#define OVRTXT_MENUITEM_LTR_TIP		N_("Change selected text's direction to override left-to-right")
	#define OVRTXT_MENUITEM_LTR_NAME	"LeftToRightOverride"
	#define OVRTXT_MENUITEM_LTR_ACCEL	"*Ctrl**Alt**Shift*L"
	#define OVRTXT_MENUITEM_LTR_ICON	GNOME_STOCK_MENU_ALIGN_LEFT

	#define OVRTXT_MENUITEM_RTL_LABEL	N_("_Right to Left")
	#define OVRTXT_MENUITEM_RTL_TIP		N_("Change selected text's direction to override right-to-left")
	#define OVRTXT_MENUITEM_RTL_NAME	"RightToLeftOverride"
	#define OVRTXT_MENUITEM_RTL_ACCEL	"*Ctrl**Alt**Shift*R"
	#define OVRTXT_MENUITEM_RTL_ICON	GNOME_STOCK_MENU_ALIGN_RIGHT

	gchar *ovrtxt_sensible_verbs[] = {
		"/commands/" OVRTXT_MENUITEM_LTR_NAME,
		"/commands/" OVRTXT_MENUITEM_RTL_NAME,
		NULL
	};
#endif // BIDIASSIST_OVRTXT

#ifdef BIDIASSIST_CLRBDC
	#define CLRBDC_MENUITEM_LABEL		N_("Clear Bidirectional Characters")
	#define CLRBDC_MENUITEM_TIP		N_("Removes all bidirectional characters in selected paragraph")
	#define CLRBDC_MENUITEM_NAME		"ClearBidiChars"	
	#define CLRBDC_MENUITEM_ACCEL		"*Alt**Shift*X"
	#define CLRBDC_MENUITEM_PATH		BIDIASSIST_MENU_PATH OVRTXT_SUBMENU_NAME"/"
	#define CLRBDC_MENUITEM_ICON		NULL

	gchar *clrbdc_sensible_verbs[] = {
		"/commands/" CLRBDC_MENUITEM_NAME,
		NULL
	};
#endif // BIDIASSIST_CLRBDC

#endif // BIDIASSIST_MENUITEMS



/* UNICODE CONSTANTS */

#if defined(BIDIASSIST_PARDIR) || defined(BIDIASSIST_CLRBDC)
	#define UNICODE_LRM	(0x200E)
	#define UNICODE_RLM	(0x200F)
#endif

#if defined(BIDIASSIST_MBDTXT) || defined(BIDIASSIST_CLRBDC)
	#define UNICODE_LRE	(0x202A)
	#define UNICODE_RLE	(0x202B)
#endif

#if defined(BIDIASSIST_MBDTXT) || defined(BIDIASSIST_OVRTXT) || defined(BIDIASSIST_CLRBDC)
	#define UNICODE_PDF	(0x202C)
#endif

#if defined(BIDIASSIST_OVRTXT) || defined(BIDIASSIST_CLRBDC)
	#define UNICODE_LRO	(0x202D)
	#define UNICODE_RLO	(0x202E)
#endif

#ifdef BIDIASSIST_CLRBDC
	#define UNICODE_IS_BIDI_CHAR(c) (			    \
			(c) == UNICODE_LRM || (c) == UNICODE_RLM || \
			((c) >= UNICODE_LRE && (c) <= UNICODE_RLO))
#endif


/* FUNCTIONS */

#ifdef BIDIASSIST_PARDIR
static void
paragraph_direction (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname)
{
	GeditDocument *doc;
	GtkTextIter start, end, iter;
	gint i, start_line, end_line;

	gedit_debug (DEBUG_PLUGINS, "");

	doc = gedit_get_active_document ();
	g_return_if_fail (doc != NULL);

	gedit_document_begin_user_action (doc);

	gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER (doc), &start, &end);

	start_line = gtk_text_iter_get_line (&start);
	end_line = gtk_text_iter_get_line (&end);

	if ((gtk_text_iter_get_visible_line_offset (&end) == 0)  && (end_line > start_line))
		end_line--;

	for (i = start_line; i <= end_line; i++) {
		gtk_text_buffer_get_iter_at_line (GTK_TEXT_BUFFER (doc), &iter, i);

		/* don't change empty lines */
		if (gtk_text_iter_ends_line (&iter))
			continue;

		gchar mark[6];
		int mark_len;

		if (gtk_text_iter_get_char (&iter) == UNICODE_LRM ||
		    gtk_text_iter_get_char (&iter) == UNICODE_RLM) {
			gtk_text_iter_forward_char (&iter);
			gtk_text_buffer_backspace (GTK_TEXT_BUFFER (doc), &iter, FALSE, TRUE);
			gtk_text_buffer_get_iter_at_line (GTK_TEXT_BUFFER (doc), &iter, i);
		}

		if (g_strcasecmp (verbname, PARDIR_MENUITEM_CLR_NAME) == 0)
			continue;

		if (g_strcasecmp (verbname, PARDIR_MENUITEM_LTR_NAME) == 0)
			mark_len = g_unichar_to_utf8(UNICODE_LRM, mark);
		else if (g_strcasecmp (verbname, PARDIR_MENUITEM_RTL_NAME) == 0)
			mark_len = g_unichar_to_utf8(UNICODE_RLM, mark);

		gtk_text_buffer_insert (GTK_TEXT_BUFFER (doc), &iter, mark, mark_len);
	}

	gedit_document_end_user_action (doc);
}
#endif // BIDIASSIST_PARDIR


#if defined(BIDIASSIST_MBDTXT) || defined(BIDIASSIST_OVRTXT)
static void
embedded_and_override_text (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname)
{
	GeditDocument *doc;
	GtkTextIter start, end, iter;
	gint start_line, end_line;

	gedit_debug (DEBUG_PLUGINS, "");

	doc = gedit_get_active_document ();
	g_return_if_fail (doc != NULL);

	gedit_document_begin_user_action (doc);

	if (!gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER (doc),
				&start, &end))
		return;

	start_line = gtk_text_iter_get_line (&start);
	end_line = gtk_text_iter_get_line (&end);

	if ((gtk_text_iter_get_visible_line_offset (&end) == 0)  && (end_line > start_line))
		end_line--;

	/* just works for part of one paragraph */
	if (end_line != start_line)
		return;

	gtk_text_buffer_get_iter_at_line (GTK_TEXT_BUFFER (doc), &iter,
			start_line);
	/* don't change empty lines */
	if (gtk_text_iter_ends_line (&iter))
		return;

	gchar mark[2][6];
	int mark_len[2];

	// EmbeddedText
	if (g_strcasecmp (verbname, MBDTXT_MENUITEM_LTR_NAME) == 0) {
		mark_len[0] = g_unichar_to_utf8(UNICODE_LRE, mark[0]);
		mark_len[1] = g_unichar_to_utf8(UNICODE_PDF, mark[1]);
	}
	else if (g_strcasecmp (verbname, MBDTXT_MENUITEM_RTL_NAME) == 0) {
		mark_len[0] = g_unichar_to_utf8(UNICODE_RLE, mark[0]);
		mark_len[1] = g_unichar_to_utf8(UNICODE_PDF, mark[1]);
	}

	// OverrideText
	else if (g_strcasecmp (verbname, OVRTXT_MENUITEM_LTR_NAME) == 0) {
		mark_len[0] = g_unichar_to_utf8(UNICODE_LRO, mark[0]);
		mark_len[1] = g_unichar_to_utf8(UNICODE_PDF, mark[1]);
	}
	else if (g_strcasecmp (verbname, OVRTXT_MENUITEM_RTL_NAME) == 0) {
		mark_len[0] = g_unichar_to_utf8(UNICODE_RLO, mark[0]);
		mark_len[1] = g_unichar_to_utf8(UNICODE_PDF, mark[1]);
	}

	gtk_text_buffer_insert (GTK_TEXT_BUFFER (doc), &end, mark[1], mark_len[1]);
	gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER (doc), &start, &end);
	gtk_text_buffer_insert (GTK_TEXT_BUFFER (doc), &start, mark[0], mark_len[0]);

	gedit_document_end_user_action (doc);
}
#endif // BIDIASSIST_MBDTXT || BIDIASSIST_OVRTXT


#ifdef BIDIASSIST_CLRBDC
static void
clear_bidichars (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname)
{
	GeditDocument *doc;
	GtkTextIter start, end, iter;

	doc = gedit_get_active_document ();
	g_return_if_fail (doc != NULL);
	gedit_document_begin_user_action (doc);
	if (!gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER (doc),
				&start, &end))
		return;

	GString *s = g_string_new (NULL);

	while (!gtk_text_iter_is_end (&start) &&
	       !gtk_text_iter_equal (&start, &end))
	{
		gunichar c;

		c = gtk_text_iter_get_char (&start);
		if (!UNICODE_IS_BIDI_CHAR(c)) {
			g_string_append_unichar (s, c);
		}

		gtk_text_iter_forward_char (&start);
	}

	gtk_text_buffer_delete_selection (GTK_TEXT_BUFFER(doc), TRUE, TRUE);
	gtk_text_buffer_insert_at_cursor (GTK_TEXT_BUFFER(doc), s->str, s->len);

	g_string_free (s, TRUE);

	gedit_document_end_user_action (doc);
}
#endif // BIDIASSIST_CLRBDC



/* PLUGIN API */

G_MODULE_EXPORT GeditPluginState
update_ui (GeditPlugin *plugin, BonoboWindow *window)
{
	BonoboUIComponent *uic;
	GeditDocument *doc;
	GeditMDI *mdi;

	gedit_debug (DEBUG_PLUGINS, "");

	g_return_val_if_fail (window != NULL, PLUGIN_ERROR);
	uic = gedit_get_ui_component_from_window (window);
	doc = gedit_get_active_document ();
	mdi = gedit_get_mdi ();
	g_return_val_if_fail (mdi != NULL, PLUGIN_ERROR);

	if ((doc == NULL) || (gedit_document_is_readonly (doc)) ||
	    (gedit_mdi_get_state (mdi) != GEDIT_STATE_NORMAL)) {		
		#ifdef BIDIASSIST_MENUITEMS
		#ifdef BIDIASSIST_PARDIR
		gedit_menus_set_verb_list_sensitive (uic,
		    pardir_sensible_verbs, FALSE);
		#endif
		#ifdef BIDIASSIST_MBDTXT
		gedit_menus_set_verb_list_sensitive (uic,
		    mbdtxt_sensible_verbs, FALSE);
		#endif
		#ifdef BIDIASSIST_OVRTXT
		gedit_menus_set_verb_list_sensitive (uic,
		    ovrtxt_sensible_verbs, FALSE);
		#endif
		#ifdef BIDIASSIST_CLRBDC
		gedit_menus_set_verb_list_sensitive (uic,
		    clrbdc_sensible_verbs, FALSE);
		#endif
		#endif // BIDIASSIST_MENUITEMS
	}

	else {
		#ifdef BIDIASSIST_MENUITEMS
		#ifdef BIDIASSIST_PARDIR
		gedit_menus_set_verb_list_sensitive (uic,
		    pardir_sensible_verbs, TRUE);
		#endif
		#ifdef BIDIASSIST_MBDTXT
		gedit_menus_set_verb_list_sensitive (uic,
		    mbdtxt_sensible_verbs, TRUE);
		#endif
		#ifdef BIDIASSIST_OVRTXT
		gedit_menus_set_verb_list_sensitive (uic,
		    ovrtxt_sensible_verbs, TRUE);
		#endif
		#ifdef BIDIASSIST_CLRBDC
		gedit_menus_set_verb_list_sensitive (uic,
		    clrbdc_sensible_verbs, TRUE);
		#endif
		#endif // BIDIASSIST_MENUITEMS
	}

	return PLUGIN_OK;
}

G_MODULE_EXPORT GeditPluginState
activate (GeditPlugin *pd)
{
	GList *top_windows;
	BonoboUIComponent *ui_component;

        gedit_debug (DEBUG_PLUGINS, "");

        top_windows = gedit_get_top_windows ();
        g_return_val_if_fail (top_windows != NULL, PLUGIN_ERROR);

        while (top_windows)
        {
		#ifdef BIDIASSIST_MENUITEMS

		#ifdef BIDIASSIST_PARDIR
		gedit_menus_add_submenu (BONOBO_WINDOW (top_windows->data),
					 BIDIASSIST_MENU_PATH, PARDIR_SUBMENU_NAME,
					 PARDIR_SUBMENU_LABEL);
		gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
				     PARDIR_SUBMENU_PATH, PARDIR_MENUITEM_LTR_NAME,
				     PARDIR_MENUITEM_LTR_LABEL, PARDIR_MENUITEM_LTR_TIP, PARDIR_MENUITEM_LTR_ICON,
				     paragraph_direction);
		gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
				     PARDIR_SUBMENU_PATH, PARDIR_MENUITEM_RTL_NAME,
				     PARDIR_MENUITEM_RTL_LABEL, PARDIR_MENUITEM_RTL_TIP, PARDIR_MENUITEM_RTL_ICON,
				     paragraph_direction);
		gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
				     PARDIR_SUBMENU_PATH, PARDIR_MENUITEM_CLR_NAME,
				     PARDIR_MENUITEM_CLR_LABEL, PARDIR_MENUITEM_CLR_TIP, PARDIR_MENUITEM_CLR_ICON,
				     paragraph_direction);

		#ifdef BIDIASSIST_PARDIR_ACCELS
		ui_component = gedit_get_ui_component_from_window ( BONOBO_WINDOW (top_windows->data));
		bonobo_ui_component_set_prop (
			ui_component, "/commands/" PARDIR_MENUITEM_LTR_NAME, "accel", PARDIR_MENUITEM_LTR_ACCEL, NULL);
		bonobo_ui_component_set_prop (
			ui_component, "/commands/" PARDIR_MENUITEM_RTL_NAME, "accel", PARDIR_MENUITEM_RTL_ACCEL, NULL);
		bonobo_ui_component_set_prop (
			ui_component, "/commands/" PARDIR_MENUITEM_CLR_NAME, "accel", PARDIR_MENUITEM_CLR_ACCEL, NULL);
		#endif // BIDIASSIST_PARDIR_ACCELS
		#endif // BIDIASSIST_PARDIR


		#ifdef BIDIASSIST_MBDTXT
		gedit_menus_add_submenu (BONOBO_WINDOW (top_windows->data),
					 BIDIASSIST_MENU_PATH, MBDTXT_SUBMENU_NAME,
					 MBDTXT_SUBMENU_LABEL);
		gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
				     MBDTXT_SUBMENU_PATH, MBDTXT_MENUITEM_LTR_NAME,
				     MBDTXT_MENUITEM_LTR_LABEL, MBDTXT_MENUITEM_LTR_TIP, MBDTXT_MENUITEM_LTR_ICON,
				     embedded_and_override_text);
		gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
				     MBDTXT_SUBMENU_PATH, MBDTXT_MENUITEM_RTL_NAME,
				     MBDTXT_MENUITEM_RTL_LABEL, MBDTXT_MENUITEM_RTL_TIP, MBDTXT_MENUITEM_RTL_ICON,
				     embedded_and_override_text);

		#ifdef BIDIASSIST_MBDTXT_ACCELS
		ui_component = gedit_get_ui_component_from_window ( BONOBO_WINDOW (top_windows->data));
		bonobo_ui_component_set_prop (
			ui_component, "/commands/" MBDTXT_MENUITEM_LTR_NAME, "accel", MBDTXT_MENUITEM_LTR_ACCEL, NULL);
		bonobo_ui_component_set_prop (
			ui_component, "/commands/" MBDTXT_MENUITEM_RTL_NAME, "accel", MBDTXT_MENUITEM_RTL_ACCEL, NULL);
		#endif // BIDIASSIST_MBDTXT_ACCELS
		#endif // BIDIASSIST_MBDTXT


		#ifdef BIDIASSIST_OVRTXT
		gedit_menus_add_submenu (BONOBO_WINDOW (top_windows->data),
					 BIDIASSIST_MENU_PATH, OVRTXT_SUBMENU_NAME,
					 OVRTXT_SUBMENU_LABEL);
		gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
				     OVRTXT_SUBMENU_PATH, OVRTXT_MENUITEM_LTR_NAME,
				     OVRTXT_MENUITEM_LTR_LABEL, OVRTXT_MENUITEM_LTR_TIP, OVRTXT_MENUITEM_LTR_ICON,
				     embedded_and_override_text);
		gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
				     OVRTXT_SUBMENU_PATH, OVRTXT_MENUITEM_RTL_NAME,
				     OVRTXT_MENUITEM_RTL_LABEL, OVRTXT_MENUITEM_RTL_TIP, OVRTXT_MENUITEM_RTL_ICON,
				     embedded_and_override_text);

		#ifdef BIDIASSIST_OVRTXT_ACCELS
		ui_component = gedit_get_ui_component_from_window ( BONOBO_WINDOW (top_windows->data));
		bonobo_ui_component_set_prop (
			ui_component, "/commands/" OVRTXT_MENUITEM_LTR_NAME, "accel", OVRTXT_MENUITEM_LTR_ACCEL, NULL);
		bonobo_ui_component_set_prop (
			ui_component, "/commands/" OVRTXT_MENUITEM_RTL_NAME, "accel", OVRTXT_MENUITEM_RTL_ACCEL, NULL);
		#endif // BIDIASSIST_OVRTXT_ACCELS
		#endif // BIDIASSIST_OVRTXT


		#ifdef BIDIASSIST_CLRBDC
		gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
				     BIDIASSIST_MENU_PATH, CLRBDC_MENUITEM_NAME,
				     CLRBDC_MENUITEM_LABEL, CLRBDC_MENUITEM_TIP, CLRBDC_MENUITEM_ICON,
				     clear_bidichars);

		#ifdef BIDIASSIST_CLRBDC_ACCELS
		ui_component = gedit_get_ui_component_from_window ( BONOBO_WINDOW (top_windows->data));
		bonobo_ui_component_set_prop (
			ui_component, "/commands/" CLRBDC_MENUITEM_NAME, "accel", CLRBDC_MENUITEM_ACCEL, NULL);
		#endif // BIDIASSIST_CLRBDC_ACCELS
		#endif // BIDIASSIST_CLRBDC

		#endif // BIDIASSIST_MENUITEMS


                pd->update_ui (pd, BONOBO_WINDOW (top_windows->data));

                top_windows = g_list_next (top_windows);
        }

        return PLUGIN_OK;
}

G_MODULE_EXPORT GeditPluginState
deactivate (GeditPlugin *pd)
{
	gedit_debug (DEBUG_PLUGINS, "");

	#ifdef BIDIASSIST_MENUITEMS
	#ifdef BIDIASSIST_PARDIR
	gedit_menus_remove_submenu_all (PARDIR_SUBMENU_PATH,  PARDIR_SUBMENU_NAME);
	#endif
	#ifdef BIDIASSIST_MBDTXT
	gedit_menus_remove_submenu_all (MBDTXT_SUBMENU_PATH, MBDTXT_SUBMENU_NAME);
	#endif
	#ifdef BIDIASSIST_OVRTXT
	gedit_menus_remove_submenu_all (OVRTXT_SUBMENU_PATH, OVRTXT_SUBMENU_NAME);
	#endif
	#ifdef BIDIASSIST_CLRBDC
	gedit_menus_remove_menu_item_all (CLRBDC_MENUITEM_PATH, CLRBDC_MENUITEM_NAME);
	#endif
	#endif // BIDIASSIST_MENUITEMS

	return PLUGIN_OK;
}

G_MODULE_EXPORT GeditPluginState
init (GeditPlugin *pd)
{
	gedit_debug (DEBUG_PLUGINS, "");

	pd->private_data = NULL;

	return PLUGIN_OK;
}

