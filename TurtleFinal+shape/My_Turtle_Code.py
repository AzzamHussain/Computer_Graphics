import turtle

# Initialize turtle
turtleX, turtleY = 0.0, 0.0
angle = 0.0

# Set up the turtle screen
screen = turtle.Screen()
t = turtle.Turtle()

def move_forward():
    t.forward(50)

def move_backward():
    t.backward(50)

def turn_left():
    t.left(45)

def turn_right():
    t.right(45)

# Keyboard bindings for controlling the turtle
screen.listen()
screen.onkey(move_forward, "w")
screen.onkey(move_backward, "s")
screen.onkey(turn_left, "a")
screen.onkey(turn_right, "d")

# Start the main loop
screen.mainloop()
