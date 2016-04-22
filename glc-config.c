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
#include <limits.h> // PATH_MAX

#define CONF_FILE ".glc-gui"

GKeyFile *open_keyfile( GKeyFile *keyfile )
{
	/* open/create config file
	 * load keyfile with data
	 * from config file
	 * exit if fail */

	/* get filename */
	char filename[PATH_MAX];
	if( sprintf( filename, "%s/%s", getenv( "HOME" ), CONF_FILE ) < 0 )
	{
		g_printf( "GLC-GUI ERROR: creating filename - %s\n", filename );
		exit(1);
	}
	/* open/create file */
	FILE *fp;
	fp = fopen( filename, "a"); // open or create file
	if ( fp == NULL )
	{
		g_printf( "GLC-GUI ERROR: creating/opening config file %s\n", filename );
		exit(1);
	}
	fclose(fp);
	/* open config file */
	GKeyFileFlags flags = G_KEY_FILE_NONE;
	if ( g_key_file_load_from_file (keyfile, filename, flags, NULL ) == FALSE )
	{
		g_printf( "GLC-GUI ERROR: opening config file - %s\n", filename );
		exit(1); // error reading the file
	}

	return( keyfile );
}

void default_pdata( const gchar *profilename )
{
	/* fill pdata with default values */
	pdata->profilename = g_strdup( profilename );
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

	return;
}

void pdata_edit()
{
	/* fill edit window
	 * with data from pdata */

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

void edit_pdata()
{
	gint i;
	/* get data from edit window */
	pdata->profilename = g_strdup( gtk_label_get_text( GTK_LABEL( data->edit_label ) ) );
	pdata->glccapture = g_strdup( gtk_entry_get_text( GTK_ENTRY( data->edit_entry_glc ) ) );
	pdata->application = g_strdup( gtk_entry_get_text( GTK_ENTRY( data->edit_entry_app ) ) );
	pdata->outfile = g_strdup( gtk_entry_get_text( GTK_ENTRY( data->edit_entry_out ) ) );
	pdata->logfile = g_strdup( gtk_entry_get_text( GTK_ENTRY( data->edit_entry_log ) ) );
	pdata->loglevel = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->edit_spin_log ) );
	pdata->fps = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_fps ) );
	pdata->resize = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_resize ) );
	pdata->cropw = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_crop_w ) );
	pdata->croph = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_crop_h ) );
	pdata->cropx = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_crop_x ) );
	pdata->cropy = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->video_spin_crop_y ) );
	if( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->video_radio_bgr ) ) )
		{ i = 1; } else { i = 2; }
	pdata->colorspace = i;
	pdata->lockfps = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->video_check_lockfps ) );
	pdata->disable = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->audio_check_disable ) );
	pdata->skip = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->audio_check_skip ) );
	pdata->pulse = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->audio_check_pulse ) );
	pdata->devices = g_strdup( gtk_entry_get_text( GTK_ENTRY( data->audio_entry_devices ) ) );
	pdata->sdl = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->audio_check_sdl ) );
	pdata->start = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->common_check_start ) );
	pdata->draw = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->common_check_draw ) );
	if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->common_radio_front ) ) )
		{ i = 1; } else { i = 2; }
	pdata->capbuf = i;
	pdata->hotkey = g_strdup( gtk_entry_get_text( GTK_ENTRY( data->common_entry_hotkey ) ) );
	pdata->reload = g_strdup( gtk_entry_get_text( GTK_ENTRY( data->common_entry_reload ) ) );
	if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->common_radio_none ) ) )
	{
		i = 1;
	} else if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->common_radio_quicklz ) ) )
	{
		i = 2;
	} else {
		i = 3;
	}
	pdata->compression = i;
	pdata->pbo = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->other_check_pbo ) );
	pdata->sync = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->other_check_sync ) );
	pdata->byte = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->other_check_byte ) );
	pdata->sig = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->other_check_sig ) );
	pdata->glf = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( data->other_check_glf ) );
	pdata->comp = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->other_spin_comp ) );
	pdata->uncomp = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->other_spin_uncomp ) );
	pdata->unscaled = gtk_spin_button_get_value( GTK_SPIN_BUTTON( data->other_spin_unscaled ) );

	return;
}

