
int entry(int argc, char **argv) {


	window.title  = STR("Le Game");
	window.width  = 960;
	window.height = 720;

	window.clear_color = hex_to_rgba(0x02a2d3aff);
	
	Gfx_Image *player = load_image_from_disk(fixed_string("player.png"), get_heap_allocator());
	assert(player, "ERROR: player is not found!");

	// Player movement.
	Vector2 player_input    = v2(0, 0);
	Vector2 player_position = v2(0, 0);

	// Time keeping.
	float64 last_time   = os_get_elapsed_seconds();
	float64 now         = 0.0f;
	float64 delta_t     = 0.0f;
	float64 sec_counter = 0.0f;

	int frame_count = 0;

	// Bullet ?
	Vector2 bullet_position  = v2(.0f, .0f);
	bool shoot_bullet        = false;

	while (!window.should_close) {
		reset_temporary_storage();

		now = os_get_elapsed_seconds();
		delta_t = now - last_time;
		
		os_update();

		if (is_key_just_pressed(KEY_ESCAPE)) {
			window.should_close = true;
		}
		
		player_input = v2(0, 0);
		if (is_key_down('A')) {
			player_input.x -= 1.0f;
		}
		if (is_key_down('D')) {
			player_input.x += 1.0f;
		}
		if (is_key_down('S')) {
			player_input.y -= 1.0f;
		}
		if (is_key_down('W')) {
			player_input.y += 1.0f;
		}
		if (is_key_down(KEY_SPACEBAR)) {
			shoot_bullet = true;
			bullet_position.x = player_position.x;
			bullet_position.y = player_position.y;
		}

		player_input = v2_normalize(player_input);

		player_position = v2_add(player_position, 
		v2_mulf(player_input, 0.08f * delta_t));

		Matrix4 xform = m4_scalar(1.0);
		xform         = m4_translate(xform, v3(
			player_position.x, player_position.y, 0));

		draw_image_xform(player, xform, v2(250, 250), COLOR_BLUE);

		if (shoot_bullet) {
			Matrix4 bullet_form = m4_scalar(1.0f);
			bullet_form         = m4_translate(
				bullet_form, v3(bullet_position.x + 113, bullet_position.y + 125, 0));

			draw_rect_xform(bullet_form, v2(15, 50), COLOR_GREEN);

			bullet_position.y += (f32) (0.08f * delta_t);
		}
		 
		gfx_update();
	}

	return 0;
}