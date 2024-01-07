#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glut.h"

float rotationAngle = 0.0f;

struct Point {
    float x, y, z;
};

std::vector<Point> points;


void readPointsFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    Point p;
    while (file >> p.x >> p.y >> p.z) {
        points.push_back(p);
    }

    file.close();
}

void imguiRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    ImGui::NewFrame();

    ImGui::SliderFloat("Rotation Angle", &rotationAngle, 0.0f, 360.0f);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Используем текущее значение rotationAngle для поворота
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Поворот точек на угол

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f); // белый цвет точек

    for (const auto& point : points) {
        glVertex3f(point.x, point.y, point.z);
    }

    glEnd();
    glFlush();

    imguiRender();
    glutSwapBuffers();
}
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Points from File");

    readPointsFromFile("trr.txt");

    ImGui::CreateContext();
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init();

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(800.0f, 600.0f);

    init();

    glutDisplayFunc(display);
    glutIdleFunc([]() {
        glutPostRedisplay();
        });


    glutReshapeFunc(ImGui_ImplGLUT_ReshapeFunc);
    glutKeyboardFunc(ImGui_ImplGLUT_KeyboardFunc);
    glutSpecialFunc(ImGui_ImplGLUT_SpecialFunc);
    glutMouseFunc(ImGui_ImplGLUT_MouseFunc);
    glutMotionFunc(ImGui_ImplGLUT_MotionFunc);
    glutPassiveMotionFunc(ImGui_ImplGLUT_MotionFunc);

    glutMainLoop();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
    return 0;
}
