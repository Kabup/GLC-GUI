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
#include <stdlib.h> // system, exit_success

/* --------------------
* 	Callbacks
*  --------------------
*/

void on_main_window_show()
{
	/* fill combobox */
	read_config();
	gtk_combo_box_set_active( GTK_COMBO_BOX( data->combo_profile ), 0 );
	gtk_check_menu_item_set_active( GTK_CHECK_MENU_ITEM( data->advanced_menu ), TRUE );
}

void on_main_window_destroy()
{
	/* quit application */
	gtk_main_quit();
}

void on_main_button_edit_clicked()
{
	active_profile = gtk_combo_box_get_active( GTK_COMBO_BOX( data->combo_profile ) );

	/* set pdata with config data */
	edit_profile();

	if( gtk_check_menu_item_get_active( GTK_CHECK_MENU_ITEM( data->advanced_menu ) ) == TRUE )
		gtk_widget_show( data->edit_window );
	else
		gtk_widget_show( data->basic_window );
}

void on_main_button_new_clicked()
{
	/* show profile window */
	active_profile = gtk_combo_box_get_active( GTK_COMBO_BOX( data->combo_profile ) );
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

void on_basic_menu_toggled()
{
	if( gtk_check_menu_item_get_active( GTK_CHECK_MENU_ITEM( data->basic_menu ) ) == TRUE )
	{
		gtk_check_menu_item_set_active( GTK_CHECK_MENU_ITEM( data->advanced_menu ), FALSE );
	} else {
		gtk_check_menu_item_set_active( GTK_CHECK_MENU_ITEM( data->advanced_menu ), TRUE );
	}
}

void on_advanced_menu_toggled()
{
	if( gtk_check_menu_item_get_active( GTK_CHECK_MENU_ITEM( data->advanced_menu ) ) == TRUE )
	{
		gtk_check_menu_item_set_active( GTK_CHECK_MENU_ITEM( data->basic_menu ), FALSE );
	} else {
		gtk_check_menu_item_set_active( GTK_CHECK_MENU_ITEM( data->basic_menu ), TRUE );
	}
}

void on_about_menu_activate()
{
	gtk_widget_show( data->about_window );
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
	/* set pdata with defaults */
	if ( new_profile() == 0 )
	{
		active_profile++;
		gtk_widget_show( data->edit_window );
	}

	on_prof_window_delete_event();
}

void on_edit_window_show()
{
	pdata_edit();
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
	write_config();
	gtk_combo_box_set_active( GTK_COMBO_BOX( data->combo_profile ), active_profile );

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

void on_about_window_delete_event()
{
	/* hide window */
	gtk_widget_hide( data->about_window );
}

void on_about_window_show()
{
	//nothing
}

void on_eventbox1_button_press_event()
{
	gtk_widget_hide( data->about_window );
}

void on_basic_window_delete_event()
{
	gtk_widget_hide( data->basic_window );
}

void on_basic_window_show()
{
	gtk_widget_show( data->basic_window );
}

