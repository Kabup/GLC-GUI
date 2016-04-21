/*
 * callbacks.c
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
 *
 * Author Kabup <kabup2@gmail.com>
 *
 */

#include "support.h"
#include "glc-config.h"
#include <glib/gprintf.h>
#include <stdlib.h> // system

/* --------------------
* 	Callbacks
*  --------------------
*/

void on_main_window_show()
{
	/* fill combobox */
	if( read_config() )
		g_printf( "Error opening config file\n");
}

void on_main_window_destroy()
{
	/* quit application */
	gtk_main_quit();
}

void on_main_button_edit_clicked()
{
	/* set pdata with combo data */
	edit_profile();
	/* call edit window */
	gtk_widget_show( data->edit_window );
}

void on_main_button_new_clicked()
{
	/* show profile window */
	gtk_widget_show( data->prof_window );
}

void on_main_button_rec_clicked()
{
	/* show profile window */
	gtk_widget_show( data->rec_window );
}

void on_main_button_play_clicked()
{
	/* play video */
	playing();
}

void on_prof_window_show()
{
	/* erase old text */
	gtk_entry_set_text( GTK_ENTRY( data->text_profile ), "" ) ;
	gtk_widget_grab_focus( GTK_WIDGET( data->text_profile ) );
}

void on_prof_window_delete_event()
{
	/* hide profile window */
	gtk_widget_hide( data->prof_window );
}

void on_prof_button_cancel_clicked()
{
	/* cancel, do nothing */
	on_prof_window_delete_event();
}

void on_prof_button_ok_clicked()
{
	/* set pdata with combo data */
	if ( ! new_profile() )
	{
		/* show edit window */
		gtk_widget_show( data->edit_window );
	}
	/* close profile window */
	on_prof_window_delete_event();
}

void on_edit_window_show()
{
	fill_edit();
}

void on_edit_window_delete_event()
{
	/* hide window */
	gtk_widget_hide( data->edit_window );
}

void on_edit_button_cancel_clicked()
{
	/* cancel, do nothing */
	on_edit_window_delete_event();
}

void on_edit_button_ok_clicked()
{
	/* save edit fields */
	if( write_config() == -1 )
		g_warning( "Error writing config file.\n" );
	/* close edit window */
	on_edit_window_delete_event();
}

void on_rec_window_delete_event()
{
	/* hide window */
	gtk_widget_hide( data->rec_window );
}

void on_rec_window_show()
{
	/* set textview */
	recording();
}

void on_rec_button_cancel_clicked()
{
	/* hide window */
	on_rec_window_delete_event();
}

void on_rec_button_record_clicked()
{
	/* start recording */
	gchar *text;
	GtkTextBuffer *buffer;
	GtkTextIter start, end;
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (data->rec_textview) );
	gtk_text_buffer_get_start_iter (buffer, &start);
	gtk_text_buffer_get_end_iter (buffer, &end);
	text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

	//g_printf( "%s\n", text );
	system(text);
	on_rec_window_delete_event();
}


