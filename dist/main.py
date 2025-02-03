from xora_engine import engine, window, input, input_lookup, graphics

window.set_stats('Xora is cool', 800, 600, 0)

texture_id = 0
shader_id = 0
world_loc = 0
perspective_loc = 0

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

def update():
    if input.is_key_down(input_lookup.Keys.escape):
        engine.quit()

def draw():
    graphics.bind_shader(shader_id)
    graphics.bind_texture(texture_id)
    # graphics.draw_mesh(1)

    # graphics.draw_texture(handle, 0.0, 0.0)
    # graphics.draw_texture_ext(texture_id, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 0.0)
    # print(f'ft: {engine.frame_time()}')
    pass
