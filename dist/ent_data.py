from utils.texture import Texture

class EntData:
    def __init__(self, shape_id: int, mesh_id: int, texture: Texture, shader_id: int, world_loc: int):
        self.shape_id = shape_id
        self.mesh_id = mesh_id
        self.texture = texture
        self.shader_id = shader_id
        self.world_loc = world_loc
        