#pragma once

class weapon_info_t {

private:
	char		u0[0x4];
public:
	char		*weapon_name;
private:
	char		u1[0xC];
public:
	__int32		weapon_max_clip;
private:
	char		u2[0xC];
public:
	__int32		weapon_max_reserved_ammo;
private:
	char		u3[0x4];
public:
	char		*weapon_model_path;
	char		*weapon_model_path_alt;
	char		*weapon_dropped_model_path;
	char		*weapon_default_clip;
private:
	char		u4[0x44];
public:
	char		*weapon_bullet_type;
private:
	char		u5[0x4];
public:
	char		*weapon_hud_name;
	char		*weapon_name_alt;
private:
	char		u6[0x38];
public:
	__int32		weapon_type;
	__int32		weapon_type_alt;
	__int32		weapon_price;
	__int32		weapon_reward;
	char		*weapon_type_name;
	float		weapon_unknown_float;
private:
	char		u7[0xC];
public:
	unsigned char	weapon_full_auto;
private:
	char		u8[ 0x3 ];
public:
	__int32		weapon_damage;
	float		weapon_armor_ratio;
	__int32		weapon_bullets;
	float		weapon_penetration;
private:
	char		u9[0x8];
public:
	float		weapon_range;
	float		weapon_range_mod;
	float		weapon_throw_velocity;
private:
	char		u10[0xC];
public:
	unsigned char	weapon_has_silencer;
private:
	char		u11[0xF];
public:
	float		weapon_max_speed;
	float		weapon_max_speed_alt;
	float		weapon_attack_move_factor;
	float		weapon_spread;
	float		weapon_spread_alt;
	float		weapon_inaccuracy_crouch;
	float		weapon_inaccuracy_crouch_alt;
	float		weapon_inaccuracy_stand;
	float		weapon_inaccuracy_stand_alt;
	float		weapon_inaccuracy_jump;
	float		weapon_inaccuracy_jump_alt;
private:
	char		u12[0x28];
public:
	__int32		weapon_recoil_seed;
private:
	char		u13[0x68];
public:
	char		*weapon_traces_type;
};
