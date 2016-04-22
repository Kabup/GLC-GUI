/* http://blog.borovsak.si/2009/09/glade3-tutorial-6-signals.html */

#ifndef __GLC_CONFIG_H__
#define __GLC_CONFIG_H__

/* FUNCTIONS PROTOTYPES */
extern GKeyFile *open_keyfile( GKeyFile *keyfile );
extern void default_pdata( const gchar *profilename );
extern void pdata_edit();
extern void edit_pdata();
extern void read_config ();
extern void write_config ();
extern int new_profile();
extern void edit_profile();
extern void recording();
extern void playing();

#endif /* __GLC_CONFIG_H__ */
