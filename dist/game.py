from xora_engine import engine, window, input, graphics, xo_math, physics
from xora_engine.input_lookup import Keys
from utils.texture import Texture
from utils.la import Vec2, Vec3
from box import Box
from ent_data import EntData
import math

cube_verts = [
    -0.5, -0.5, -0.5,  0.0, 0.0,
    0.5, -0.5, -0.5,  1.0, 0.0,
    0.5,  0.5, -0.5,  1.0, 1.0,
    0.5,  0.5, -0.5,  1.0, 1.0,
    -0.5,  0.5, -0.5,  0.0, 1.0,
    -0.5, -0.5, -0.5,  0.0, 0.0,

    -0.5, -0.5,  0.5,  0.0, 0.0,
    0.5, -0.5,  0.5,  1.0, 0.0,
    0.5,  0.5,  0.5,  1.0, 1.0,
    0.5,  0.5,  0.5,  1.0, 1.0,
    -0.5,  0.5,  0.5,  0.0, 1.0,
    -0.5, -0.5,  0.5,  0.0, 0.0,

    -0.5,  0.5,  0.5,  1.0, 0.0,
    -0.5,  0.5, -0.5,  1.0, 1.0,
    -0.5, -0.5, -0.5,  0.0, 1.0,
    -0.5, -0.5, -0.5,  0.0, 1.0,
    -0.5, -0.5,  0.5,  0.0, 0.0,
    -0.5,  0.5,  0.5,  1.0, 0.0,

    0.5,  0.5,  0.5,  1.0, 0.0,
    0.5,  0.5, -0.5,  1.0, 1.0,
    0.5, -0.5, -0.5,  0.0, 1.0,
    0.5, -0.5, -0.5,  0.0, 1.0,
    0.5, -0.5,  0.5,  0.0, 0.0,
    0.5,  0.5,  0.5,  1.0, 0.0,

    -0.5, -0.5, -0.5,  0.0, 1.0,
    0.5, -0.5, -0.5,  1.0, 1.0,
    0.5, -0.5,  0.5,  1.0, 0.0,
    0.5, -0.5,  0.5,  1.0, 0.0,
    -0.5, -0.5,  0.5,  0.0, 0.0,
    -0.5, -0.5, -0.5,  0.0, 1.0,

    -0.5,  0.5, -0.5,  0.0, 1.0,
    0.5,  0.5, -0.5,  1.0, 1.0,
    0.5,  0.5,  0.5,  1.0, 0.0,
    0.5,  0.5,  0.5,  1.0, 0.0,
    -0.5,  0.5,  0.5,  0.0, 0.0,
    -0.5,  0.5, -0.5,  0.0, 1.0
]

class Game:
    def __init__(self):
        self.speed = 10
        self.turn_speed = 1
        self.brick_tex = Texture(graphics.new_texture_from_file('./textures/wall.jpg'))
        self.crate_tex = Texture(graphics.new_texture_from_file('./textures/container.jpg'))
        self.common_tex = Texture(graphics.new_texture_from_file('./textures/colormap.png'))
        self.cam_pos = Vec3(0.0, 0.0, -5.0)
        self.cam_angle = Vec2(0.0, 0.0)
        with open('./shaders/ball_vert.glsl', 'r') as f:
            vert_src = f.read()
        with open('./shaders/ball_frag.glsl', 'r') as f:
            frag_src = f.read()
        self.shader_id = graphics.new_shader(vert_src, frag_src)
        self.world_loc = graphics.get_shader_uniform_location(self.shader_id, 'world')
        self.perspective_loc = graphics.get_shader_uniform_location(self.shader_id, 'perspective')
        self.floor_shape_id = physics.add_box_shape(50.0, 50.0, 50.0)
        self.box_shape_id = physics.add_box_shape(0.5, 0.5, 0.5)
        self.sphere_shape_id = physics.add_sphere_shape(0.25)
        cube_verts = [v*100 for v in cube_verts]
        self.big_cube = graphics.new_mesh(cube_verts, [3,2])
        box_ent_data = EntData(self.box_shape_id, 1, self.crate_tex, self.shader_id, self.world_loc)
        sphere_ent_data = EntData(self.sphere_shape_id, 3, self.crate_tex, self.shader_id, self.world_loc)
        floor_ent_data = EntData(self.floor_shape_id, self.big_cube, self.brick_tex, self.shader_id, self.world_loc)
        self.boxes = [
            Box(sphere_ent_data, Vec3(0.0, 0.0, 0.0), 1.0),
            Box(box_ent_data, Vec3(0.0, 1.0, 0.0), 1.0),
            Box(box_ent_data, Vec3(0.0, 2.0, 0.0), 1.0),
            Box(floor_ent_data, Vec3(0.0, 56.0, 0.0), 0.0),
        ]
        # physics.add_impulse(self.boxes[0].handle, 0.0, -10.0, 0.0)
        self.is_jump_down = False

    def update(self, dt: float):
        if input.is_key_down(Keys.escape):
            engine.quit()
        move = Vec3(0.0, 0.0, 0.0)
        if input.is_key_down(Keys.a):
            move.x = 1.0
        if input.is_key_down(Keys.d):
            move.x = -1.0
        # if input.is_key_down(Keys.left_control):
        #     move.y = -1.0
        # if input.is_key_down(Keys.space):
        #     move.y = 1.0
        if input.is_key_down(Keys.s):
            move.z = 1.0
        if input.is_key_down(Keys.w):
            move.z = -1.0
        if input.is_key_down(Keys.left):
            self.cam_angle.x += self.turn_speed * dt
        if input.is_key_down(Keys.right):
            self.cam_angle.x -= self.turn_speed * dt
        if input.is_key_down(Keys.up):
            self.cam_angle.y += self.turn_speed * dt
        if input.is_key_down(Keys.down):
            self.cam_angle.y -= self.turn_speed * dt
        mx = move.x
        mz = move.z
        a = self.cam_angle.x
        move.z = 0.0
        move.x = 0.0
        move.z += mx * math.sin(a)
        move.x += mx * math.cos(a)
        move.z += mz * math.sin(a+math.pi*0.5)
        move.x += mz * math.cos(a+math.pi*0.5)
        # print(a)
        physics.add_force(self.boxes[0].handle, move.x, move.y, move.z)
        next_jump = input.is_key_down(Keys.space)
        if next_jump and not self.is_jump_down:
            physics.add_impulse(self.boxes[0].handle, 0.0, -10.0, 0.0)
        self.is_jump_down = next_jump
        physics.simulate()
    def draw(self):
        graphics.bind_shader(self.shader_id)
        pos = self.cam_pos
        box_pos = self.boxes[0].get_pos()
        xo_math.push_perspective(30.0, 8.0/6.0, 0.01, 100.0)
        xo_math.push_vector3(pos.x, pos.y, pos.z)
        xo_math.translate()
        xo_math.push_vector3(self.cam_angle.y, self.cam_angle.x, 0.0)
        xo_math.rotate_euler()
        xo_math.push_vector3(-box_pos.x, -box_pos.y, -box_pos.z)
        xo_math.translate()
        graphics.set_shader_uniform_mat4x4(self.shader_id, self.perspective_loc)

        for box in self.boxes:
            box.draw()
    def draw_ui(self):
        # self.brick_tex.draw(0.0, 0.0)
        pass
