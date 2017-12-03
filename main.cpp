#include <GLFW/glfw3.h>
#include <irrKlang/irrKlang.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "object.cpp"

using namespace std;
using namespace irrklang;

ISoundEngine* music = createIrrKlangDevice();

void animate() {
    if(parameter <= 0) parameter=3;
    if (state!=2 && state!=3) {
        ground1 -= velocity;
        if (ground1 <= SCREEN_LEFT-200) {
            ground1=ground4+200;
        }
        ground2 -= velocity;
        if (ground2 <= SCREEN_LEFT-200) {
            ground2=ground1+200;
        }
        ground3 -= velocity;
        if (ground3 <= SCREEN_LEFT-200) {
            ground3=ground2+200;
        }
        ground4 -= velocity;
        if (ground4 <= SCREEN_LEFT-200) {
            ground4=ground3+200;
        }
    }
    if(start==1) {
        if(posX > SCREEN_LEFT+125) posX -= velocity/3;
        if(posX <= SCREEN_LEFT+125) blinking=0;
        objX -= velocity;
        if (objX <= -400) {
            objX=400;
            tipe=rand()%3;
        }
    }
    if(jump==1 && run==0) {
        if(posY<=maxheight && state!=2)
            posY += velocity;
        else
            run = 1;
    }
    if(run==1) {
        if(posY >= minheight) {
            if(tipe==0 && (posX+30>=objX && posX-30<=objX+50) && posY>=minheight+75 && state!=2){
                posY -= velocity;
            }
            if(tipe==0 && !(posX+30>=objX && posX-30<=objX+50) && state!=2) {
                posY -= velocity;
            }
            if(tipe>0 && state!=2) {
                posY -= velocity;
            }
        }
        else {
            jump = 0;
            keyEnable = 1;
        }
    }
    if(tipe==0) {
        if(jump==0) {
            if(slide==0 && (posX+30>=objX && posX-30<=objX+50) && state!=2) {
                parameter--;
                blinking=1;
                posX=objX+100;
                posY=minheight;
                if(parameter==0) {
                    finalscore=score;
                    posX=SCREEN_LEFT+125;
                    objX=350;
                    state=3;
                    start=0;
                    parameter=3;
                    music->stopAllSounds();
                    music->play2D("audio/03.ogg", false);
                }
            }
            if(slide==1 && (posX+22>=objX && posX-22<=objX+50) && state!=2) {
                parameter--;
                blinking=1;
                posX=objX+100;
                posY=minheight;
                if(parameter==0) {
                    finalscore=score;
                    posX=SCREEN_LEFT+125;
                    objX=350;
                    state=3;
                    start=0;
                    parameter=3;
                    music->stopAllSounds();
                    music->play2D("audio/03.ogg", false);
                }
            }
        }
        if(jump==1) {
            if(posY+30<=minheight+75 && (posX+30>=objX && posX-30<=objX+50) && state!=2) {
                parameter--;
                blinking=1;
                jump=0;
				run=1;
                posX=objX+100;
                posY=minheight;
                if(parameter==0) {
                    finalscore=score;
                    posX=SCREEN_LEFT+125;
                    objX=350;
                    state=3;
                    start=0;
                    parameter=3;
                    music->stopAllSounds();
                    music->play2D("audio/03.ogg", false);
                }
            }
        }
    }
    if(tipe==1 && (posX+30>=objX && posX-30<=objX+50) && slide==0 && state!=2) {
        parameter--;
        blinking=1;
        jump=0;
		run=1;
        posX=objX+100;
        posY=minheight;
        if(parameter==0) {
            finalscore=score;
            posX=SCREEN_LEFT+125;
            objX=350;
            state=3;
            start=0;
            parameter=3;
            music->stopAllSounds();
            music->play2D("audio/03.ogg", false);
        }
    }
    if(tipe==2 && jump==0) {
        if(posY >= minheight-100 && (posX-30>=objX && posX-30<=objX+100) && state!=2) {
			if (posX+30 >= objX+100) posX=objX+70;
            posY -= velocity;
            keyEnable = 0;
            if (posY <= minheight-75) {
                parameter--;
                blinking=1;
                posX=objX+200;
                posY=minheight;
                if(parameter==0) {
                    finalscore=score;
                    posX=SCREEN_LEFT+125;
                    objX=350;
                    state=3;
                    start=0;
                    parameter=3;
                    music->stopAllSounds();
                    music->play2D("audio/03.ogg", false);
                }
            }
        }
        else keyEnable=1;
    }
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        if (start==0) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        else {
            start=0;
            state=2;
        }
    }
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        if (state!=2) {
            music->stopAllSounds();
            music->play2D("audio/01.ogg", true);
        }
        start=1;
        state=1;
        slide=0;
    }
    if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
        music->stopAllSounds();
        music->play2D("audio/01.ogg", true);
        start=0;
        state=0;
        objX=350;
        parameter=3;
        score=0;
        velocity=0.2;
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS && slide == 0 && state == 1 && keyEnable == 1) {
        music->play2D("audio/02.ogg", false);
        jump=1;
        run=0;
        keyEnable=0;
    }
    if(key == GLFW_KEY_DOWN && jump==0 && state == 1){
        if(action == GLFW_PRESS) {
            slide = 1;
            run = 0;
        }
        else if(action == GLFW_RELEASE) {
            slide = 0;
            run = 1;
        }
    }
}

