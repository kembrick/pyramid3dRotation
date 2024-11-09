#ifndef PYRAMID3D_SHOW3D_H
#define PYRAMID3D_SHOW3D_H

#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "rigidBody.h"

int screenWidth = 800, screenHeight = 800;

double c1 = sqrt(3) / 6;
double c2 = sqrt(3) / 3;
double c3 = 1.0f / 4.0f; // rotation about the mass center - 1/4 of the pyramid height

void drawShape() {

    glColor3f(0.2, 0.9, 0.5);

    glBegin(GL_TRIANGLES);

    //bottom triangle
    glVertex3f(-0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0.0f, c2 * a , -c3 * h);

    //right side triangle
    glVertex3f(-0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0.0f, 0.0f, h - c3 * h);

    //left side triangle
    glVertex3f(0.0f, 0.0f, h - c3 * h);
    glVertex3f(-0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0.0f, c2 * a , -c3 * h);

    //front triangle
    glVertex3f(0.5f * a, -c1 * a, -c3 * h);
    glVertex3f(0.0f, 0.0f, h - c3 * h);
    glVertex3f(0.0f, c2 * a , -c3 * h);

    glEnd();

}

void display() {
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 1, 1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    RigidBody rigby = calculateRotation();
    glTranslated(0.0f, 0.0f, -100.0f);
    glRotatef(2 * rad2Deg(acos(rigby.q.r)), rigby.q.i, rigby.q.j, rigby.q.k);
    drawShape();
    glPopMatrix();
    glFlush();
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