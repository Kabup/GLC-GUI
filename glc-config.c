/*
 * config.c
 *
 * Copyright 2016 Kabup <kabup@kabup-pc>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 * Author Kabup <kabup2@gmail.com>
 *
 */

#include "support.h"
#include <stdlib.h>     /* getenv, system */
#include <glib.h>

#define CONF_FILE ".glc-gui"

int read_config()
{
	/* Open config file
	 * if not exists, create it
	 * read data and fill the liststore
	 * set combo with liststore
	 * enable/disable buttons
	*/

	/* create/open config file */
	GKeyFile *keyfile;
	GKeyFileFlags flags = G_KEY_FILE_NONE;
	GError *error = NULL;
	/* get filename, create file */
	char filename[256];
	sprintf( filename, "%s/%s", getenv( "HOME" ), CONF_FILE );
	FILE *fp;
	fp = fopen( filename, "a");
	fclose(fp);
	/* open config file */
	keyfile = g_key_file_new ();
	if (! g_key_file_load_from_file (keyfile, filename, flags, &error))
		return(-1);

	/* create list */
	GtkListStore *liststore;
	liststore = gtk_list_store_new( 33, G_TYPE_STRING,
					G_TYPE_STRING, G_TYPE_STRING,
					G_TYPE_STRING, G_TYPE_STRING,
					G_TYPE_INT,
					G_TYPE_INT, G_TYPE_DOUBLE,	G_TYPE_INT,
					G_TYPE_INT, G_TYPE_INT,	G_TYPE_INT,
					G_TYPE_INT, G_TYPE_BOOLEAN,
					G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
					G_TYPE_STRING, G_TYPE_BOOLEAN,
					G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
					G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING,
					G_TYPE_INT,
					G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
					G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
					G_TYPE_INT, G_TYPE_INT, G_TYPE_INT );
	/* create variables */
	gchar *ls0;
	gchar *ls1, *ls2, *ls3, *ls4;
	gint ls5;
	gint ls6;
	gdouble ls7;
	gint ls8, ls9, ls10, ls11, ls12;
	gboolean ls13;
	gboolean ls14, ls15, ls16;
	gchar *ls17;
	gboolean ls18;
	gboolean ls19, ls20;
	gint ls21;
	gchar *ls22, *ls23;
	gint ls24;
	gboolean ls25, ls26, ls27, ls28, ls29;
	gint ls30, ls31, ls32;

	/* scan keyfile for groups, get values */
	gchar **listgroups = NULL;
	gint i, count=0;
	listgroups = g_key_file_get_groups( keyfile, NULL );
	for (i=0;listgroups[i] != NULL;i++)
	{
		/* get values from config file */
		ls0 = listgroups[i];
		ls1 = g_key_file_get_string( keyfile, ls0, "glcpath", NULL );
		ls2 = g_key_file_get_string( keyfile, ls0, "application", NULL );
		ls3 = g_key_file_get_string( keyfile, ls0, "outfile", NULL );
		ls4 = g_key_file_get_string( keyfile, ls0, "logfile", NULL );
		ls5 = g_key_file_get_integer( keyfile, ls0, "loglvl", NULL );
		ls6 = g_key_file_get_integer( keyfile, ls0, "video_fps", NULL );
		ls7 = g_key_file_get_double( keyfile, ls0, "video_resize", NULL );
		ls8 = g_key_file_get_integer( keyfile, ls0, "video_cropw", NULL );
		ls9 = g_key_file_get_integer( keyfile, ls0, "video_croph", NULL );
		ls10 = g_key_file_get_integer( keyfile, ls0, "video_cropx", NULL );
		ls11 = g_key_file_get_integer( keyfile, ls0, "video_cropy", NULL );
		ls12 = g_key_file_get_integer( keyfile, ls0, "video_colorspace", NULL);
		ls13 = g_key_file_get_boolean( keyfile, ls0, "video_lockfps", NULL);
		ls14 = g_key_file_get_boolean( keyfile, ls0, "audio_disable", NULL );
		ls15 = g_key_file_get_boolean( keyfile, ls0, "audio_skip", NULL );
		ls16 = g_key_file_get_boolean( keyfile, ls0, "audio_pulse", NULL );
		ls17 = g_key_file_get_string( keyfile, ls0, "audio_devices", NULL);
		ls18 = g_key_file_get_boolean( keyfile, ls0, "audio_sdl", NULL );
		ls19 = g_key_file_get_boolean( keyfile, ls0, "common_start", NULL);
		ls20 = g_key_file_get_boolean( keyfile, ls0, "common_draw", NULL);
		ls21 = g_key_file_get_integer( keyfile, ls0, "common_capbuf", NULL );
		ls22 = g_key_file_get_string( keyfile, ls0, "common_hotkey", NULL);
		ls23 = g_key_file_get_string( keyfile, ls0, "common_reload", NULL);
		ls24 = g_key_file_get_integer( keyfile, ls0, "common_compression", NULL );
		ls25 = g_key_file_get_boolean( keyfile, ls0, "other_pbo", NULL);
		ls26 = g_key_file_get_boolean( keyfile, ls0, "other_sync", NULL);
		ls27 = g_key_file_get_boolean( keyfile, ls0, "other_byte", NULL);
		ls28 = g_key_file_get_boolean( keyfile, ls0, "other_sig", NULL);
		ls29 = g_key_file_get_boolean( keyfile, ls0, "other_glf", NULL);
		ls30 = g_key_file_get_integer( keyfile, ls0, "other_comp", NULL );
		ls31 = g_key_file_get_integer( keyfile, ls0, "other_uncomp", NULL );
		ls32 = g_key_file_get_integer( keyfile, ls0, "other_unscaled", NULL );
		/* store the values in liststore */
		gtk_list_store_insert_with_values( liststore, NULL, -1,
								0, ls0, 1, ls1,	2, ls2, 3, ls3,
								4, ls4, 5, ls5,	6, ls6, 7, ls7,
								8, ls8, 9, ls9,	10, ls10, 11, ls11,
								12, ls12, 13, ls13, 14, ls14, 15, ls15,
								16, ls16, 17, ls17, 18, ls18,
								19, ls19, 20, ls20, 21, ls21, 22, ls22,
								23, ls23, 24, ls24,
								25, ls25, 26, ls26, 27, ls27, 28, ls28,
								29, ls29, 30, ls30, 31, ls31, 32, ls32,
										 -1 );
		count++;
	}
	g_strfreev ( listgroups );

	/* save/close keyfile */
	if ( ! g_key_file_save_to_file( keyfile, filename, &error ) )
		return(-1);
	g_key_file_free( keyfile );

	/* set combo with data, point to first row */
	gtk_combo_box_set_model ( GTK_COMBO_BOX( data->combo_profile ), GTK_TREE_MODEL( liststore ) );
	gtk_combo_box_set_active( GTK_COMBO_BOX( data->combo_profile ), 0 );
	/* release liststore */
	g_object_unref(liststore);

	/* enable/disable buttons */
	if( count > 0 )
	{
		gtk_widget_set_sensitive ( data->main_button_rec, TRUE );
		gtk_widget_set_sensitive ( data->main_button_edit, TRUE );
	} else {
		gtk_widget_set_sensitive ( data->main_button_rec, FALSE );
		gtk_widget_set_sensitive ( data->main_button_edit, FALSE );
	}

	return(0);
}

