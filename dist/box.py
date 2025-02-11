from xora_engine import physics, graphics
from utils.la import Vec3

class Box:
    def __init__(self, shape_id: int, shader_id: int, world_loc: int, origin: Vec3, mass: float):
        self.shader_id = shader_id
        self.world_loc = world_loc
        self.handle = physics.add_rigid_body(shape_id, origin.x, origin.y, origin.z, mass)
    def draw(self):
        physics.push_body_transform(self.handle)
        graphics.set_shader_uniform_mat4x4(self.shader_id, self.world_loc)
        graphics.draw_mesh(1)