#pragma once
#include "../../source-sdk/classes/c_usercmd.hpp"

class i_input {
public:
	char pad_0000[172]; //0x0000
	bool N0000004E; //0x00AC
	bool m_fCameraInThirdPerson; //0x00AD
	char pad_00AE[2]; //0x00AE
	vec3_t m_vecCameraOffset; //0x00B0

	c_usercmd* get_user_cmd(int slot, int sequence_num) {
		using original_fn = c_usercmd * (__thiscall*)(void*, int, int);
		return (*(original_fn * *)this)[8](this, slot, sequence_num);
	}
};