#include <GLFW/glfw3.h>
#include <irrKlang/irrKlang.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

float SCREEN_RIGHT=300, SCREEN_LEFT=-300, SCREEN_TOP=200, SCREEN_BOTTOM=-200, SCREEN_FRONT=10.f, SCREEN_BACK=-10.f;
float ground1=SCREEN_LEFT, ground2=SCREEN_LEFT+200, ground3=SCREEN_LEFT+400, ground4=SCREEN_LEFT+600;
float posX=SCREEN_LEFT+125, posY=SCREEN_BOTTOM+105;
float maxheight=posY+130, minheight=posY, objX=350, ticks=0.0, velocity=0.2, score=0, sprite=1, finalscore;
int run=1, jump=0, slide=0, keyEnable=1, state=0, start=0, parameter=3, tipe;
int digit1, digit2, digit3, digit4, temp, blinking=0;
double currentTime = glfwGetTime();

void load_bmp(char *filename, unsigned int texture_id) {
    FILE *file;
    short int bpp, planes;
    long size, imgwidth, imgheight, i;
    char *imgdata, temp;

    if (!(file = fopen(filename, "rb"))) {
        fprintf(stderr, "Error: file %s not found!\n", filename);
    };

    fseek(file, 18, SEEK_CUR);
    fread(&imgwidth, 4, 1, file);
    fread(&imgheight, 4, 1, file);

    size = imgwidth * imgheight * 3;
    fread(&bpp, 2, 1, file);
    fread(&planes, 2, 1, file);

    fseek(file, 24, SEEK_CUR);
    imgdata = (char *)malloc(size);
    fread(imgdata, size, 1, file);

    for ( i = 0; i < size; i += 3) {
        temp = imgdata[i];
        imgdata[i] = imgdata[i+2];
        imgdata[i+2] = temp;
    }
    fclose(file);

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgwidth, imgheight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgdata);
    free(imgdata);
}

