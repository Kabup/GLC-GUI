/* http://blog.borovsak.si/2009/09/glade3-tutorial-6-signals.html */

#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__

/* FUNCTIONS PROTOTYPES */

extern void on_main_window_show();
extern void on_main_window_destroy();
extern void on_main_button_edit_clicked();
extern void on_main_button_new_clicked ();
extern void on_main_button_rec_clicked();
extern void on_main_button_play_clicked();
extern void on_basic_menu_toggled();
extern void on_advanced_menu_toggled();
extern void on_about_menu_activate();
extern void on_prof_window_show();
extern void on_prof_window_delete_event();
extern void on_prof_button_cancel_clicked();
extern void on_prof_button_ok_clicked();
extern void on_edit_window_show();
extern void on_edit_window_delete_event();
extern void on_edit_button_cancel_clicked();
extern void on_edit_button_ok_clicked();
extern void on_rec_window_show();
extern void on_rec_window_delete_event();
extern void on_rec_button_cancel_clicked();
extern void on_rec_button_record_clicked();
extern void on_about_window_show();
extern void on_about_window_delete_event();
extern void on_eventbox1_button_press_event();
extern void on_basic_window_delete_event();
extern void on_basic_window_show();

#endif /* __CALLBACKS__ */
