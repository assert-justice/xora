def add_box_shape(width: float, height: float, depth: float) -> int: ...
def add_sphere_shape(radius: float) -> int: ...
def add_rigid_body(shape_id: int, x: float, y: float, z: float, mass: float) -> int: ...
def push_body_transform(body_id: int) -> None: ...
def get_body_position(body_id: int) -> tuple[float, float, float]: ...
def add_force(body_id: int, fx: float, fy: float, fz: float) -> None: ...
def add_impulse(body_id: int, fx: float, fy: float, fz: float) -> None: ...
def simulate() -> None: ...