int write_config ()
{
	/* create/open keyfile
	 * retrieve data from edit window,
	 * loop through config,
	 * save in config file (new or old)
	 */

	/* open or create config file */
	GKeyFile *keyfile;
	GKeyFileFlags flags = G_KEY_FILE_NONE;
	GError *error = NULL;
	/* get filename, create file */
	char filename[256];
	sprintf( filename, "%s/%s", getenv( "HOME" ), CONF_FILE );
	FILE *fp;
	fp = fopen( filename, "a");
	fclose(fp);
	/* open config file */
	keyfile = g_key_file_new ();
	if (! g_key_file_load_from_file (keyfile, filename, flags, &error))
		return -1;

	gint i;
	/* get data from edit window */
	const gchar *ls0 = gtk_label_get_text( GTK_LABEL( data->edit_label ) );
	const gchar *ls1 = gtk_entry_get_text( GTK_ENTRY( data->edit_entry_glc ) );
	const gchar *ls2 = gtk_entry_get_text( GTK_ENTRY( data->edit_entry_app ) );
	const gchar *ls3 = gtk_entry_get_text( GTK_ENTRY( data->edit_entry_out ) );
	const gchar *ls4 = gtk_entry_get_text( GTK_ENTRY( data->edit_entry_log ) );
	const gint ls5 = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->edit_spin_log ) );
	const gint ls6 = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_fps ) );
	const gdouble ls7 = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_resize ) );
	const gint ls8 = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_crop_w ) );
	const gint ls9 = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_crop_h ) );
	const gint ls10 = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_crop_x ) );
	const gint ls11 = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_crop_y ) );
	if( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->video_radio_bgr ) ) )
		{ i = 1; } else { i = 2; }
	const gint ls12 = i;
	const gboolean ls13 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->video_check_lockfps ) );
	const gboolean ls14 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->audio_check_disable ) );
	const gboolean ls15 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->audio_check_skip ) );
	const gboolean ls16 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->audio_check_pulse ) );
	const gchar *ls17 = gtk_entry_get_text( GTK_ENTRY( data->audio_entry_devices ) );
	const gboolean ls18 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->audio_check_sdl ) );
	const gboolean ls19 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->common_check_start ) );
	const gboolean ls20 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->common_check_draw ) );
	if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->common_radio_front ) ) )
		{ i = 1; } else { i = 2; }
	const gint ls21 = i;
	const gchar *ls22 = gtk_entry_get_text( GTK_ENTRY( data->common_entry_hotkey ) );
	const gchar *ls23 = gtk_entry_get_text( GTK_ENTRY( data->common_entry_reload ) );
	if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->common_radio_none ) ) )
	{
		i = 1;
	} else if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->common_radio_quicklz ) ) )
	{
		i = 2;
	} else {
		i = 3;
	}
	const gint ls24 = i;
	const gboolean ls25 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->other_check_pbo ) );
	const gboolean ls26 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->other_check_sync ) );
	const gboolean ls27 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->other_check_byte ) );
	const gboolean ls28 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->other_check_sig ) );
	const gboolean ls29 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->other_check_glf ) );
	const gint ls30 = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->other_spin_comp ) );
	const gint ls31 = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->other_spin_uncomp ) );
	const gint ls32 = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->other_spin_unscaled ) );

	/* save data in file */
	g_key_file_set_string( keyfile, ls0, "glcpath", ls1 );
	g_key_file_set_string( keyfile, ls0, "application", ls2 );
	g_key_file_set_string( keyfile, ls0, "outfile", ls3 );
	g_key_file_set_string( keyfile, ls0, "logfile", ls4 );
	g_key_file_set_integer( keyfile, ls0, "loglvl", ls5 );
	g_key_file_set_integer( keyfile, ls0, "video_fps", ls6 );
	g_key_file_set_double( keyfile, ls0, "video_resize", ls7 );
	g_key_file_set_integer( keyfile, ls0, "video_cropw", ls8 );
	g_key_file_set_integer( keyfile, ls0, "video_croph", ls9 );
	g_key_file_set_integer( keyfile, ls0, "video_cropx", ls10 );
	g_key_file_set_integer( keyfile, ls0, "video_cropy", ls11 );
	g_key_file_set_integer( keyfile, ls0, "video_colorspace", ls12 );
	g_key_file_set_boolean( keyfile, ls0, "video_lockfps", ls13 );
	g_key_file_set_boolean( keyfile, ls0, "audio_disable", ls14 );
	g_key_file_set_boolean( keyfile, ls0, "audio_skip", ls15 );
	g_key_file_set_boolean( keyfile, ls0, "audio_pulse", ls16 );
	g_key_file_set_string( keyfile, ls0, "audio_devices", ls17 );
	g_key_file_set_boolean( keyfile, ls0, "audio_sdl", ls18 );
	g_key_file_set_boolean( keyfile, ls0, "common_start", ls19 );
	g_key_file_set_boolean( keyfile, ls0, "common_draw", ls20 );
	g_key_file_set_integer( keyfile, ls0, "common_capbuf", ls21 );
	g_key_file_set_string( keyfile, ls0, "common_hotkey", ls22 );
	g_key_file_set_string( keyfile, ls0, "common_reload", ls23 );
	g_key_file_set_integer( keyfile, ls0, "common_compression", ls24 );
	g_key_file_set_boolean( keyfile, ls0, "other_pbo", ls25 );
	g_key_file_set_boolean( keyfile, ls0, "other_sync", ls26 );
	g_key_file_set_boolean( keyfile, ls0, "other_byte", ls27 );
	g_key_file_set_boolean( keyfile, ls0, "other_sig", ls28 );
	g_key_file_set_boolean( keyfile, ls0, "other_glf", ls29 );
	g_key_file_set_integer( keyfile, ls0, "other_comp", ls30 );
	g_key_file_set_integer( keyfile, ls0, "other_uncomp", ls31 );
	g_key_file_set_integer( keyfile, ls0, "other_unscaled", ls32 );

	/* save/close keyfile */
	if ( ! g_key_file_save_to_file( keyfile, filename, &error ) )
		return(-1);
	g_key_file_free( keyfile );
	/* reset combo box */
	if( read_config() == -1 )
		return(-1);

	return(0);
}

