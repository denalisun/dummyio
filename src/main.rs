mod game;

use raylib::prelude::*;
use crate::game::{player::Player};

fn main() {
    let (mut rl, thread) = raylib::init()
        .size(800, 600)
        .title("Dummy.io")
        .build();

    let mut plr: Player = Player::new(
        Vector2::new(100_f32, 100_f32),
        0_f32,
        100_f32,
        100_f32,
        250);

    while !rl.window_should_close() {
        let mut d: RaylibDrawHandle<'_> = rl.begin_drawing(&thread);
        
        plr.update(&mut d);
        
        d.clear_background(Color::BLACK);
        d.draw_fps(10, 10);

        plr.render(&mut d);
    }
}