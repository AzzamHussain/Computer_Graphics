#include <windows.h>   // Include for Windows OS
#include <gl/Gl.h>     // OpenGL library
#include <gl/Glu.h>    // GLU library
#include <gl/glut.h>   // GLUT library

// Function to draw axes
void axis(double length)
{
    // Draw a z-axis with a cone at the end
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0); 
    glVertex3d(0, 0, length); // Along the z-axis
    glEnd();
    
    // Translate to the end of the axis to draw the cone
    glTranslated(0, 0, length - 0.2);
    glutWireCone(0.04, 0.2, 12, 9);
    glPopMatrix();
}

// Function to display wireframes
void displayWire(void)
{
    // Set the view volume shape
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0 * 64 / 48.0, 2.0 * 64 / 48.0, -2.0, 2.0, 0.1, 100);

    // Position and aim the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color to black for drawing lines
    glColor3d(0, 0, 0);

    // Draw axes
    axis(0.5); // Z-axis

    glPushMatrix();
    glRotated(90, 0, 1.0, 0); // Rotate to draw the Y-axis
    axis(0.5); // Y-axis
    glRotated(-90.0, 1, 0, 0); // Rotate to draw the X-axis
    axis(0.5); // X-axis
    glPopMatrix();

    // Draw shapes
    glPushMatrix();
    glTranslated(0.5, 0.5, 0.5); // Big cube at (0.5, 0.5, 0.5)
    glutWireCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.0, 1.0, 0); // Sphere at (1,1,0)
    glutWireSphere(0.25, 10, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.0, 0, 1.0); // Cone at (1,0,1)
    glutWireCone(0.2, 0.5, 10, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1, 1, 1); // Teapot at (1,1,1)
    glutWireTeapot(0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 1.0, 0); // Torus at (0,1,0)
    glRotated(90.0, 1, 0, 0);
    glutWireTorus(0.1, 0.3, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.0, 0, 0); // Dodecahedron at (1,0,0)
    glScaled(0.15, 0.15, 0.15);
    glutWireDodecahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 1.0, 1.0); // Small Cube at (0,1,1)
    glutWireCube(0.25);
    glPopMatrix();

    // Draw Cylinder
    glPushMatrix();
    glTranslated(0, 0, 1.0); // Cylinder at (0,0,1)
    GLUquadricObj* qobj = gluNewQuadric(); // Initialize quadric object
    gluQuadricDrawStyle(qobj, GLU_LINE);
    gluCylinder(qobj, 0.2, 0.2, 0.4, 8, 8);
    gluDeleteQuadric(qobj); // Free the quadric object after use
    glPopMatrix();

    // Flush drawing commands
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Initialize display mode
    glutInitWindowSize(640, 680); // Window size
    glutInitWindowPosition(100, 100); // Window position
    glutCreateWindow("Transformation testbed - wireframes"); // Create window
    glutDisplayFunc(displayWire); // Set display callback function

    // Set background color and viewport
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glViewport(0, 0, 640, 640);

    // Start the main loop
    glutMainLoop();

    return 0; // Program termination
}
