from xora_engine import engine, window
from game import Game
window.set_stats('Xora is cool', 800, 600, 0)

game = None

def init():
    global game
    game = Game()

def update():
    game.update(engine.delta_time())

def draw():
    game.draw()

def draw_ui():
    game.draw_ui()