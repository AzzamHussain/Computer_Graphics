#include <gl/glut.h>
#include <iostream>
#include <Windows.h>
// #include <mmsystem.h>  // Commented out the header for sound as it won't be needed
#include <stdio.h>
#include "pixMap.h"

using namespace std;

// Removed the backgroundPixmap
int screenWidth = 700;
int screenHeight = 700;
int score = 0; // Score to track hits

// Global variables to control bullet movement direction
float bulletDirectionX = 0.0f; // Bullet's horizontal direction

class Point2
{
public:
    float x, y;
    Point2() : x(0), y(0) {}
    Point2(float xx, float yy) : x(xx), y(yy) {}
    float getX() { return x; }
    float getY() { return y; }
};

class Spider
{
private:
    enum State
    {
        ALIVE,
        DEAD
    } state;
    RGBApixmap pix[2];
    float directionX, directionY; // Direction of movement
    int spiderWidth, spiderHeight;
    bool splashVisible; // To show splash effect when hit
    int splashTimer;    // Timer to control splash visibility
public:
    float pos_X, pos_Y;
    bool isMoving;
    float spiderSpeed;

    Spider() {}

    Spider(Point2 pos)
    {
        isMoving = true;
        splashVisible = false;
        splashTimer = 0;
        spiderSpeed = 39.0f; // Movement speed

        // spiderSpeed = 99.0f; // Movement speed
        this->pos_X = pos.getX();
        this->pos_Y = pos.getY();
        directionX = 0.5f;  // Initial direction (moving right)
        directionY = 1.0f;  // Initial direction (moving up)
        spiderWidth = 100;  // Set desired width
        spiderHeight = 100; // Set desired height

        string fname[2] = {"spider.bmp", "mak3.bmp"}; // Replace with actual image filenames
        for (int i = 0; i < 2; i++)
        {
            pix[i].readBMPFile(fname[i], 1);
            pix[i].setChromaKey(255, 255, 255);
        }
    }

    void setState(int i)
    {
        if (i == 1)
            this->state = DEAD;
        else
        {
            this->state = ALIVE;
        }
    }

    int getState()
    {
        return (this->state == DEAD) ? 1 : 0;
    }

    void changePosition(float dx, float dy)
    {
        this->pos_X += dx;
        this->pos_Y += dy;
    }

    void hit()
    {
        this->isMoving = false;
        this->state = DEAD;
        splashVisible = true; // Show splash
        splashTimer = 50;     // Set a timer for splash visibility
        score++;              // Increase the score when hit
    }

    void reset()
    {
        pos_X = rand() % (screenWidth - 100); // Reset to a random position
        pos_Y = rand() % (screenHeight - 100);
        isMoving = true;
        setState(0); // Set state to ALIVE
    }

    void render()
    {
        glPushMatrix();
        glRasterPos2f(this->pos_X, this->pos_Y);

        // Scale the spider to the desired size
        glPixelZoom((float)spiderWidth / pix[0].nCols, (float)spiderHeight / pix[0].nRows);

        if (splashVisible)
        {
            pix[1].mDraw(); // Show splash effect
        }
        else if (this->isMoving)
        {
            pix[0].mDraw();
        }
        glPopMatrix();

        // Countdown splash timer and reset if needed
        if (splashTimer > 0)
        {
            splashTimer--;
        }
        if (splashTimer == 0 && splashVisible)
        {
            splashVisible = false;
            reset(); // Reset spider after showing splash
        }
    }

    void moveSpider()
    {
        if (!isMoving)
            return; // Don't move if it's not moving

        // Update position with constant movement
        pos_X += directionX * spiderSpeed;
        pos_Y += directionY * spiderSpeed;

        // Bounce off the screen edges
        if (pos_X < 0 || pos_X > screenWidth - 100)
        {
            directionX = -directionX; // Reverse X direction
        }
        if (pos_Y < 0 || pos_Y > screenHeight - 100)
        {
            directionY = -directionY; // Reverse Y direction
        }
    }
};

