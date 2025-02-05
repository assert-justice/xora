from xora_engine import engine, window, input, input_lookup, graphics, xo_math

window.set_stats('Xora is cool', 800, 600, 0)

texture_id = 0
shader_id = 0
world_loc = 0
perspective_loc = 0
cam_pos = [0.0, 0.0, -2.0]

def init():
    global texture_id
    global shader_id
    global world_loc
    global perspective_loc
    texture_id = graphics.new_texture_from_file('./textures/wall.jpg')
    with open('./shaders/ball_vert.glsl', 'r') as f:
        vert_src = f.read()
    with open('./shaders/ball_frag.glsl', 'r') as f:
        frag_src = f.read()
    shader_id = graphics.new_shader(vert_src, frag_src)
    world_loc = graphics.get_shader_uniform_location(shader_id, 'world')
    perspective_loc = graphics.get_shader_uniform_location(shader_id, 'perspective')
    # print(perspective_loc)
    # print(window.get_dimensions())

def update():
    if input.is_key_down(input_lookup.Keys.escape):
        engine.quit()
    speed = 10
    dx = 0
    dy = 0
    dz = 0
    if input.is_key_down(input_lookup.Keys.a):
        dx = -1
    if input.is_key_down(input_lookup.Keys.d):
        dx = 1
    if input.is_key_down(input_lookup.Keys.left_control):
        dy = -1
    if input.is_key_down(input_lookup.Keys.space):
        dy = 1
    if input.is_key_down(input_lookup.Keys.s):
        dz = -1
    if input.is_key_down(input_lookup.Keys.w):
        dz = 1
    dt = engine.delta_time()
    dx *= speed * dt
    cam_pos[0] += dx
    dy *= speed * dt
    cam_pos[1] += dy
    dz *= speed * dt
    cam_pos[2] += dz

def draw():
    graphics.bind_shader(shader_id)
    graphics.bind_texture(texture_id)
    xo_math.push_identity()
    # xo_math.push_vector3(1.0, 0.0, 0.0)
    # xo_math.rotate_euler()
    graphics.set_shader_uniform_mat4x4(shader_id, world_loc)
    xo_math.push_perspective(30.0, 8.0/6.0, 0.01, 100.0)
    cx = cam_pos[0]
    cy = cam_pos[1]
    cz = cam_pos[2]
    xo_math.push_vector3(cx, cy, cz)
    xo_math.translate()
    graphics.set_shader_uniform_mat4x4(shader_id, perspective_loc)
    graphics.draw_mesh(1)

    # graphics.draw_texture(handle, 0.0, 0.0)
    # graphics.draw_texture_ext(texture_id, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 0.0)
    # print(f'ft: {engine.frame_time()}')
    pass

def draw_ui():
    graphics.draw_texture_ext(texture_id, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 0.0)
    pass