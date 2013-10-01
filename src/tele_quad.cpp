#include <iostream>
#include <fstream>
#include <termio.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cstdlib>

static int tty_unbuffered(int);     
static void tty_atexit(void);
static int tty_reset(int);
static void keyboard_init();

static void key_help();
static void B_pressed();
static void F_pressed();
static void W_pressed();
static void S_pressed();
static void A_pressed();
static void D_pressed();
static void Q_pressed();
static void E_pressed();
static void H_pressed();


static struct termios save_termios;
static int  ttysavefd = -1;

int main(int argc, char **argv)
{
    keyboard_init();
    

    char c;
    int status=0; // status = 0 : in biped mode            status =1 : in quad mode
    std::cout << "The tele-quad is on!\n  Type h for help in instructions! \n";
    while(1)
    {
        if ( read(STDIN_FILENO, &c, 1) == 1) {
            switch (c) {

                case 'B':    
                case 'b':
                    if( status == 0) {
                            B_pressed();
                            status = 1;
                             break;
                    }                    
                    if( status == 1)  {
                            key_help();
                            break;
                    }
                case 'F':    
                case 'f':
                    if( status == 1 ) {
                            F_pressed();
                            status = 0;
                            break;
                    }
                    if( status == 0 ) {
                            key_help();
                            break;
                    }
                 case 'W':
                 case 'w':
                    if( status == 1) {
                            W_pressed();
                            break;
                    } 
                    if( status == 0) {
                            key_help();
                            break;
                    }
                 case 'S':
                 case 's':
                    if(status ==1) {
                            S_pressed();
                            break;
                    }
                    if( status == 0 ) {
                            key_help();
                            break;
                    }
                 case 'A':
                 case 'a':
                    if(status ==1) {
                            A_pressed();
                            break;
                    }
                    if(status == 0) {
                            key_help();
                            break;
                    }
                 case 'D':
                 case 'd':
                    if(status == 1 ) { 
                            D_pressed();
                            break;
                    }
                    if(status == 0) {
                            key_help();
                            break;
                    }
                 case 'Q':
                 case 'q':
                    if(status == 1 ) { 
                            Q_pressed();
                            break;
                    }
                    if(status == 0) {
                            key_help();
                            break;
                    }
                 case 'E':
                 case 'e':
                    if(status == 1 ) { 
                            E_pressed();
                            break;
                    }
                    if(status == 0) {
                            key_help();
                            break;
                    }
                 case 'H':
                 case 'h':
                            H_pressed();                    
                    break;

                 default:
                    std::cout << "Undefined keys!  type h for instruction help! \n";

            }
        }

    }
    tty_reset(STDIN_FILENO);
    return 0;
}

static void key_help() {
    std::cout << "Illegal Input!\n   status = 1 ! \n";
    std::cout << "Type h for help !\n";
}
static void B_pressed() {   
    std::cout << "'B' key pressed!\n";
    std::cout << " Motion in progress: biped -> quad_ready !\n";
    system("/home/hubo/hongfei/otherRepos/hubo-read-trajectory/hubo-read-trajectory -f 100 -i -n /home/hubo/hongfei/myRepos/HUBO_work/trajs/quadwalk_crouch.txt");
}

static void F_pressed() {
    std::cout << "'F' key pressed!  \n";
    std::cout << " Motion in progress: quad_ready -> biped !\n";
    system("/home/hubo/hongfei/otherRepos/hubo-read-trajectory/hubo-read-trajectory -f 100 -i -n /home/hubo/hongfei/myRepos/HUBO_work/trajs/quadwalk_stand.txt");
}

static void W_pressed() {
    std::cout << "'W' key pressed!  \n";
    std::cout << " Motion in progress: quad_forward ! \n";                           
    system("/home/hubo/hongfei/otherRepos/hubo-read-trajectory/hubo-read-trajectory -f 100 -i -n /home/hubo/hongfei/myRepos/HUBO_work/trajs/quadwalk_forward.txt");
}

    