int new_profile()
{
	/* check new profile name against
	 * name profiles in combobox
	 * return if exists, otherwise
	 * clear edit window */

	/* profile text is empty? */
	const gchar *string;
	string = gtk_entry_get_text( GTK_ENTRY( data->text_profile ) );
	if ( ! string[0] )
		return(-1);
	/* set initial values */
	GtkTreeModel *model;
	GtkTreeIter iter;
	model = gtk_combo_box_get_model( GTK_COMBO_BOX( data->combo_profile ) );
	gint rows = gtk_tree_model_iter_n_children( GTK_TREE_MODEL( model ), NULL );
	gtk_tree_model_get_iter_first( model, &iter );

	/* loop for duplicate entry */
	gchar *combo_str = NULL;
	gint i = 0;
	for (i=0;i<rows;i++)
	{
		/* get value */
		gtk_tree_model_get( model, &iter, 0, &combo_str, -1 );
		/* is the same */
		if ( ! g_strcmp0( string, combo_str ) )
			return(-1);
		/* next */
		gtk_tree_model_iter_next( model, &iter );
	}

	/* new profile, reset fields with defaults */
	pdata->profilename = g_strdup( string );
	pdata->glccapture = g_strdup( "" );
	pdata->application = g_strdup( "" );
	pdata->outfile = g_strdup( "" );
	pdata->logfile = g_strdup( "" );
	pdata->loglevel = 0;
	pdata->fps = 30;
	pdata->resize = 1;
	pdata->cropw = 0;
	pdata->croph = 0;
	pdata->cropx = 0;
	pdata->cropy = 0;
	pdata->colorspace = 2;
	pdata->lockfps = FALSE;
	pdata->disable = FALSE;
	pdata->skip = FALSE;
	pdata->pulse = FALSE;
	pdata->devices = g_strdup( "" );
	pdata->sdl = FALSE;
	pdata->start = FALSE;
	pdata->draw = FALSE;
	pdata->capbuf = 1;
	pdata->hotkey = g_strdup( "" );
	pdata->reload = g_strdup( "" );
	pdata->compression = 2;
	pdata->pbo = FALSE;
	pdata->sync = FALSE;
	pdata->byte = FALSE;
	pdata->sig = FALSE;
	pdata->glf = FALSE;
	pdata->comp = 50;
	pdata->uncomp = 25;
	pdata->unscaled = 25;

	/* Free string (if not NULL). */
	if( combo_str )
		g_free( combo_str );

	return(0);
}

