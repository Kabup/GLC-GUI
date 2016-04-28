/*
 * GLC-GUI
 *
 * glc-gui.c
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
 *  Author: Kabup <kabup2@gmail.com>
 *
 */

#include "support.h"
#include "glc-config.h"
#include "callbacks.h"

#define UI_FILE "glc-gui.glade"

int main(int argc, char **argv)
{
	GtkBuilder 	*builder;
	GError		*error = NULL;

	gtk_init( &argc, &argv );

	/* load glade UI file */
	builder = gtk_builder_new();
	if( ! gtk_builder_add_from_file( builder, UI_FILE, &error ) )
	{
		g_warning( "%s", error->message );
		g_free( error );
		return(-1);
	}

	/* Allocate data structure */
	data = g_slice_new( ChData );
	pdata = g_slice_new( PrfData );
	/* Get objects from UI */
	#define GW( name ) CH_GET_WIDGET( builder, name, data )
		GW( main_window );
		GW( combo_profile );
		GW( basic_menu );
		GW( advanced_menu );
		GW( main_button_rec );
		GW( main_button_edit );
		GW( main_button_new );
		GW( main_button_play );
		GW( prof_window );
		GW( text_profile );
		GW( edit_window );
		GW( edit_label );
		GW( edit_entry_glc );
		GW( edit_entry_app );
		GW( edit_entry_out );
		GW( edit_entry_log );
		GW( edit_spin_log );
		GW( video_spin_fps);
		GW( video_spin_resize);
		GW( video_spin_crop_w);
		GW( video_spin_crop_h);
		GW( video_spin_crop_x);
		GW( video_spin_crop_y);
		GW( video_radio_bgr);
		GW( video_radio_420jpeg);
		GW( video_check_lockfps);
		GW( audio_check_disable);
		GW( audio_check_skip);
		GW( audio_check_pulse);
		GW( audio_entry_devices);
		GW( audio_check_sdl);
		GW( common_check_start);
		GW( common_check_draw);
		GW( common_radio_back);
		GW( common_radio_front);
		GW( common_entry_hotkey);
		GW( common_entry_reload);
		GW( common_radio_none);
		GW( common_radio_quicklz);
		GW( common_radio_lzo);
		GW( other_check_pbo);
		GW( other_check_sync);
		GW( other_check_byte);
		GW( other_check_sig);
		GW( other_check_glf);
		GW( other_spin_comp);
		GW( other_spin_uncomp);
		GW( other_spin_unscaled);
		GW( rec_window );
		GW( rec_textview );
		GW( about_window );
		/* basic window */
		GW( basic_window );
		GW( basic_entry_outfile );
		GW( basic_entry_appfile );
		GW( basic_entry_hotkey );
		GW( basic_spin_resize );
		GW( basic_check_draw );
		GW( basic_check_pulse );
		GW( basic_combo_devices );
		GW( basic_check_disable );
		/* play window */
		GW( play_window );
		GW( play_entry_videofile );
		GW( play_check_aoss );
		GW( play_textview );
		GW( play_radio_youtube );
		GW( play_radio_custom );
		GW( play_entry_custom );
		GW( filedialog_window );
	#undef GW

	/* connect signals */
	gtk_builder_connect_signals( builder, data );
	/* free builder */
	g_object_unref( G_OBJECT( builder ) );
	/* show window */
	gtk_widget_show( data->main_window );
	/* main loop */
	gtk_main();
	/* Free any allocated data */
	g_slice_free( ChData, data );
	g_slice_free( PrfData, pdata );
	g_free( error );

	return(0);
}




