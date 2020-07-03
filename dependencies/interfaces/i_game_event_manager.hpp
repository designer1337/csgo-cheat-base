#pragma once

#include <cstdint>

#define EVENT_DEBUG_ID_INIT 42
#define EVENT_DEBUG_ID_SHUTDOWN 13

class bf_write;
class bf_read;

class i_game_event {
public:
	virtual					~i_game_event() = 0;
	virtual const char		*get_name() const = 0;

	virtual bool            is_reliable() const = 0;
	virtual bool            is_local() const = 0;
	virtual bool            is_empty( const char *name = nullptr ) = 0;

	virtual bool            get_bool( const char *name = nullptr, bool def = false ) = 0;
	virtual int             get_int( const char *name = nullptr, int def = 0 ) = 0;
	virtual uint64_t        get_uint_64( const char *name = nullptr, unsigned long def = 0 ) = 0;
	virtual float           get_float( const char *name = nullptr, float def = 0.0f ) = 0;
	virtual const char		*get_string( const char *name = nullptr, const char *def = "" ) = 0;
	virtual const wchar_t	*get_wstring( const char *name, const wchar_t *def = L"" ) = 0;

	virtual void            set_bool( const char *name, bool value ) = 0;
	virtual void            set_int( const char *name, int value ) = 0;
	virtual void            set_uint_64( const char *name, unsigned long value ) = 0;
	virtual void            set_float( const char *name, float value ) = 0;
	virtual void            set_string( const char *name, const char *value ) = 0;
	virtual void            set_wstring( const char *name, const wchar_t *value ) = 0;
};

class i_game_event_listener2 {
public:
	virtual ~i_game_event_listener2( void ) {}

	virtual void fire_game_event( i_game_event *event ) = 0;
	int debug_id;
	virtual int  get_event_debug_id( void ) { return debug_id; };
};

class i_game_event_manager2 {
public:
	virtual             ~i_game_event_manager2() = 0;
	virtual int         load_events_from_file( const char *filename ) = 0;
	virtual void        reset() = 0;
	virtual bool        add_listener( i_game_event_listener2 *listener, const char *name, bool serverside ) = 0;
	virtual bool        find_listener( i_game_event_listener2 *listener, const char *name ) = 0;
	virtual int         remove_listener( i_game_event_listener2 *listener ) = 0;
	virtual i_game_event *CreateEvent( const char *name, bool force, unsigned int unk ) = 0;
	virtual bool        fire_event( i_game_event *event, bool dont_broadcast = false ) = 0;
	virtual bool        fire_event_client_side( i_game_event *event ) = 0;
	virtual i_game_event *duplicate_event( i_game_event *event ) = 0;
	virtual void        free_event( i_game_event *event ) = 0;
	virtual bool        serialize_event( i_game_event *event, bf_write *buf ) = 0;
	virtual i_game_event *unserialize_event( bf_read *buf ) = 0;
};