void edit_profile()
{
	/* get values from combo
	 * and write them in pdata */

	/* initialize objects */
	GtkTreeModel *model;
	GtkTreeIter iter;
	if( ! gtk_combo_box_get_active_iter( GTK_COMBO_BOX( data->combo_profile ), &iter ) )
		return;
	model = gtk_combo_box_get_model( GTK_COMBO_BOX( data->combo_profile ) );
	/* variables */
	gchar *ls0, *ls1, *ls2, *ls3, *ls4;
	gint ls5 = 0;
	gint ls6;
	gdouble ls7;
	gint ls8, ls9, ls10, ls11 = 0;
	gint ls12;
	gboolean ls13;
	gboolean ls14, ls15, ls16, ls18;
	gchar *ls17;
	gboolean ls19, ls20;
	gint ls21;
	gchar *ls22, *ls23;
	gint ls24;
	gboolean ls25, ls26, ls27, ls28, ls29;
	gint ls30, ls31, ls32;

	/* get items from combo */
	gtk_tree_model_get( model, &iter,
						 0, &ls0, 1, &ls1, 2, &ls2, 3, &ls3,
						 4, &ls4, 5, &ls5, 6, &ls6, 7, &ls7,
						 8, &ls8, 9, &ls9, 10, &ls10, 11, &ls11,
						 12, &ls12, 13, &ls13, 14, &ls14, 15, &ls15,
						 16, &ls16, 17, &ls17, 18, &ls18,
						 19, &ls19, 20, &ls20, 21, &ls21, 22, &ls22,
						 23, &ls23, 24, &ls24,
						 25, &ls25, 26, &ls26, 27, &ls27, 28, &ls28,
						 29, &ls29, 30, &ls30, 31, &ls31, 32, &ls32,
						  -1 );

	/* set struct with values */
	pdata->profilename = g_strdup( ls0 );
	pdata->glccapture = g_strdup( ls1 );
	pdata->application = g_strdup( ls2 );
	pdata->outfile = g_strdup( ls3 );
	pdata->logfile = g_strdup( ls4 );
	pdata->loglevel = ls5;
	pdata->fps = ls6;
	pdata->resize = ls7;
	pdata->cropw = ls8;
	pdata->croph = ls9;
	pdata->cropx = ls10;
	pdata->cropy = ls11;
	pdata->colorspace = ls12;
	pdata->lockfps = ls13;
	pdata->disable = ls14;
	pdata->skip = ls15;
	pdata->pulse = ls16;
	pdata->devices = g_strdup( ls17 );
	pdata->sdl = ls18;
	pdata->start = ls19;
	pdata->draw = ls20;
	pdata->capbuf = ls21;
	pdata->hotkey = g_strdup( ls22 );
	pdata->reload = g_strdup( ls23 );
	pdata->compression = ls24;
	pdata->pbo = ls25;
	pdata->sync = ls26;
	pdata->byte = ls27;
	pdata->sig = ls28;
	pdata->glf = ls29;
	pdata->comp = ls30;
	pdata->uncomp = ls31;
	pdata->unscaled = ls32;

	return;
}

