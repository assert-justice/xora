class Vec2:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y
    def __add__(self, v):
        return Vec3(self.x + v.x, self.y + v.y)
    def __sub__(self, v):
        return Vec3(self.x - v.x, self.y - v.y)
    def __mul__(self, s: float):
        return Vec3(self.x * s, self.y * s)
    def __str__(self):
        return f'(x: {self.x}, y: {self.y})'

class Vec3:
    def __init__(self, x: float, y: float, z: float):
        self.x = x
        self.y = y
        self.z = z
    def __add__(self, v):
        return Vec3(self.x + v.x, self.y + v.y, self.z + v.z)
    def __sub__(self, v):
        return Vec3(self.x - v.x, self.y - v.y, self.z - v.z)
    def __mul__(self, s: float):
        return Vec3(self.x * s, self.y * s, self.z * s)
    def __str__(self):
        return f'(x: {self.x}, y: {self.y}, z: {self.z})'