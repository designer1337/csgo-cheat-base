#pragma once
#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1
#define MAX_FLOWS		2
#include "../../dependencies/interfaces/i_game_event_manager.hpp"
class INetChannelInfo
{
public:
	enum
	{
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		TEMPENTS,		// temp entities
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		PAINTMAP,		// paintmap data
		ENCRYPTED,		// encrypted data
		TOTAL,			// must be last and is not a real group
	};
};

class i_net_channel {
private:
	uint8_t u0[0x17];
public:
	bool should_delete;
	int out_sequence_nr;
	int in_sequence_nr;
	int out_sequence_nr_ack;
	int out_reliable_state;
	int in_reliable_state;
	int choked_packets;

	int	SendDatagram(bf_write* pDatagram)
	{
		using original_fn = int(__thiscall*)(i_net_channel*, bf_write*);
		return (*(original_fn**)this)[46](this, pDatagram);
	}

	bool Transmit(bool bOnlyReliable = false)
	{
		using original_fn = bool(__thiscall*)(i_net_channel*, bool);
		return (*(original_fn**)this)[49](this, bOnlyReliable);
	}
};

class i_net_message
{
public:
	virtual					~i_net_message() { }
	virtual void			set_net_channel(void* pNetChannel) = 0;
	virtual void			set_reliable(bool bState) = 0;
	virtual bool			process() = 0;
	virtual	bool			read_from_buffer(bf_read& buffer) = 0;
	virtual	bool			write_to_buffer(bf_write& buffer) = 0;
	virtual bool			is_reliable() const = 0;
	virtual int				get_type() const = 0;
	virtual int				get_group() const = 0;
	virtual const char* get_name() const = 0;
	virtual i_net_channel* get_net_channel() const = 0;
	virtual const char* to_string() const = 0;
	virtual std::size_t		get_size() const = 0;
};