void fill_edit()
{
	/* fill edit window
	 * with data from
	 * pdata */

	gtk_label_set_text( GTK_LABEL( data->edit_label ), pdata->profilename );
	gtk_entry_set_text( GTK_ENTRY( data->edit_entry_glc ), pdata->glccapture );
	gtk_entry_set_text( GTK_ENTRY( data->edit_entry_app ), pdata->application );
	gtk_entry_set_text( GTK_ENTRY( data->edit_entry_out ), pdata->outfile );
	gtk_entry_set_text( GTK_ENTRY( data->edit_entry_log ), pdata->logfile );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( data->edit_spin_log ), pdata->loglevel );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( data->video_spin_fps ), pdata->fps );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( data->video_spin_resize ), pdata->resize );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( data->video_spin_crop_w ), pdata->cropw );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( data->video_spin_crop_h ), pdata->croph );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( data->video_spin_crop_x ), pdata->cropx );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( data->video_spin_crop_y ), pdata->cropy );
	if ( pdata->colorspace == 2 )
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->video_radio_420jpeg ), TRUE );
	else
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->video_radio_bgr ), TRUE );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->video_check_lockfps ), pdata->lockfps );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->audio_check_disable ), pdata->disable );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->audio_check_skip ), pdata->skip );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->audio_check_pulse ), pdata->pulse );
	gtk_entry_set_text( GTK_ENTRY( data->audio_entry_devices ), pdata->devices );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->audio_check_sdl ), pdata->sdl );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->common_check_start ), pdata->start );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->common_check_draw ), pdata->draw );
	if ( pdata->capbuf == 1 )
	{
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->common_radio_front ), TRUE );
	} else {
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->common_radio_back ), TRUE );
	}
	gtk_entry_set_text( GTK_ENTRY( data->common_entry_hotkey ), pdata->hotkey );
	gtk_entry_set_text( GTK_ENTRY( data->common_entry_reload ), pdata->reload );
	if ( pdata->compression == 1 )
	{
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->common_radio_none ), TRUE );
	} else if ( pdata->compression == 2 )
	{
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->common_radio_quicklz ), TRUE );
	} else {
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->common_radio_lzo ), TRUE );
	}
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->other_check_pbo ), pdata->pbo );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->other_check_sync ), pdata->sync );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->other_check_byte ), pdata->byte );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->other_check_sig ), pdata->sig );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( data->other_check_glf ), pdata->glf );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( data->other_spin_comp ), pdata->comp );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( data->other_spin_uncomp ), pdata->uncomp );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( data->other_spin_unscaled ), pdata->unscaled );

	return;
}

