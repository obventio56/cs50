//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
#define BH 12
#define BL 34
#define CD 10

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
GLabel initlives(GWindow window);
GLabel initWin(GWindow window);
GLabel initEnd(GWindow window);
void updatellabel(GWindow window, GLabel label, int points);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void sleep(unsigned int mseconds);

int main(void)
{   
    // seed pseudorandom number generator
    srand48(time(NULL));
    double vy = drand48();
    double vx = drand48();

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    GLabel llabel = initlives(window);
    setLocation(llabel, 10, 590);
    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    pause(1000);

    // keep playing until game over
    updatellabel(window, llabel, 3);
    while (lives > 0 && bricks > 0)
    {
        while(bricks > 0)
        {
            GEvent mouse = getNextEvent(MOUSE_EVENT);
            if (mouse != NULL)
            {
                if (getEventType(mouse) == MOUSE_MOVED)
                {
                    double x = getX(mouse) - getWidth(paddle) / 2;
                    double y = getY(paddle);
                    setLocation(paddle, x,y);
                }
            }
            move(ball,vx,vy);
            if (getX(ball) + CD >= WIDTH)
            {
                vx = -vx;
            } 
            else if (getX(ball) <= 0)
            {
                vx = -vx;
            }
            else if (getY(ball) <= 0)
            {
                vy = -vy;
            }
            pause(1);
            GObject object = detectCollision(window, ball);
            if (object != NULL)
            {
                if (object == paddle)
                {
                    vy = -vy;
                }
                else if (strcmp(getType(object), "GRect") == 0)
                {
                    bricks--;
                    points++;
                    updateScoreboard(window, label, points);
                    vy = -vy;
                    removeGWindow(window, object);
                }
            }
            if (getY(ball) + CD >= HEIGHT)
            {
                lives = lives - 1;
                updatellabel(window, llabel, lives);
                setLocation(ball,(WIDTH/2) - (CD/2), (HEIGHT/2) - (CD/2));
                pause (1000);
                if (bricks == 0)
                {
                GLabel win = initWin(window);
                pause(5000);
                break;
                }
                else
                {
                break;
                }
            } 
        }
        
    }

    // wait for click before exiting
    removeGWindow(window, label);
    GLabel messege = initEnd(window);
    sleep(5000);
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int x = 0; x < COLS; x++)
        {
            GRect brick = newGRect(2 + (BL+6) * x, 50 + (BH+2) * i, BL, BH);
            if (i == 0)
            {
            setColor(brick, "RED");
            }
            else if (i == 1)
            {
            setColor(brick, "YELLOW");
            }
            else if (i == 2)
            {
            setColor(brick, "ORANGE");
            }
            else if (i == 3)
            {
            setColor(brick, "GREEN");
            }
            else if (i == 4)
            {
            setColor(brick, "BLUE");
            }
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval((WIDTH/2) - (CD/2), (HEIGHT/2) - (CD/2), CD, CD);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((WIDTH/2) - (BL/2) ,HEIGHT - (BH + 10), BL, BH);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    add(window, label);
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    return label;
}

GLabel initlives(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-24");
    add(window, label);
    double x = 10;
    double y = 590;
    setLocation(label, x, y);
    return label;
}

GLabel initEnd(GWindow window)
{
    GLabel label = newGLabel("Click to Close Window");
    setFont(label, "SansSerif-24");
    add(window, label);
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    return label;
}

GLabel initWin(GWindow window)
{
    GLabel label = newGLabel("You Win!!!");
    setFont(label, "SansSerif-24");
    add(window, label);
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    return label;
}

void sleep(unsigned int mseconds) 
{ 
    clock_t goal = mseconds + clock(); 
    while (goal > clock()); 
}



/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

void updatellabel(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = 10;
    double y = 590;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
