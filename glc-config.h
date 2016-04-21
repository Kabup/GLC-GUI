/* http://blog.borovsak.si/2009/09/glade3-tutorial-6-signals.html */

#ifndef __GLC_CONFIG_H__
#define __GLC_CONFIG_H__

/* FUNCTIONS PROTOTYPES */
extern int read_config ();
extern int write_config ();
extern int new_profile();
extern void edit_profile();
extern void fill_edit();
extern void recording();
extern void playing();

#endif /* __GLC_CONFIG_H__ */
