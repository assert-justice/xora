from xora_engine import engine

def init():
    print('sup')

def update():
    print(f'dt: {engine.delta_time()}')

def draw():
    print(f'ft: {engine.frame_time()}')