from xora_engine import physics, graphics
from utils.la import Vec3
from ent_data import EntData

class Box:
    def __init__(self, ent_data: EntData, origin: Vec3, mass: float):
        self.ent_data = ent_data
        self.handle = physics.add_rigid_body(ent_data.shape_id, origin.x, origin.y, origin.z, mass)
    def draw(self):
        self.ent_data.texture.bind()
        physics.push_body_transform(self.handle)
        graphics.set_shader_uniform_mat4x4(self.ent_data.shader_id, self.ent_data.world_loc)
        graphics.draw_mesh(self.ent_data.mesh_id)