static void S_pressed() {
    std::cout << "'S' key pressed! \n";                          
    std::cout << "Motion in progress: quad_backward ! \n";
    system("/home/hubo/hongfei/otherRepos/hubo-read-trajectory/hubo-read-trajectory -f 100 -i -n /home/hubo/hongfei/myRepos/HUBO_work/trajs/quadwalk_back.txt");
}

static void A_pressed() {
    std::cout << "'A' key pressed! \n"; 
    std::cout << "Motion in progress:  Left turn by 22.5 degrees! \n";
    system("/home/hubo/hongfei/otherRepos/hubo-read-trajectory/hubo-read-trajectory -f 100 -i -n /home/hubo/hongfei/myRepos/HUBO_work/trajs/quadwalk_turnleft.txt");
}

static void D_pressed() {
    std::cout << "'D' key pressed ! \n";
    std::cout << "Motion in progress: Right turn by 22.5 degrees! \n";
    system("/home/hubo/hongfei/otherRepos/hubo-read-trajectory/hubo-read-trajectory -f 100 -i -n /home/hubo/hongfei/myRepos/HUBO_work/trajs/quadwalk_turnright.txt");
}

static void Q_pressed() {
    std::cout << "'Q' key pressed ! \n";
    std::cout << "Motion in progress: Move Left side by 5cm! \n";
    system("/home/hubo/hongfei/otherRepos/hubo-read-trajectory/hubo-read-trajectory -f 100 -i -n /home/hubo/hongfei/myRepos/HUBO_work/trajs/quadwalk_sideright.txt");
}

static void E_pressed() {
    std::cout << "'E' key pressed ! \n";
    std::cout << "Motion in progress: Move Right side by 5cm! \n";
    system("/home/hubo/hongfei/otherRepos/hubo-read-trajectory/hubo-read-trajectory -f 100 -i -n /home/hubo/hongfei/myRepos/HUBO_work/trajs/quadwalk_sideleft.txt");
}

static void H_pressed() {
    std::cout << "Legal keys for tele-operation : \n";
    std::cout << "b :          crouch down   ,   biped->quad   status->1   \n";
    std::cout << "f :          stand  up     ,   quad ->biped  status->0   \n";
    std::cout << "w :          quad-forward  ,   status=1   required         \n";
    std::cout << "u :   fast   quad-forward  ,   status=1   required         \n";
    std::cout << "s :          quad_backward ,   status=1   required         \n";
    std::cout << "a :          turn   left   ,   status=1   required         \n";
    std::cout << "d :          turn   right  ,   status=1   required         \n";
    std::cout << "q :          side   left   ,   status=1   required         \n";
    std::cout << "e :          side   right  ,   status=1   required         \n";
}



static int
tty_unbuffered(int fd)      /* put terminal into a raw mode */
{
    struct termios  buf;

    if (tcgetattr(fd, &buf) < 0)
        return(-1);
        
    save_termios = buf; /* structure copy */

    /* echo off, canonical mode off */
    buf.c_lflag &= ~(ECHO | ICANON);

    /* 1 byte at a time, no timer */
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
        return(-1);

    ttysavefd = fd;
    return(0);
}

static int
tty_reset(int fd)       /* restore terminal's mode */
{
    if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
        return(-1);
    return(0);
}

static void
tty_atexit(void)        /* can be set up by atexit(tty_atexit) */
{
    if (ttysavefd >= 0)
        tty_reset(ttysavefd);
}

static void
keyboard_init()
{
   /* make stdin unbuffered */
    if (tty_unbuffered(STDIN_FILENO) < 0) {
        std::cout << "Set tty unbuffered error" << std::endl;
        exit(1);
    }

    atexit(tty_atexit);

    /* nonblock I/O */
    int flags;
    if ( (flags = fcntl(STDIN_FILENO, F_GETFL, 0)) == 1) {
        perror("fcntl get flag error");
        exit(1);
    }
    if (fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl set flag error");
        exit(1);
    }
}