void read_config()
{
	/* Get group names from config
	 * read data and fill the liststore
	 * set combo with liststore
	 * enable/disable buttons */

	/* get groups list */
	GKeyFile *keyfile = g_key_file_new ();
	keyfile = open_keyfile( keyfile );
	gchar **listgroups = g_key_file_get_groups( keyfile, NULL );
	g_key_file_free( keyfile );

	/* fill combo with names */
	GtkListStore *liststore = gtk_list_store_new( 1, G_TYPE_STRING );
	gchar *groupname;
	gint i;
	gboolean showbuttons = FALSE;
	for (i=0;listgroups[i] != NULL;i++)
	{
		groupname = listgroups[i];
		gtk_list_store_insert_with_values( liststore, NULL, -1,
								0, groupname, -1 );
		showbuttons = TRUE;
	}
	g_strfreev ( listgroups );

	/* set combo with data, point to first row */
	gtk_combo_box_set_model ( GTK_COMBO_BOX( data->combo_profile ), GTK_TREE_MODEL( liststore ) );
	/* release liststore */
	g_object_unref(liststore);

	/* enable/disable buttons */
	if( showbuttons == TRUE )
	{
		gtk_widget_set_sensitive ( data->main_button_rec, TRUE );
		gtk_widget_set_sensitive ( data->main_button_edit, TRUE );
	} else {
		gtk_widget_set_sensitive ( data->main_button_rec, FALSE );
		gtk_widget_set_sensitive ( data->main_button_edit, FALSE );
	}

	return;
}

void write_config ()
{
	/* create/open keyfile
	 * retrieve data from edit window,
	 * loop through config,
	 * save in config file (new or old)
	 */

	edit_pdata();

	/* open config file */
	GKeyFile *keyfile = g_key_file_new ();
	keyfile = open_keyfile( keyfile );

	/* save data in file */
	char *ls0 = pdata->profilename;
	g_key_file_set_string( keyfile, ls0, "glcpath", pdata->glccapture );
	g_key_file_set_string( keyfile, ls0, "application", pdata->application );
	g_key_file_set_string( keyfile, ls0, "outfile", pdata->outfile );
	g_key_file_set_string( keyfile, ls0, "logfile", pdata->logfile );
	g_key_file_set_integer( keyfile, ls0, "loglevel", pdata->loglevel );
	g_key_file_set_integer( keyfile, ls0, "video_fps", pdata->fps );
	g_key_file_set_double( keyfile, ls0, "video_resize", pdata->resize );
	g_key_file_set_integer( keyfile, ls0, "video_crop_w", pdata->cropw );
	g_key_file_set_integer( keyfile, ls0, "video_crop_h", pdata->croph );
	g_key_file_set_integer( keyfile, ls0, "video_crop_x", pdata->cropx );
	g_key_file_set_integer( keyfile, ls0, "video_crop_y", pdata->cropy );
	g_key_file_set_integer( keyfile, ls0, "video_colorspace", pdata->colorspace );
	g_key_file_set_boolean( keyfile, ls0, "video_lockfps", pdata->lockfps );
	g_key_file_set_boolean( keyfile, ls0, "audio_disable", pdata->disable );
	g_key_file_set_boolean( keyfile, ls0, "audio_skip", pdata->skip );
	g_key_file_set_boolean( keyfile, ls0, "audio_pulse", pdata->pulse );
	g_key_file_set_string( keyfile, ls0, "audio_devices", pdata->devices );
	g_key_file_set_boolean( keyfile, ls0, "audio_sdl", pdata->sdl );
	g_key_file_set_boolean( keyfile, ls0, "common_start", pdata->start );
	g_key_file_set_boolean( keyfile, ls0, "common_draw", pdata->draw );
	g_key_file_set_integer( keyfile, ls0, "common_capbuf", pdata->capbuf );
	g_key_file_set_string( keyfile, ls0, "common_hotkey", pdata->hotkey );
	g_key_file_set_string( keyfile, ls0, "common_reload", pdata->reload );
	g_key_file_set_integer( keyfile, ls0, "common_compression", pdata->compression );
	g_key_file_set_boolean( keyfile, ls0, "other_pbo", pdata->pbo );
	g_key_file_set_boolean( keyfile, ls0, "other_sync", pdata->sync );
	g_key_file_set_boolean( keyfile, ls0, "other_byte", pdata->byte );
	g_key_file_set_boolean( keyfile, ls0, "other_sig", pdata->sig );
	g_key_file_set_boolean( keyfile, ls0, "other_glf", pdata->glf );
	g_key_file_set_integer( keyfile, ls0, "other_comp", pdata->comp );
	g_key_file_set_integer( keyfile, ls0, "other_uncomp", pdata->uncomp );
	g_key_file_set_integer( keyfile, ls0, "other_unscaled", pdata->unscaled );

	/* save/close keyfile */
	char filename[PATH_MAX];
	if( sprintf( filename, "%s/%s", getenv( "HOME" ), CONF_FILE ) < 0 )
	{
		g_printf( "GLC-GUI ERROR: creating filename - %s\n", filename );
		exit(1);
	}
	if ( g_key_file_save_to_file( keyfile, filename, NULL ) == FALSE )
	{
		g_printf( "GLC-GUI ERROR: saving in config file - %s\n", filename );
		exit(1);
	}
	g_key_file_free( keyfile );

	/* reset combo box */
	read_config();

	return;
}
int new_profile()
{
	/* check if new profile name
	 * is empty or already exists
	 * if not, fill pdata with defaults */

	/* profile text is empty? */
	const gchar *string;
	string = gtk_entry_get_text( GTK_ENTRY( data->text_profile ) );
	if ( ! string[0] )
		return(-1); // empty

	/* check profile name with groups */
	GKeyFile *keyfile = g_key_file_new ();
	keyfile = open_keyfile( keyfile );
	gchar **listgroups = g_key_file_get_groups( keyfile, NULL );
	g_key_file_free( keyfile );

	gint i;
	for (i=0;listgroups[i] != NULL;i++)
	{
		if( g_strcmp0( listgroups[i], string ) == 0 )
			return(-1); // is the same, exit
	}
	g_strfreev ( listgroups );

	/* fill pdata with default values */
	default_pdata( string );
	return(0);
}

