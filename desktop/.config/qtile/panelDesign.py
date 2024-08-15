from typing import Optional
from libqtile.widget.textbox import TextBox

def lower_left_triangle():
    return TextBox(
        text='\u25e2',
        padding=0,
        fontsize=50,
        background="#282a36",
        foreground="#f8f8f8")

def left_half_circle(fg_color, bg_color):
    return TextBox(
        text='\uE0B6',
        fontsize=35,
        foreground=fg_color,
        background=bg_color,
        padding=0)


def right_half_circle(fg_color, bg_color: Optional['str'] = None):
    return TextBox(
        text='\uE0B4',
        fontsize=35,
        background=bg_color,
        foreground=fg_color,
        padding=0)