Spider spider(Point2(300, 220));

bool isBulletFired = false;
bool isBulletMoving = false;
float bulletX = screenWidth / 2;
float bulletY = 50.0f;
float bulletSpeed = 10.0f; // Reduced for smoother movement

void updateBullet()
{
    if (isBulletMoving)
    {
        bulletY += bulletSpeed;
        bulletX += bulletDirectionX * bulletSpeed; // Add horizontal movement

        if (bulletY >= screenHeight)
        {
            isBulletMoving = false;
        }
    }
}

class Bullet
{
public:
    float x, y;
    Bullet(float initialX, float initialY) : x(initialX), y(initialY) {}

    void render()
    {
        glPushMatrix();
        glTranslatef(x, y, 0.0);
        glColor3f(0.9, 0.5, 0.6);

        // glColor3f(0.5, 0.1, 0.2);

        // Enlarge the bullet by 10x
        // Triangle for the tip of the bullet
        glBegin(GL_TRIANGLES);
        glVertex2f(0, 0);
        glVertex2f(-25, -45); // Was -3, -5
        glVertex2f(25, -45);  // Was 3, -5
        glEnd();

        // Polygon for the body of the bullet
        glBegin(GL_POLYGON);
        glVertex2f(20, -40);   // Was 3, -5
        glVertex2f(-20, -40);  // Was -3, -5
        glVertex2f(-20, -140); // Was -3, -15
        glVertex2f(20, -140);  // Was 3, -15
        glEnd();

        glPopMatrix();
    }

    void setPosition(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    void changePosition(float dx, float dy)
    {
        x += dx;
        y += dy;
    }
};

Bullet bullet(bulletX, bulletY);

void bullet_movement(int y)
{
    bullet.changePosition(bulletDirectionX * 20, 20);
    glutPostRedisplay();

    // Adjust collision detection to match the spider's actual size (spiderWidth and spiderHeight)
    if ((bullet.x >= spider.pos_X && bullet.x <= spider.pos_X + 100) &&
        (bullet.y >= spider.pos_Y && bullet.y <= spider.pos_Y + 100))
    {
        bullet.setPosition(bulletX, 20);
        spider.hit(); // Call hit instead of die
        isBulletMoving = false;
        glutPostRedisplay();
    }

    if (bullet.y < screenHeight && isBulletMoving)
    { // Allow bullet to go fully upwards
        glutTimerFunc(5, bullet_movement, y);
    }
    else if (bullet.y >= screenHeight)
    { // When bullet reaches the top
        bullet.setPosition(bulletX, 20);
        glutPostRedisplay();
    }
}

void pressKeySpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (!isBulletMoving)
        {
            isBulletMoving = true;
            isBulletFired = true;
            bullet_movement(0);
        }
        break;
    case GLUT_KEY_LEFT:                // Move bullet to the left before firing
        bullet.changePosition(-10, 0); // Set direction to left
        break;
    case GLUT_KEY_RIGHT:              // Move bullet to the right before firing
        bullet.changePosition(10, 0); // Set direction to right
        break;
    }
}

void displayScore()
{
    glColor3f(0.0, 0.0, 0.0); // Black color for score
    glRasterPos2f(20, screenHeight - 30);
    string scoreText = "Score: " + to_string(score);
    for (char &c : scoreText)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update game objects
    updateBullet();
    spider.moveSpider(); // Continuous spider movement
    spider.render();
    bullet.render();

    // Display the score
    displayScore();

    glFlush(); // Flush the rendering pipeline after drawing everything
}

void myInit(void)
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Red background
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_EQUAL, 1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Spider Game");

    glutDisplayFunc(myDisplay);
    glutSpecialFunc(pressKeySpecial);

    myInit();
    glutIdleFunc(myDisplay); // Ensure the game keeps updating

    glutMainLoop();
}