void recording()
{
	/* create the command line
	 * checking defaults
	 * and save it in the
	 * textview
	 */

	/* fill pdata from combo */
	edit_profile();

	gint mark = 0;
	gchar commandline[1000]; //how much?
	/* create command line */
	if( ! g_strcmp0( pdata->glccapture, "" ) )
		pdata->glccapture = "glc-capture";
	sprintf( commandline, "%s ", pdata->glccapture );
	if( ! g_strcmp0( pdata->outfile, "" ) )
		mark = 1;
	sprintf( commandline, "%s -o %s ", commandline, pdata->outfile );
	if( g_strcmp0( pdata->logfile, "" ) )
		sprintf( commandline, "%s -v %d -l %s ", commandline, pdata->loglevel, pdata->logfile );
	if( pdata->fps != 30 )
		sprintf( commandline, "%s -f %d ", commandline, pdata->fps );
	if( pdata->resize != 1 )
		sprintf( commandline, "%s -r %.2lf ", commandline, pdata->resize );
	if( pdata->cropw != 0 )
		sprintf( commandline, "%s -c %dx%d+%d+%d ", commandline, pdata->cropw, pdata->croph, pdata->cropx, pdata->cropy );
	if( pdata->colorspace == 1 )
		sprintf( commandline, "%s -e %s ", commandline, "bgr" );
	if( pdata->lockfps )
		sprintf( commandline, "%s -n ", commandline );
	if( pdata->disable )
		sprintf( commandline, "%s --disable-audio ", commandline );
	else {
		if( pdata->skip )
			sprintf( commandline, "%s --audio-skip ", commandline );
		if( pdata->pulse )
			sprintf( commandline, "%s -p ", commandline );
		else {
			if( g_strcmp0( pdata->devices, "" ) )
				sprintf( commandline, "%s -a %s ", commandline, pdata->devices );
			if( pdata->sdl )
				sprintf( commandline, "%s -j ", commandline );
		}
	}
	if( pdata->start )
		sprintf( commandline, "%s -s ", commandline );
	if( pdata->draw )
		sprintf( commandline, "%s -i ", commandline );
	if( pdata->capbuf == 2 )
		sprintf( commandline, "%s -b %s ", commandline, "back" );
	if( g_strcmp0( pdata->hotkey, "" ) )
		sprintf( commandline, "%s -k %s ", commandline, pdata->hotkey );
	if( g_strcmp0( pdata->reload, "" ) )
		sprintf( commandline, "%s --reload %s ", commandline, pdata->reload );
	if( pdata->compression == 1 )
		sprintf( commandline, "%s -z %s ", commandline, "none" );
	if( pdata->compression == 3 )
		sprintf( commandline, "%s -z %s ", commandline, "lzo" );
	if( pdata->pbo )
		sprintf( commandline, "%s --pbo ", commandline );
	if( pdata->sync )
		sprintf( commandline, "%s --sync ", commandline );
	if( pdata->byte )
		sprintf( commandline, "%s --byte-aligned ", commandline );
	if( pdata->sig )
		sprintf( commandline, "%s --sighandler ", commandline );
	if( pdata->glf )
		sprintf( commandline, "%s --g ", commandline );
	if( pdata->comp != 50 )
		sprintf( commandline, "%s --compressed=%d ", commandline, pdata->comp );
	if( pdata->uncomp != 25 )
		sprintf( commandline, "%s --uncompressed=%d ", commandline, pdata->uncomp );
	if( pdata->unscaled != 25 )
		sprintf( commandline, "%s --unscaled=%d ", commandline, pdata->unscaled );
	if( ! g_strcmp0( pdata->application, "" ) )
		mark = 2;
	sprintf( commandline, "%s %s ", commandline, pdata->application );

	/* fill textview with command line */
	GtkTextBuffer *buffer;
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW ( data->rec_textview ) );
	if ( mark == 0 )
		gtk_text_buffer_set_text ( buffer, commandline , -1 );
	if ( mark == 1 )
		gtk_text_buffer_set_text ( buffer, "WARNING: you need to fill outfile field" , -1 );
	if ( mark == 2 )
		gtk_text_buffer_set_text ( buffer, "WARNING: you need to fill application field" , -1 );

	return;
}

void playing()
{
	/* play */
	gint i;
	i = system("cat ~/.glc-gui");
	i++; // to avoid warning

	return;
}
