#pragma once

#include "globals.h"
#include <vector>
#include <random>
#include <array>

//Отрисовка сетки:
void DrawGrid1D(HDC hdcMem, const std::vector<bool>& grid, int cellSize);
void DrawGrid2D(HDC hdcMem, const std::vector<std::vector<bool>>& grid, int cellSize);
//Оставшиеся функции работы с сеткой:
void UpdateGrid1D();
void UpdateGrid2D();
void ClearGrid1D();
void ClearGrid2D();
void RandomGrid1D();
void RandomGrid2D();

// Структура шаблона фигуры
struct Pattern {
    const char* data[16];  // максимум 16 строк на шаблон (можно увеличить)
    size_t rows;
};
//Отрисова фигур в логике сетки:
void DrawFromTemplate(POINT, const Pattern&);

// cструктуры для шаблонов фигур



extern const Pattern block;
extern const Pattern beehive;
extern const Pattern loaf;
extern const Pattern boat;
extern const Pattern tub;

extern const Pattern blinker;
extern const Pattern toad;
extern const Pattern beacon;
extern const Pattern pulsar;

extern const Pattern glider;
extern const Pattern lwss;
extern const Pattern mwss;
extern const Pattern hwss;