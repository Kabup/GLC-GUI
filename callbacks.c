/*
 * GLC-GUI
 *
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
#include <stdlib.h> // system, exit_success

/* --------------------
* 	Callbacks
*  --------------------
*/

void on_main_window_show()
{
	/* fill combo */
	read_config();

	/* set combo, menu */
	gtk_combo_box_set_active( GTK_COMBO_BOX( data->combo_profile ), 0 );
	gtk_check_menu_item_set_active( GTK_CHECK_MENU_ITEM( data->advanced_menu ), TRUE );
}

void on_main_window_destroy()
{
	/* quit program */
	gtk_main_quit();
}

void on_main_button_edit_clicked()
{
	/* set pdata with config data */
	config_pdata();
	/* show edit window */
	if( gtk_check_menu_item_get_active( GTK_CHECK_MENU_ITEM( data->advanced_menu ) ) == TRUE )
		gtk_widget_show( data->edit_window );
	else
		gtk_widget_show( data->basic_window );
}

void on_main_button_new_clicked()
{
	gtk_widget_show( data->prof_window );
}

void on_main_button_rec_clicked()
{
	gtk_widget_show( data->rec_window );
}

void on_main_button_play_clicked()
{
	/* set pdata with config data */
	config_pdata();

	gtk_widget_show( data->play_window );
}

void on_basic_menu_toggled()
{
	/* toggle menu */
	if( gtk_check_menu_item_get_active( GTK_CHECK_MENU_ITEM( data->basic_menu ) ) == TRUE )
	{
		gtk_check_menu_item_set_active( GTK_CHECK_MENU_ITEM( data->advanced_menu ), FALSE );
	} else {
		gtk_check_menu_item_set_active( GTK_CHECK_MENU_ITEM( data->advanced_menu ), TRUE );
	}
}

void on_advanced_menu_toggled()
{
	/* toggle menu */
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
	/* erase entry */
	gtk_entry_set_text( GTK_ENTRY( data->text_profile ), "" ) ;
	gtk_widget_grab_focus( GTK_WIDGET( data->text_profile ) );
}

void on_prof_window_delete_event()
{
	gtk_widget_hide( data->prof_window );
}

void on_prof_button_cancel_clicked()
{
	on_prof_window_delete_event();
}

void on_prof_button_ok_clicked()
{
	/* create new profile
	 * call basic ou edit window */

	gint i;
	i = new_profile();
	if ( i >= 0 )
	{
		if( gtk_check_menu_item_get_active( GTK_CHECK_MENU_ITEM( data->advanced_menu ) ) == TRUE )
			gtk_widget_show( data->edit_window );
		else
			gtk_widget_show( data->basic_window );
	}

	on_prof_window_delete_event();
}

void on_edit_window_show()
{
	/* reset edit window with pdata */
	pdata_edit();
}

void on_edit_window_delete_event()
{
	gtk_widget_hide( data->edit_window );
}

void on_edit_button_cancel_clicked()
{
	on_edit_window_delete_event();
}

void on_edit_button_ok_clicked()
{
	/* save edit data */
	edit_pdata();
	pdata_config();

	on_edit_window_delete_event();
}

void on_rec_window_delete_event()
{
	gtk_widget_hide( data->rec_window );
}

void on_rec_window_show()
{
	/* set command line */
	recording();
}

void on_rec_button_cancel_clicked()
{
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

void on_basic_button_filedialog_clicked()
{
	//teste
}

void on_play_window_delete_event()
{
	/* save data */
	edit_pdata();
	pdata_config();

	gtk_widget_hide( data->play_window );
}

void on_play_window_show()
{
	/* set data profile */
	pdata_edit();
}

void on_play_button_filechooser_clicked()
{
	/* call filedialog */
	gtk_file_chooser_set_action( GTK_FILE_CHOOSER( data->filedialog_window ), GTK_FILE_CHOOSER_ACTION_OPEN );
	gtk_widget_show( data->filedialog_window );
}

void on_play_button_glcinfo_clicked()
{
	glcinfo();
}

void on_play_button_glcplay_clicked()
{
	glcplay();
}

void on_play_button_encode_clicked()
{
	encoding();
}

void on_filedialog_button_cancel_clicked()
{
	gtk_widget_hide( data->filedialog_window );
}

void on_filedialog_button_ok_clicked()
{
	/* get filename */
	gchar *filename;
	filename = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( data->filedialog_window ) );
	gtk_entry_set_text( GTK_ENTRY( data->play_entry_videofile ), filename );

	gtk_widget_hide( data->filedialog_window );
}



