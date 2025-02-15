def is_key_down(key_id: int) -> bool: ...
def is_mouse_button_down(button_id: int) -> bool: ...
def get_mouse_pos() -> tuple[int, int]: ...
def set_mouse_pos(x: int, y: int) -> None: ...
def get_mouse_change() -> tuple[int, int]: ...

def is_gamepad_connected(pad_id: int) -> bool: ...
def get_gamepad_name(pad_id: int) -> str: ...
def is_gamepad_button_down(pad_id: int, button_id: int) -> bool: ...
def get_gamepad_axis(pad_id: int, axis_id: int) -> float: ...
