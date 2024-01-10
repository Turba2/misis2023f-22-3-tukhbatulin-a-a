#define _CRT_SECURE_NO_WARNINGS // Отключение предупреждения C4996

#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <png.h> 
#include <imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glut.h"

struct Point {
    float x, y, z;
};

std::vector<Point> points;
float rotationAngle = 0.0f;
float rotationAngleX = 0.0f;
float rotationAngleY = 0.0f;
ImVec4 pointColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Черный цвет точек по умолчанию
float pointSize = 5.0f; // Размер точек по умолчанию

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

void savePNG(const char* filename, int width, int height, unsigned char* pixels) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        std::cerr << "Error: Unable to create file " << filename << std::endl;
        return;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(fp);
        std::cerr << "Error: Unable to create PNG write structure" << std::endl;
        return;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        fclose(fp);
        std::cerr << "Error: Unable to create PNG info structure" << std::endl;
        return;
    }

    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; ++y) {
        row_pointers[y] = (png_bytep)&pixels[(height - y - 1) * width * 3];
    }

    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    free(row_pointers);
}

void imguiRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(400.0f, 150.0f));

    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::SliderFloat("Rotation Angle Z", &rotationAngle, 0.0f, 360.0f);
    ImGui::SliderFloat("Rotation Angle X", &rotationAngleX, 0.0f, 360.0f);
    ImGui::SliderFloat("Rotation Angle Y", &rotationAngleY, 0.0f, 360.0f);

    ImGui::ColorEdit3("Point Color", (float*)&pointColor);

    ImGui::SliderFloat("Point Size", &pointSize, 1.0f, 10.0f);

    if (ImGui::Button("Save Screenshot")) {
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);
        unsigned char* pixels = new unsigned char[width * height * 3];
        glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

        savePNG("screenshot.png", width, height, pixels);

        delete[] pixels;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

    glPointSize(pointSize);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);

    glColor4f(pointColor.x, pointColor.y, pointColor.z, pointColor.w);

    for (const auto& point : points) {
        glVertex3f(point.x, point.y, point.z);
    }

    glEnd();
    glFlush();

    imguiRender();
    glutSwapBuffers();
}

void init() {
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
    glutInitWindowSize(840, 900);
    glutCreateWindow("OpenGL Points from File");

    readPointsFromFile("output.txt");

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
