from xora_engine import engine, window, input, input_lookup

window.set_stats('Xora is cool', 800, 600, 0)

def init():
    print(f'window width: {window.get_width()}')
    print(f'window height: {window.get_height()}')

def update():
    if input.is_key_down(input_lookup.Keys.escape):
        engine.quit()

def draw():
    pass
    # print(f'ft: {engine.frame_time()}')