void setup_viewport(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(SCREEN_LEFT, SCREEN_RIGHT, SCREEN_BOTTOM, SCREEN_TOP, SCREEN_FRONT, SCREEN_BACK);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    if(state==0) menu();
    if(state==1) background();
    if(state==2) pause();
    if(state==3) {
		gameover();
		score=0;
		velocity=0.2;
		temp = finalscore;
		digit4 = temp%10;
		scores(SCREEN_RIGHT-5, SCREEN_TOP-5, 2, digit4);
		temp /= 10;
		digit3 = temp%10;
		scores(SCREEN_RIGHT-35, SCREEN_TOP-5, 2, digit3);
		temp /= 10;
		digit2 = temp%10;
		scores(SCREEN_RIGHT-65, SCREEN_TOP-5, 2, digit2);
		temp /= 10;
		digit1 = temp%10;
		scores(SCREEN_RIGHT-95, SCREEN_TOP-5, 2, digit1);
	}
    alas(ground1, SCREEN_BOTTOM); alas(ground2, SCREEN_BOTTOM); alas(ground3, SCREEN_BOTTOM); alas(ground4, SCREEN_BOTTOM);
    nyawa(); poin();

    rintangan(objX, SCREEN_BOTTOM, 2, tipe);
    glPushMatrix();
        if (slide == 1) {
            glScalef(0.7, 0.7, 0);
            glTranslatef(-95, -55, 0);
        }
        if (state!=3) karakter(posX, posY, 1, sprite);
        else karakter(SCREEN_LEFT+(SCREEN_RIGHT-SCREEN_LEFT)/2, posY, 1, 13);
    glPopMatrix();
}

int main(int argc, char *argv[]) {
    GLFWwindow* window;
    if (!glfwInit()) exit(EXIT_FAILURE);
    window = glfwCreateWindow(600, 400, "Project Grafkom", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glTga();

    music->play2D("audio/00.ogg", true);

    while (!glfwWindowShouldClose(window)) {
        currentTime=glfwGetTime();
        while (currentTime> ticks) {
            animate();
            ticks+=0.001;
            if (blinking==0) {
                if (sprite>12) sprite=1;
                if (state!=2) sprite+=0.01;
            }
            else {
                if (sprite>2) sprite=0;
                if (state!=2) sprite+=0.01;
            }
            if (state==1) score+=0.01;
            if (state==1) velocity+=0.00001;
            currentTime=glfwGetTime();
        }

        setup_viewport(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
