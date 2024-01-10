// Отключение предупреждения C4996 (связано с функциями безопасности ввода/вывода в Visual Studio)
#define _CRT_SECURE_NO_WARNINGS

// Подключение необходимых заголовочных файлов
#include <GL/glut.h>            // Заголовочный файл GLUT
#include <fstream>              // Заголовочный файл для работы с файлами
#include <iostream>             // Заголовочный файл для потокового ввода/вывода
#include <vector>               // Заголовочный файл для работы с векторами
#include <png.h>                // Заголовочный файл для работы с изображениями PNG
#include <imgui.h>              // Заголовочный файл библиотеки Dear ImGui
#include "imgui_impl_opengl3.h"// Заголовочный файл для связи ImGui с OpenGL
#include "imgui_impl_glut.h"    // Заголовочный файл для связи ImGui с GLUT

// Структура, представляющая точку в трехмерном пространстве
struct Point {
    float x, y, z;
};

std::vector<Point> points;      // Вектор для хранения точек
float rotationAngle = 0.0f;     // Угол вращения
float rotationAngleX = 0.0f;    // Угол вращения по оси X
float rotationAngleY = 0.0f;    // Угол вращения по оси Y
ImVec4 pointColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Цвет точек по умолчанию - черный
float pointSize = 8.0f;         // Размер точек по умолчанию

// Функция для чтения точек из файла
void readPointsFromFile(const char* filename) {
    std::ifstream file(filename); // Открытие файла
    if (!file.is_open()) {        // Проверка на успешное открытие файла
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    Point p;
    while (file >> p.x >> p.y >> p.z) { // Чтение координат точек из файла
        points.push_back(p); // Добавление точки в вектор
    }

    file.close(); // Закрытие файла
}

// Функция для сохранения изображения в формате PNG
void savePNG(const char* filename, int width, int height, unsigned char* pixels) {
    FILE* fp = fopen(filename, "wb"); // Открытие файла для записи
    if (!fp) { // Проверка на успешное открытие файла
        std::cerr << "Error: Unable to create file " << filename << std::endl;
        return;
    }

    // Создание структуры для записи PNG изображения
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) { // Проверка на успешное создание структуры
        fclose(fp);
        std::cerr << "Error: Unable to create PNG write structure" << std::endl;
        return;
    }

    // Создание структуры с информацией об изображении
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) { // Проверка на успешное создание структуры
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        fclose(fp);
        std::cerr << "Error: Unable to create PNG info structure" << std::endl;
        return;
    }

    // Установка параметров изображения (ширина, высота, глубина цвета и т.д.)
    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Выделение памяти и установка указателей на строки изображения
    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; ++y) {
        row_pointers[y] = (png_bytep)&pixels[(height - y - 1) * width * 3];
    }

    // Инициализация записи изображения в файл
    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    fclose(fp); // Закрытие файла
    png_destroy_write_struct(&png_ptr, &info_ptr); // Освобождение памяти
    free(row_pointers); // Освобождение памяти
}

// Функция для отрисовки интерфейса с помощью ImGui
void imguiRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(400.0f, 170.0f));

    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    // Интерфейс для изменения углов вращения и параметров точек
    ImGui::SliderFloat("Rotation Angle Z", &rotationAngle, 0.0f, 360.0f);
    ImGui::SliderFloat("Rotation Angle X", &rotationAngleX, 0.0f, 360.0f);
    ImGui::SliderFloat("Rotation Angle Y", &rotationAngleY, 0.0f, 360.0f);

    ImGui::ColorEdit3("Point Color", (float*)&pointColor);

    ImGui::SliderFloat("Point Size", &pointSize, 1.0f, 10.0f);

    // Кнопка для сохранения скриншота
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

// Функция отрисовки сцены
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

    // Отрисовка всех точек из вектора
    for (const auto& point : points) {
        glVertex3f(point.x, point.y, point.z);
    }

    glEnd();
    glFlush();

    imguiRender(); // Вызов функции отрисовки интерфейса
    glutSwapBuffers();
}

// Функция инициализации OpenGL
void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Основная функция программы
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(840, 900);
    glutCreateWindow("OpenGL Points from File");

    readPointsFromFile("output.txt"); // Чтение точек из файла

    ImGui::CreateContext(); // Инициализация ImGui
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init();

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(800.0f, 600.0f);

    init(); // Инициализация OpenGL

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

    glutMainLoop(); // Основной цикл GLUT

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
