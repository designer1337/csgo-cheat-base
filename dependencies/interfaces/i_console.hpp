#pragma once
#include "../../source-sdk/classes/convar.hpp"
#include "../../source-sdk/misc/color.hpp"
#include "i_app_system.hpp"

class i_console;
class convar;
class con_command;
class con_command_base;

typedef int cvar_dll_indentifier_t;

class i_console_display_func {
public:
	virtual void color_print( const uint8_t *clr, const char *msg ) = 0;
	virtual void print( const char *msg ) = 0;
	virtual void drint( const char *msg ) = 0;
};

class i_console : public i_app_system {
public:
	virtual cvar_dll_indentifier_t	allocate_dll_indentifier() = 0;
	virtual void			register_con_command( con_command_base *base ) = 0;
	virtual void			unregister_con_command( con_command_base *base ) = 0;
	virtual void			unregister_con_commands( cvar_dll_indentifier_t id ) = 0;
	virtual const char		*get_command_line_value( const char *name ) = 0;
	virtual con_command_base	*find_command_base( const char *name ) = 0;
	virtual const con_command_base	*find_command_base( const char *name ) const = 0;
	virtual convar			*get_convar( const char *var_name ) = 0;
	virtual const convar		*get_convar( const char *var_name ) const = 0;
	virtual con_command		*find_command( const char *name ) = 0;
	virtual const con_command	*find_command( const char *name ) const = 0;
	virtual void			install_global_change_callback( fn_change_callback_t callback ) = 0;
	virtual void			remove_global_change_callback( fn_change_callback_t callback ) = 0;
	virtual void			call_global_change_callbacks( convar *var, const char *old_str, float old_val ) = 0;
	virtual void			install_console_display_func( i_console_display_func *func ) = 0;
	virtual void			remove_console_display_func( i_console_display_func *func ) = 0;
	virtual void			console_color_printf( const color &clr, const char *format, ... ) const = 0;
	virtual void			console_printf( const char *format, ... ) const = 0;
	virtual void			dconsole_dprintf( const char *format, ... ) const = 0;
	virtual void			rever_flagged_convars( int flag ) = 0;
};
