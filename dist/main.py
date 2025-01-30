from xora_engine import engine, window

window.set_stats('Xora is cool', 800, 600, 0)

def init():
    print(f'window width: {window.get_width()}')
    print(f'window height: {window.get_height()}')

def update():
    pass
    # print(f'dt: {engine.delta_time()}')

def draw():
    pass
    # print(f'ft: {engine.frame_time()}')
