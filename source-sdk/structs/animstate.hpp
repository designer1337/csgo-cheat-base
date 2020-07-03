#pragma once

class anim_state {

private:
	char	u0[ 0x18 ];
public:
	float	anim_update_timer;
private:
	char	u1[ 0xC ];
public:
	float	started_moving_time;
	float	last_move_time;
private:
	char	u2[ 0x10 ];
public:
	float	last_lby_time;
private:
	char	u3[ 0x8 ];
public:
	float	run_amount;
private:
	char	u4[ 0x10 ];
public:
	void	*entity;
	__int32 active_weapon;
	__int32 last_active_weapon;
	float	last_clientside_anim_update_time;
	__int32 last_clientside_anim_update_framecount;
	float	eye_timer;
	float	eye_angles_y;
	float	eye_angles_x;
	float	goal_feet_yaw;
	float	current_feet_yaw;
	float	torso_yaw;
	float	last_move_yaw;
	float	lean_amount;
private:
	char	u5[ 0x4 ];
public:
	float	feet_cycle;
	float	feet_yaw_rate;
private:
	char	u6[ 0x4 ];
public:
	float	duck_amount;
	float	landing_duck_amount;
private:
	char	u7[ 0x4 ];
public:
	vec3_t	current_origin;
	vec3_t	last_origin;
	float	velocity_x;
	float	velocity_y;
private:
	char	u8[ 0x10 ];
public:
	float	move_direction_1;
	float	move_direction_2;
private:
	char	u9[ 0x4 ];
public:
	float	velocity;
	float	jump_fall_velocity; 
	float	clamped_velocity; 
	float	feet_speed_forwards_or_sideways;
	float	feet_speed_unknown_forwards_or_sideways; 
	float	last_time_started_moving;
	float	last_time_stopped_moving;
	bool	on_ground;
	bool	hit_in_ground_anim;
private:
	char	u10[ 0x4 ];
public:
	float	last_origin_z;
	float	head_from_ground_distance_standing;
	float	stop_to_full_running_fraction;
private:
	char	u11[ 0x14 ];
public:
	__int32 is_not_moving;
private:
	char	u12[ 0x20 ];
public:
	float	last_anim_update_time;
	float	moving_direction_x;
	float	moving_direction_y;
	float	moving_direction_z;
private:
	char	u13[ 0x44 ];
public:
	__int32 started_moving;
private:
	char	u14[ 0x8 ];
public:
	float	lean_yaw;
private:
	char	u15[ 0x8 ];
public:
	float	poses_speed;
private:
	char	u16[ 0x8 ];
public:
	float	ladder_speed;
private:
	char	u17[ 0x8 ];
public:
	float	ladder_yaw;
private:
	char	u18[ 0x8 ];
public:
	float	some_pose;
private:
	char	u19[ 0x14 ];
public:
	float	body_yaw;
private:
	char	u20[ 0x8 ];
public:
	float	body_pitch;
private:
	char	u21[ 0x8 ];
public:
	float	death_yaw;
private:
	char	u22[ 0x8 ];
public:
	float	stand;
private:
	char	u23[ 0x8 ];
public:
	float	jump_fall;
private:
	char	u24[ 0x8 ];
public:
	float	aim_blend_stand_idle;
private:
	char	u25[ 0x8 ];
public:
	float	aim_blend_crouch_idle;
private:
	char	u26[ 0x8 ];
public:
	float	strafe_yaw;
private:
	char	u27[ 0x8 ];
public:
	float	aim_blend_stand_walk;
private:
	char	u28[ 0x8 ];
public:
	float	aim_blend_stand_run;
private:
	char	u29[ 0x8 ];
public:
	float	aim_blend_crouch_walk;
private:
	char	u30[ 0x8 ];
public:
	float	move_blend_walk;
private:
	char	u31[ 0x8 ];
public:
	float	move_blend_run;
private:
	char	u32[ 0x8 ];
public:
	float	move_blend_crouch;
private:
	char	u33[ 0x4 ];
public:
	float	speed;
	__int32 moving_in_any_direction;
	float	acceleration;
private:
	char	u34[ 0x74 ];
public:
	float	crouch_height;
	__int32 is_full_crouched;
private:
	char	u35[ 0x4 ];
public:
	float	velocity_subtract_x;
	float	velocity_subtract_y;
	float	velocity_subtract_z;
	float	standing_head_height;
};
