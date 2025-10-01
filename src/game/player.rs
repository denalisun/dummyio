use raylib::prelude::*;

#[allow(dead_code)] // this is very very temporary
pub struct Player {
    pub position: Vector2,
    pub rotation: f32,
    pub move_speed: f32,
    pub health: f32,
    pub max_health: f32,
    pub money: u32,
}

impl Player {
    pub fn new(position: Vector2, rotation: f32, health: f32, max_health: f32, money: u32) -> Self {
        Self { position, rotation, move_speed: 100.0, health, max_health, money }
    }

    pub fn update(&mut self, d: &mut RaylibDrawHandle<'_>) {
        // Player movement
        self.position.x += (d.is_key_down(KeyboardKey::KEY_D) as i32 - d.is_key_down(KeyboardKey::KEY_A) as i32) as f32 * (d.get_frame_time() * self.move_speed);
        self.position.y += (d.is_key_down(KeyboardKey::KEY_S) as i32 - d.is_key_down(KeyboardKey::KEY_W) as i32) as f32 * (d.get_frame_time() * self.move_speed);
    }

    pub fn render(&self, d: &mut RaylibDrawHandle<'_>) {
        d.draw_circle(self.position.x as i32, self.position.y as i32, 5_f32, Color::TAN);
    }
}