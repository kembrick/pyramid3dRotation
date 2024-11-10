#ifndef PYRAMID3D_SHOW3D_H
#define PYRAMID3D_SHOW3D_H

#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "rigidBody.h"

int screenWidth = 800, screenHeight = 800;

float c1 = (float)sqrt(3) / 6;
float c2 = (float)sqrt(3) / 3;
float c3 = 1.0f / 4.0f; // rotation about the mass center - 1/4 of the pyramid height

void drawShape() {

    glColor3f(0.2, 0.9, 0.5);

    glBegin(GL_TRIANGLES);

    //bottom triangle
    glVertex3f(-0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0, c2 * a , -c3 * h);

    //right side triangle
    glVertex3f(-0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0, 0, h - c3 * h);

    //left side triangle
    glVertex3f(0, 0, h - c3 * h);
    glVertex3f(-0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0, c2 * a , -c3 * h);

    //front triangle
    glVertex3f(0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0, 0, h - c3 * h);
    glVertex3f(0, c2 * a , -c3 * h);

    glEnd();

}

void display() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 1, 1, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    RigidBody rigby = calculateRotation();
    glTranslated(0.0f, 0.0f, -100.0f);
    glRotatef(2 * (float)rad2Deg(acos(rigby.q.r)), (float)rigby.q.i, (float)rigby.q.j, (float)rigby.q.k);
    drawShape();
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void start(int argc, char** argv) {
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Regular triangle pyramid rotation");
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

#endif //PYRAMID3D_SHOW3D_H