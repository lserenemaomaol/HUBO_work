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
            
                    
                case 'b':
                    if( status == 0) {
                            std::cout << "'B' key pressed!\n";
                            std::cout << " Motion in progress: biped -> quad_ready !\n";
                            system("/home/hubo/hongfei/otherRepos/hubo-read-trajectory/hubo-read-trajectory -f 100 -i -n /home/hubo/hongfei/myRepos/HUBO_work/trajs/BipedOverBricks_v5.txt");		
                            status = 1;
                             break;
                    }
                    
                    if( status == 1)  {
                            std::cout << "Illegal Input!\n   status = 1 ! \n";
                            std::cout << "Type f !\n";
                            break;
                    }
             
                    
                case 'f':
                    if( status == 1 ) {
                            std::cout << "'F' key pressed!  \n";
                            std::cout << " Motion in progress: quad_ready -> biped !\n";
                            system("/home/hubo/hongfei/otherRepos/hubo-read-trajectory/hubo-read-trajectory -f 100 -i -n /home/hubo/hongfei/myRepos/HUBO_work/trajs/BipedOverBricks_v5.txt");
                            status = 0;
                            break;
                    }

                    if( status == 0 ) {
                            std::cout << "Illegal Input!\n   status = 0 ! \n";
                            std::cout << "Type b !\n";
                            break;
                    }
 

            }
        }

    }
    tty_reset(STDIN_FILENO);
    return 0;
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

