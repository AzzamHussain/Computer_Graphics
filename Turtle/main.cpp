                                               //SNOWFLAKE//

//#include <GL/glut.h>
//#include <cmath>
//using namespace std;
//
//void drawMotif() {
//    glBegin(GL_LINE_STRIP);
//    glVertex2d(0.0f, 0.01f);
//    glVertex2d(0.3, 0.01);
//    glVertex2d(0.4, 0.15);
//    glVertex2d(0.41, 0.12);
//    glVertex2d(0.33, 0.01);
//    glVertex2d(0.5, 0.01);
//    glVertex2d(0.6, 0.13);
//    glVertex2d(0.61, 0.1);
//    glVertex2d(0.53, 0.01f);
//    glVertex2d(0.7, 0.01f);
//    glVertex2d(0.75, 0.0);
//    glEnd();
//}
//
//// Function to render the line
//void display() {
//    // Clear the screen with a white background
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // Set the line color to black
//    glColor3f(0.1f, 0.0f, 0.0f);
//
//    for (int i = 0; i < 8; ++i) {
//        glPushMatrix();
//        glRotated(i * 60, 0.0, 0.0, 1.0);
//        drawMotif();
//        glScalef(1.0, -1.0, 1.0);
//        drawMotif();
//        glScaled(1.0, -1.0, 1.0);
//        glPopMatrix();
//    }
//    // Flush the drawing to the screen
//    glFlush();
//}
//
//// Initialization function
//void init() {
//    // Set the background color to white
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//    // Set the projection (2D orthographic projection)
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set the coordinate system
//}
//
//int main(int argc, char** argv) {
//    // Initialize GLUT
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//
//    // Create a window
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Simple Line");
//
//    // Initialize OpenGL settings
//    init();
//
//    // Set the display function (called in the rendering loop)
//    glutDisplayFunc(display);
//
//    // Start the GLUT main loop
//    glutMainLoop();
//
//    return 0;
//}

                                              //TURTLE//

#include <GL/glut.h>
#include <cmath>
#include <vector>
#define PI 3.141592

// Define a simple structure to represent lines
struct Line {
    float x1, y1, x2, y2;
};

// Turtle class
class Turtle {
public:
    float x, y;          // Current position
    float heading;       // Heading angle in degrees
    bool isPenDown;      // Pen state (down or up)
    std::vector<Line> path;  // Stores the lines to draw

    Turtle() : x(0), y(0), heading(0), isPenDown(true) {}

    void forward(float distance) {
        float rad = heading * PI / 180.0f;  // Convert to radians
        float newX = x + distance * cos(rad);
        float newY = y + distance * sin(rad);

        if (isPenDown) {
            path.push_back({ x, y, newX, newY });
        }

        x = newX;
        y = newY;
    }

    void right(float angle) {
        heading -= angle;
    }

    void left(float angle) {
        heading += angle;
    }

    void penUp() {
        isPenDown = false;
    }

    void penDown() {
        isPenDown = true;
    }

    void draw() {
        glBegin(GL_LINES);
        for (const auto& line : path) {
            glVertex2f(line.x1, line.y1);
            glVertex2f(line.x2, line.y2);
        }
        glEnd();
    }
};

// Create a turtle instance
Turtle turtle;

// Initialize OpenGL settings
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);  // Black color for drawing lines
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);  // Set coordinate system
}

// Display callback for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    turtle.draw();  // Draw the turtle's path
    glFlush();
}

// Keyboard callback for controlling the turtle
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':  // Move forward
        turtle.forward(1);
        break;
    case 'a':  // Turn left
        turtle.left(15);
        break;
    case 'd':  // Turn right
        turtle.right(15);
        break;
    case 'u':  // Pen up
        turtle.penUp();
        break;
    case 'p':  // Pen down
        turtle.penDown();
        break;
    }
    glutPostRedisplay();  // Request a redraw
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);  // Set initial window position
    glutCreateWindow("Turtle Graphics with OpenGL");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}