void glTga(void) {
    glEnable (GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    load_bmp("img/ground.bmp", 1);
    load_bmp("img/wall.bmp", 2);
    load_bmp("img/heart.bmp", 3);
    load_bmp("img/emptyheart.bmp", 4);
    load_bmp("img/menu.bmp", 5);
    load_bmp("img/pause.bmp", 6);
    load_bmp("img/over.bmp", 7);
    load_bmp("img/0.bmp", 10);
    load_bmp("img/1.bmp", 11);
    load_bmp("img/2.bmp", 12);
    load_bmp("img/3.bmp", 13);
    load_bmp("img/4.bmp", 14);
    load_bmp("img/5.bmp", 15);
    load_bmp("img/6.bmp", 16);
    load_bmp("img/7.bmp", 17);
    load_bmp("img/8.bmp", 18);
    load_bmp("img/9.bmp", 19);
    load_bmp("img/blink.bmp", 20);
    load_bmp("img/poring01.bmp", 21);
    load_bmp("img/poring02.bmp", 22);
    load_bmp("img/poring03.bmp", 23);
    load_bmp("img/poring04.bmp", 24);
    load_bmp("img/poring05.bmp", 25);
    load_bmp("img/poring06.bmp", 26);
    load_bmp("img/poring07.bmp", 27);
    load_bmp("img/poring08.bmp", 28);
    load_bmp("img/poring09.bmp", 29);
    load_bmp("img/poring10.bmp", 30);
    load_bmp("img/poring11.bmp", 31);
    load_bmp("img/poring12.bmp", 32);
    load_bmp("img/poringsad.bmp", 33);
}

void karakter(float x, float y, float z, int sprit) {
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sprit+20);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 1);
            glVertex3f(x-30, y+30, z);
        glTexCoord2f(1, 1);
            glVertex3f(x+30, y+30, z);
        glTexCoord2f(1, 0);
            glVertex3f(x+30, y-30, z);
        glTexCoord2f(0, 0);
            glVertex3f(x-30, y-30, z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void circle (float x, float y, float z, float r){
    double t = 0;
    const float pi = 3.14159;
    float deltaT;
    deltaT = (3.14159/100.0)*0.1;
    glBegin(GL_POLYGON);
        for(t = 0.0; t <= (1*pi); t += deltaT){
            glVertex3f(r*cos(t)+x, r*sin(t)+y, z);
        }
        for(t = 0.0; t <= (1*pi); t += deltaT){
            glVertex3f(r*cos(-t)+x, r*sin(-t)+y, z);
        }
    glEnd();
}

void background() {
    glBegin(GL_POLYGON);
        glColor3ub(135, 206, 250);
        glVertex3f(SCREEN_LEFT, SCREEN_BOTTOM, 4);
        glVertex3f(SCREEN_RIGHT, SCREEN_BOTTOM, 4);
        glVertex3f(SCREEN_RIGHT, SCREEN_TOP, 4);
        glVertex3f(SCREEN_LEFT, SCREEN_TOP, 4);
    glEnd();
}

void menu() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 5);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 1);
            glVertex3f(SCREEN_LEFT, SCREEN_TOP, 4);
        glTexCoord2f(1, 1);
            glVertex3f(SCREEN_RIGHT, SCREEN_TOP, 4);
        glTexCoord2f(1, 0);
            glVertex3f(SCREEN_RIGHT, SCREEN_BOTTOM, 4);
        glTexCoord2f(0, 0);
            glVertex3f(SCREEN_LEFT, SCREEN_BOTTOM, 4);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void pause() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 1);
            glVertex3f(SCREEN_LEFT, SCREEN_TOP, 4);
        glTexCoord2f(1, 1);
            glVertex3f(SCREEN_RIGHT, SCREEN_TOP, 4);
        glTexCoord2f(1, 0);
            glVertex3f(SCREEN_RIGHT, SCREEN_BOTTOM, 4);
        glTexCoord2f(0, 0);
            glVertex3f(SCREEN_LEFT, SCREEN_BOTTOM, 4);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void gameover() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 1);
            glVertex3f(SCREEN_LEFT, SCREEN_TOP, 4);
        glTexCoord2f(1, 1);
            glVertex3f(SCREEN_RIGHT, SCREEN_TOP, 4);
        glTexCoord2f(1, 0);
            glVertex3f(SCREEN_RIGHT, SCREEN_BOTTOM, 4);
        glTexCoord2f(0, 0);
            glVertex3f(SCREEN_LEFT, SCREEN_BOTTOM, 4);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void life (float x, float y, float z) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 1);
            glVertex3f(x, y, z);
        glTexCoord2f(1, 1);
            glVertex3f(x+30, y, z);
        glTexCoord2f(1, 0);
            glVertex3f(x+30, y-30, z);
        glTexCoord2f(0, 0);
            glVertex3f(x, y-30, z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void scores (float x, float y, float z, int digit) {
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, digit+10);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 1);
            glVertex3f(x-30, y, z);
        glTexCoord2f(1, 1);
            glVertex3f(x, y, z);
        glTexCoord2f(1, 0);
            glVertex3f(x, y-30, z);
        glTexCoord2f(0, 0);
            glVertex3f(x-30, y-30, z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void emptylife (float x, float y, float z) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 1);
            glVertex3f(x, y, z);
        glTexCoord2f(1, 1);
            glVertex3f(x+30, y, z);
        glTexCoord2f(1, 0);
            glVertex3f(x+30, y-30, z);
        glTexCoord2f(0, 0);
            glVertex3f(x, y-30, z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void nyawa () {
    if(state>0 && state<3) {
        if(parameter==3) {
            life(SCREEN_LEFT+5, SCREEN_TOP-5, 2);
            life(SCREEN_LEFT+40, SCREEN_TOP-5, 2);
            life(SCREEN_LEFT+75, SCREEN_TOP-5, 2);
        }
        if(parameter==2) {
            life(SCREEN_LEFT+5, SCREEN_TOP-5, 2);
            life(SCREEN_LEFT+40, SCREEN_TOP-5, 2);
            emptylife(SCREEN_LEFT+75, SCREEN_TOP-5, 2);
        }
        if(parameter==1) {
            life(SCREEN_LEFT+5, SCREEN_TOP-5, 2);
            emptylife(SCREEN_LEFT+40, SCREEN_TOP-5, 2);
            emptylife(SCREEN_LEFT+75, SCREEN_TOP-5, 2);
        }
    }
}

void poin () {
	if(state>0 && state<3) {
		if(score > 9999) score=9999;
		temp = score;
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

	glColor3ub(135, 206, 250);
    glBegin(GL_POLYGON);
        glVertex3f(SCREEN_RIGHT-125, SCREEN_TOP-3, 1);
        glVertex3f(SCREEN_RIGHT-5, SCREEN_TOP-3, 1);
        glVertex3f(SCREEN_RIGHT-5, SCREEN_TOP-7, 1);
        glVertex3f(SCREEN_RIGHT-125, SCREEN_TOP-7, 1);
    glEnd();
}

void alas (float x, float y) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 1);
            glVertex3f(x, y+75, 3);
        glTexCoord2f(1, 1);
            glVertex3f(x+200, y+75, 3);
        glTexCoord2f(1, 0);
            glVertex3f(x+200, y, 3);
        glTexCoord2f(0, 0);
            glVertex3f(x, y, 3);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void rintangan (float x, float y, float z, int tipe) {
    switch (tipe) {
        case 0:
            glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 2);
                glBegin(GL_POLYGON);
                    glTexCoord2f(0, 1);
                        glVertex3f(x, y+150, z);
                    glTexCoord2f(1, 1);
                        glVertex3f(x+50, y+150, z);
                    glTexCoord2f(1, 0);
                        glVertex3f(x+50, y+75, z);
                    glTexCoord2f(0, 0);
                        glVertex3f(x, y+75, z);
                glEnd();
            glDisable(GL_TEXTURE_2D);
            break;
        case 1:
            glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 2);
                glBegin(GL_POLYGON);
                    glTexCoord2f(0, 1);
                        glVertex3f(x, y+200, z);
                    glTexCoord2f(1, 1);
                        glVertex3f(x+50, y+200, z);
                    glTexCoord2f(1, 0);
                        glVertex3f(x+50, y+120, z);
                    glTexCoord2f(0, 0);
                        glVertex3f(x, y+120, z);
                glEnd();
            glDisable(GL_TEXTURE_2D);
            break;
        case 2:
            glBegin(GL_POLYGON);
                glColor3ub(135, 206, 250);
                glVertex3f(x, y+75, z);
                glVertex3f(x+100, y+75, z);
                glVertex3f(x+100, y, z);
                glVertex3f(x, y, z);
            glEnd();
            break;
    }
}
