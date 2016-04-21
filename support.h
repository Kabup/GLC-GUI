/* http://blog.borovsak.si/2009/09/glade3-tutorial-6-signals.html */

#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <gtk/gtk.h>
#include <glib/gprintf.h> /* g_printf */

/* Convenience macros for obtaining objects from UI file */
#define CH_GET_OBJECT( builder, name, type, data ) \
	data->name = type( gtk_builder_get_object( builder, #name ) )
#define CH_GET_WIDGET( builder, name, data ) \
	CH_GET_OBJECT( builder, name, GTK_WIDGET, data )

/* Main data structure definition */
typedef struct _ChData ChData;
struct _ChData
{
	/* Widgets */
	GtkWidget *main_window;  	/* Main application window */
	GtkWidget *combo_profile;   /* profile combobox */
	GtkWidget *main_button_rec;
	GtkWidget *main_button_edit;
	GtkWidget *main_button_new;
	GtkWidget *main_button_play;
	GtkWidget *prof_window;
	GtkWidget *text_profile;
	/* edit window */
	GtkWidget *edit_window;
	GtkWidget *edit_label;
	GtkWidget *edit_entry_glc;
	GtkWidget *edit_entry_app;
	GtkWidget *edit_entry_out;
	GtkWidget *edit_entry_log;
	GtkWidget *edit_spin_log;
	/* video */
	GtkWidget *video_spin_fps;
	GtkWidget *video_spin_resize;
	GtkWidget *video_spin_crop_w;
	GtkWidget *video_spin_crop_h;
	GtkWidget *video_spin_crop_x;
	GtkWidget *video_spin_crop_y;
	GtkWidget *video_radio_bgr;
	GtkWidget *video_radio_420jpeg;
	GtkWidget *video_check_lockfps;
	/* audio */
	GtkWidget *audio_check_disable;
	GtkWidget *audio_check_skip;
	GtkWidget *audio_check_pulse;
	GtkWidget *audio_entry_devices;
	GtkWidget *audio_check_sdl;
	/* common */
	GtkWidget *common_check_start;
	GtkWidget *common_check_draw;
	GtkWidget *common_radio_front;
	GtkWidget *common_radio_back;
	GtkWidget *common_entry_hotkey;
	GtkWidget *common_entry_reload;
	GtkWidget *common_radio_none;
	GtkWidget *common_radio_quicklz;
	GtkWidget *common_radio_lzo;
	/* other */
	GtkWidget *other_check_pbo;
	GtkWidget *other_check_sync;
	GtkWidget *other_check_byte;
	GtkWidget *other_check_sig;
	GtkWidget *other_check_glf;
	GtkWidget *other_spin_comp;
	GtkWidget *other_spin_uncomp;
	GtkWidget *other_spin_unscaled;
	/* rec */
	GtkWidget *rec_window;
	GtkWidget *rec_textview;
};

extern ChData *data;
ChData     	*data;

/* Data from current profile  */
typedef struct _PrfData PrfData;
struct _PrfData
{
	/* Data */
	gchar *profilename;
	gchar *glccapture;
	gchar *application;
	gchar *outfile;
	gchar *logfile;
	gint loglevel;
	gint fps;
	gdouble resize;
	gint cropw, croph, cropx, cropy;
	gint colorspace;
	gboolean lockfps;
	gboolean disable, skip, pulse, sdl;
	gchar *devices;
	gboolean start, draw;
	gint capbuf, compression;
	gchar *hotkey, *reload;
	gboolean pbo, sync, byte, sig, glf;
	gint comp, uncomp, unscaled;
};

extern PrfData *pdata;
PrfData		*pdata;

#endif /* __SUPPORT_H__ */
