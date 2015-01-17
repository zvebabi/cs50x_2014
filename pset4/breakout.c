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

// number of rows of bricks, no more than 10, because no more colors in color's string
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

//size of paddle
#define WIDTH_PAD WIDTH/10
#define HEIGHT_PAD HEIGHT/60
//size of briks
#define HEIGHT_BR HEIGHT_PAD
#define WIDTH_BR WIDTH/COLS-(float)HEIGHT_BR/2.0

#define VELOCITY 2.0
// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
GLabel initLives_Value(GWindow window);
void updateLivesValue(GWindow window, GLabel lives_value, int lives);

    
int main(int argc, char* argv[])
{
    // seed pseudorandom number generator
    srand48(time(NULL));

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
    
    //Initiate livesboard, bottom left of window
    GLabel lives_value = initLives_Value(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    //ball velocity
    double x_velocity = 3*drand48();
    double y_velocity = VELOCITY;
    
    //show lives
    updateLivesValue(window, lives_value, lives);
    
    // wait for click before starting    
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        pause (5); //slowly game
                    
        // PADDLE_MOVEMENT
        // check for mouse event for movement of pad
        if(argc > 1)
        {
            if(strcmp(argv[1], "GOD")==0)
            {
                move(paddle, x_velocity, 0);
            }
        }
        else 
        {
            GEvent event_pad = getNextEvent(MOUSE_EVENT);
            // if we heard one
            if (event_pad != NULL)
            {
                // if the event was movement
                if (getEventType(event_pad) == MOUSE_MOVED)
                {
                    // paddle foolow at cursor
                    double x = getX(event_pad) - WIDTH_PAD / 2;
                    double y = getY(paddle);
                    if (x < 0)
                    {
                        x = 0;
                    }
                    if (x > WIDTH-WIDTH_PAD)
                    {
                        x = WIDTH-WIDTH_PAD;
                    }
                    setLocation(paddle, x, y);
                }
            }
        }
        // BALL_MOVEMENT
        move(ball, x_velocity, y_velocity);
        if (getX(ball)<0 || getX(ball)+2*RADIUS > getWidth(window))
        {
            x_velocity = -x_velocity;
        }
        if (getY(ball)<0)
        {
            y_velocity = -y_velocity;
        }
        if(getY(ball)+2*RADIUS > getHeight(window))
        {
            lives--;
            updateLivesValue(window, lives_value, lives);
            setLocation(ball, getWidth(window)/2-RADIUS, getHeight(window)/2-RADIUS);
            setLocation(paddle,(WIDTH-WIDTH_PAD)/2, HEIGHT*9/10);
            if (lives<1)
            {
                break;
            }
            waitForClick();
        }        
        
        //detect paddle-ball touching or ball-brick
        GObject object = detectCollision(window, ball);
        
        if(object != NULL)
        {
            if(strcmp(getType(object), "GRect")== 0)
            {
                if(object==paddle)
                {
                    y_velocity = -y_velocity;
                }
                else //remove brick if ball touched
                {
                    y_velocity = -y_velocity;
                    removeGWindow(window, object);
                    ++points;
                    --bricks;
                    updateScoreboard(window, label, points);
                }
            }
        }   
        
        
    }
    
    //Lose or Win label
    if(bricks>0)
    {
        GLabel game_over= newGLabel("You loose!");
        setColor(game_over, "RED");
        setFont(game_over, "SansSerif-36");
        add(window, game_over);
        setLocation(game_over, (WIDTH-getWidth(game_over))/2, HEIGHT*1/3);
    }
    else
    {
        GLabel game_over= newGLabel("YOU WIN!");
        setColor(game_over, "GREEN");
        setFont(game_over, "SansSerif-36");
        add(window, game_over);
        setLocation(game_over, (WIDTH-getWidth(game_over))/2, HEIGHT*1/3);
    }

        
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/*
*  Init label with lives
*/
GLabel initLives_Value(GWindow window)
{    
    GLabel lives_value= newGLabel("");
    setColor(lives_value, "LIGHT_GRAY");
    setFont(lives_value, "SansSerif-25");
    setLocation(lives_value, 10, HEIGHT-10);
    add(window, lives_value);
    return lives_value;    
}

/*
*Update lives value
*/
void updateLivesValue(GWindow window, GLabel lives_value, int lives)
{
    //update label
    char l[12];
    char t[7]=" lives";    
    sprintf(l, "%i%s", lives, t);
    setLabel(lives_value, l);
    //positioning of label
    setLocation(lives_value, 10, HEIGHT-10);
}        
/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    //set color for rows
    string colors[10]={"CYAN", "GREEN","YELLOW", "ORANGE", "RED","CYAN", "GREEN","YELLOW", "ORANGE", "RED"};
    for(int i=0; i < ROWS; ++i)
    {
        for(int j=0; j < COLS; ++j)
        {
            GRect brick = newGRect(HEIGHT_BR/4+j*(HEIGHT_BR/2+WIDTH_BR),HEIGHT*1/12+i*(HEIGHT_BR*3/2),WIDTH_BR, HEIGHT_BR);
            setFilled(brick, true); 
            setColor(brick, colors[i]);
            add(window, brick);
        }
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(getWidth(window)/2-RADIUS, getHeight(window)/2-RADIUS, 2*RADIUS,2*RADIUS);
    setFilled(ball,true);
    setColor(ball, "BLUE");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((WIDTH-WIDTH_PAD)/2, HEIGHT*9/10, WIDTH_PAD, HEIGHT_PAD);
    setFilled(paddle, true);
    setColor(paddle, "black");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreboard = newGLabel("0");
    setFont(scoreboard, "SansSerif-36");
    setColor(scoreboard, "LIGHT_GRAY");
    double x = (getWidth(window) - getWidth(scoreboard)) / 2;
    double y = (getHeight(window) - getHeight(scoreboard)) / 2;
    setLocation(scoreboard, x, y);
    add(window, scoreboard);
    return scoreboard;
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
