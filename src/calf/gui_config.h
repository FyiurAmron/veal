#ifndef CALF_GUI_CONFIG_H
#define CALF_GUI_CONFIG_H

#include <gtk/gtk.h>
#include <glib.h>
#include <gconf/gconf-client.h>
#include <string>

struct gui_config_db_iface
{
    virtual bool has_key(const char *key) = 0;
    virtual bool get_bool(const char *key, bool def_value) = 0;
    virtual int get_int(const char *key, int def_value) = 0;
    virtual std::string get_string(const char *key, const std::string &def_value) = 0;
    virtual void set_bool(const char *key, bool value) = 0;
    virtual void set_int(const char *key, int value) = 0;
    virtual void set_string(const char *key, const std::string &value) = 0;
    virtual ~gui_config_db_iface() {}
};

class gconf_config_db: public gui_config_db_iface
{
protected:
    GConfClient *client;
    std::string prefix;
    void handle_error(GError *error);
public:
    gconf_config_db(const char *parent_key);
    virtual bool has_key(const char *key);
    virtual bool get_bool(const char *key, bool def_value);
    virtual int get_int(const char *key, int def_value);
    virtual std::string get_string(const char *key, const std::string &def_value);
    virtual void set_bool(const char *key, bool value);
    virtual void set_int(const char *key, int value);
    virtual void set_string(const char *key, const std::string &value);
    virtual ~gconf_config_db();
    
};

struct gui_config
{
    int cols, rows;
    bool rack_ears;
    
    gui_config();
    ~gui_config();
    void load(gui_config_db_iface *db);
    void save(gui_config_db_iface *db);
};

#endif