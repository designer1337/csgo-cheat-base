#pragma once

enum cmd_buttons {
	in_attack = (1 << 0),
	in_jump = (1 << 1),
	in_duck = (1 << 2),
	in_forward = (1 << 3),
	in_back = (1 << 4),
	in_use = (1 << 5),
	in_cancel = (1 << 6),
	in_left = (1 << 7),
	in_right = (1 << 8),
	in_moveleft = (1 << 9),
	in_moveright = (1 << 10),
	in_attack2 = (1 << 11),
	in_run = (1 << 12),
	in_reload = (1 << 13),
	in_alt1 = (1 << 14),
	in_alt2 = (1 << 15),
	in_score = (1 << 16),
	in_speed = (1 << 17),
	in_walk = (1 << 18),
	in_zoom = (1 << 19),
	in_weapon1 = (1 << 20),
	in_weapon2 = (1 << 21),
	in_bullrush = (1 << 22),
	in_grenade1 = (1 << 23),
	in_grenade2 = (1 << 24),
	in_attack3 = (1 << 25)
};

typedef unsigned long CRC32_t;

void      CRC32_Init(CRC32_t * pulCRC);
void      CRC32_ProcessBuffer(CRC32_t * pulCRC, const void* p, int len);
void      CRC32_Final(CRC32_t * pulCRC);
CRC32_t	  CRC32_GetTableEntry(unsigned int slot);

inline CRC32_t CRC32_ProcessSingleBuffer(const void* p, int len)
{
	CRC32_t crc;

	CRC32_Init(&crc);
	CRC32_ProcessBuffer(&crc, p, len);
	CRC32_Final(&crc);

	return crc;
}

class c_usercmd {
public:
	virtual ~c_usercmd() {};

	CRC32_t GetChecksum(void) const
	{
		CRC32_t crc;
		CRC32_Init(&crc);

		CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
		CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
		CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
		CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
		CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
		CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
		CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
		CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
		CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
		CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
		CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
		CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
		CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
		CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));

		CRC32_Final(&crc);
		return crc;
	}

	int       command_number;     // For matching server and client commands for debugging
	int       tick_count;         // The tick the client created this command
	vec3_t    viewangles;         // Player instantaneous view angles.
	vec3_t    aimdirection;       //
	float     forwardmove;        // Forward velocity
	float     sidemove;           // Sideways velocity
	float     upmove;             // Upward velocity
	int       buttons;            // Attack button states
	byte      impulse;            // Impulse command issued.
	int       weaponselect;       // Current weapon id
	int       weaponsubtype;      //
	int       random_seed;        // For shared random functions
	short     mousedx;            // Mouse accum in x from create move
	short     mousedy;            // Mouse accum in y from create move
	bool      hasbeenpredicted;   // Client only, tracks whether we've predicted this command at least once
	char      pad_0x4C[0x18];
};