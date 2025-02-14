from xora_engine import engine, window, graphics
from game import Game
from utils.texture import Texture
window.set_stats('Xora is cool', 800, 600, 0)

game = None
tex = None
acc = 0
idx = 0

def init():
    global game
    global tex
    game = Game()
    # tex = Texture(graphics.new_texture_from_file('./textures/moth.png'))
    # # tex.height = -600.0
    # # tex.width = 800.0
    # tex.width = 4 * 64.0
    # tex.height = 4 * 64.0
    # tex.sw /= 12

def update():
    game.update(engine.delta_time())

def draw():
    game.draw()
    pass

def draw_ui():
    # game.draw_ui()
    # global acc
    # global idx
    # ft = engine.frame_time()
    # acc += ft
    # if acc > 1/12:
    #     acc -= 1/12
    #     idx += 1
    #     idx %= 12
    # tex.sx = tex.sh * idx
    # tex.draw(0.0, 0.0)
    pass