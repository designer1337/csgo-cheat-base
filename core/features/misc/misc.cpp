#include "../features.hpp"

void misc::movement::bunny_hop(c_usercmd* cmd) {
	if (!variables::test_bool)
		return;

	static bool last_jumped = false, should_fake = false;

	if (!last_jumped && should_fake) {
		should_fake = false;
		cmd->buttons |= in_jump;
	}
	else if (cmd->buttons & in_jump) {
		if (csgo::local_player->flags() & fl_onground) {
			last_jumped = true;
			should_fake = true;
		}
		else {
			cmd->buttons &= ~in_jump;
			last_jumped = false;
		}
	}
	else {
		last_jumped = false;
		should_fake = false;
	}
};
