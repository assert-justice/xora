from xora_engine import engine, window, input, input_lookup, graphics

window.set_stats('Xora is cool', 800, 600, 0)

handle = 0

def init():
    global handle
    print(f'window width: {window.get_width()}')
    print(f'window height: {window.get_height()}')
    handle = graphics.new_texture_from_file('./textures/wall.jpg')
    print(graphics.get_texture_dimensions(handle))
    # print(handle)

def update():
    if input.is_key_down(input_lookup.Keys.escape):
        engine.quit()

def draw():
    # graphics.draw_texture(handle, 0.0, 0.0)
    graphics.draw_texture_ext(handle, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 0.0)
    # print(f'ft: {engine.frame_time()}')
