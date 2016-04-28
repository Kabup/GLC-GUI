/* http://blog.borovsak.si/2009/09/glade3-tutorial-6-signals.html */

#ifndef __GLC_CONFIG_H__
#define __GLC_CONFIG_H__

/* FUNCTIONS PROTOTYPES */
extern int file_exists(const gchar *filename );
extern void write_textview( GtkWidget *textview, const gchar *message );
extern GKeyFile *open_keyfile( GKeyFile *keyfile );
extern void default_pdata( const gchar *profilename );
extern void pdata_edit();
extern void pdata_config();
extern void pdata_basic();
extern void basic_pdata();
extern int config_combo();
extern void config_pdata();
extern void edit_pdata();
extern int new_profile();
extern void recording();
extern void glcinfo();
extern void glcplay();
extern void encoding();
extern void encode_mencoder();
extern int get_pa_sources();

#endif /* __GLC_CONFIG_H__ */
