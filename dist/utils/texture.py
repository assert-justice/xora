from xora_engine import graphics

class Texture:
    def __init__(self, handle: int):
        self.handle = handle
        ext = graphics.get_texture_dimensions(self.handle)
        self.width = float(ext[0])
        self.height = float(ext[1])
        self.sx = 0.0
        self.sy = 0.0
        self.sw = self.width
        self.sh = self.height
        self.ox = 0.0
        self.oy = 0.0
        self.angle = 0.0
    def draw(self, x: float, y: float):
        graphics.draw_texture_ext(self.handle, 
                                  x, 
                                  y, 
                                  self.width, 
                                  self.height, 
                                  self.sx,
                                  self.sy,
                                  self.sw,
                                  self.sh,
                                  self.ox,
                                  self.oy,
                                  self.angle)
    def bind(self):
        graphics.bind_texture(self.handle)