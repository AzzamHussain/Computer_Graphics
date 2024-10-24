import turtle

def draw_polygon(sides, length):
    angle = 360 / sides  
    for _ in range(sides):
        turtle.forward(length) 
        turtle.right(angle)     

# A hexagon
turtle.speed(3)
draw_polygon(6, 100)
turtle.done()






