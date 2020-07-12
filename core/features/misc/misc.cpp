#include "../features.hpp"

namespace misc {
void on_create_move() {
	movement::bunny_hop();
}
namespace movement {
void bunny_hop() {
	if (!variables::test_bool)
		return;

	const int move_type = csgo::local_player->move_type();

	if (move_type == movetype_ladder || move_type == movetype_noclip || move_type == movetype_observer)
		return;

	if (!(csgo::local_player->flags() & fl_onground))
		csgo::cmd->buttons &= ~in_jump;
};
} // namespace movement
} // namespace misc