void edit_profile()
{
	/* get values from config
	 * and write them in pdata */

	/* get profile name
	 * selected in combo */
	const gchar *ls0;
	gtk_combo_box_set_id_column( GTK_COMBO_BOX( data->combo_profile ), 0 );
	ls0 = gtk_combo_box_get_active_id( GTK_COMBO_BOX( data->combo_profile ) );

	/* open config file */
	GKeyFile *keyfile = g_key_file_new ();
	keyfile = open_keyfile( keyfile );
	/* read keys from config */
	gchar *ls1 = g_key_file_get_string( keyfile, ls0, "glcpath", NULL );
	gchar *ls2 = g_key_file_get_string( keyfile, ls0, "application", NULL );
	gchar *ls3 = g_key_file_get_string( keyfile, ls0, "outfile", NULL );
	gchar *ls4 = g_key_file_get_string( keyfile, ls0, "logfile", NULL );
	gint ls5 = g_key_file_get_integer( keyfile, ls0, "loglevel", NULL );
	gint ls6 = g_key_file_get_integer( keyfile, ls0, "video_fps", NULL );
	gdouble ls7 = g_key_file_get_double( keyfile, ls0, "video_resize", NULL );
	gint ls8 = g_key_file_get_integer( keyfile, ls0, "video_crop_w", NULL );
	gint ls9 = g_key_file_get_integer( keyfile, ls0, "video_crop_h", NULL );
	gint ls10 = g_key_file_get_integer( keyfile, ls0, "video_crop_x", NULL );
	gint ls11 = g_key_file_get_integer( keyfile, ls0, "video_crop_y", NULL );
	gint ls12 = g_key_file_get_integer( keyfile, ls0, "video_colorspace", NULL );
	gboolean ls13 = g_key_file_get_boolean( keyfile, ls0, "video_lockfps", NULL );
	gboolean ls14 = g_key_file_get_boolean( keyfile, ls0, "audio_disable", NULL );
	gboolean ls15 = g_key_file_get_boolean( keyfile, ls0, "audio_skip", NULL );
	gboolean ls16 = g_key_file_get_boolean( keyfile, ls0, "audio_pulse", NULL );
	gchar *ls17 = g_key_file_get_string( keyfile, ls0, "audio_devices", NULL );
	gboolean ls18 = g_key_file_get_boolean( keyfile, ls0, "audio_sdl", NULL );
	gboolean ls19 = g_key_file_get_boolean( keyfile, ls0, "common_start", NULL );
	gboolean ls20 = g_key_file_get_boolean( keyfile, ls0, "common_draw", NULL );
	gint ls21 = g_key_file_get_integer( keyfile, ls0, "common_capbuf", NULL );
	gchar *ls22 = g_key_file_get_string( keyfile, ls0, "common_hotkey", NULL );
	gchar *ls23 = g_key_file_get_string( keyfile, ls0, "common_reload", NULL );
	gint ls24 = g_key_file_get_integer( keyfile, ls0, "common_compression", NULL );
	gboolean ls25 = g_key_file_get_boolean( keyfile, ls0, "other_pbo", NULL );
	gboolean ls26 = g_key_file_get_boolean( keyfile, ls0, "other_sync", NULL );
	gboolean ls27 = g_key_file_get_boolean( keyfile, ls0, "other_byte", NULL );
	gboolean ls28 = g_key_file_get_boolean( keyfile, ls0, "other_sig", NULL );
	gboolean ls29 = g_key_file_get_boolean( keyfile, ls0, "other_glf", NULL );
	gint ls30 = g_key_file_get_integer( keyfile, ls0, "other_comp", NULL );
	gint ls31 = g_key_file_get_integer( keyfile, ls0, "other_uncomp", NULL );
	gint ls32 = g_key_file_get_integer( keyfile, ls0, "other_unscaled", NULL );
	g_key_file_free( keyfile );

	/* set pdata struct with values */
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

void recording()
{
	/* create the command line
	 * checking defaults
	 * and save it in the
	 * textview
	 */

	/* fill pdata from keyfile */
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
		if( pdata->sdl )
			sprintf( commandline, "%s -j ", commandline );
		if( g_strcmp0( pdata->devices, "" ) )
			sprintf( commandline, "%s -a %s ", commandline, pdata->devices );
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
	edit_profile();
	gchar commandline[1000];
	sprintf( commandline, "%s %s", "glc-play", pdata->outfile );
	system( commandline );

	return;
}
