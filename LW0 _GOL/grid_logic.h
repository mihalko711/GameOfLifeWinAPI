#pragma once

#include "globals.h"
#include <vector>
#include <random>
#include <array>

//��������� �����:
void DrawGrid1D(HDC hdcMem, const std::vector<bool>& grid, int cellSize);
void DrawGrid2D(HDC hdcMem, const std::vector<std::vector<bool>>& grid, int cellSize);
//���������� ������� ������ � ������:
void UpdateGrid1D();
void UpdateGrid2D();
void ClearGrid1D();
void ClearGrid2D();
void RandomGrid1D();
void RandomGrid2D();

// ��������� ������� ������
struct Pattern {
    const char* data[16];  // �������� 16 ����� �� ������ (����� ���������)
    size_t rows;
};
//�������� ����� � ������ �����:
void DrawFromTemplate(POINT, const Pattern&);

// c��������� ��� �������� �����



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