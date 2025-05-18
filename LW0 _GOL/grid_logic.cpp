#include "grid_logic.h"

void DrawGrid1D(HDC hdcMem, const std::vector<bool>& grid, int cellSize) {
    for (size_t i = 0; i < cellCount1D * cellCount1D; i++) {
        RECT cellRect = {
            (LONG)((i % cellCount1D) * cellSize), (LONG)((i / cellCount1D) * cellSize),
            (LONG)((i % cellCount1D + 1) * cellSize), (LONG)(((i / cellCount1D) + 1) * cellSize)
        };

        FillRect(hdcMem, &cellRect, grid[i] ? hBrushAlive1D : hBrushDead1D);
    }

    if (cellBorder1D) {
        // граница
        int yMax = cellCount1D * cellSize;
        int xMax = cellCount1D * cellSize;
        int xPos, yPos;
        for (int x = 0; x < cellCount1D; x++) {
            yPos = x * cellSize;
            MoveToEx(hdcMem, 0, yPos, NULL);
            LineTo(hdcMem, yMax, yPos);
        }
        for (int y = 0; y < cellCount1D; y++) {
            xPos = y * cellSize;
            MoveToEx(hdcMem, xPos, 0, NULL);
            LineTo(hdcMem, xPos, xMax);
        }
    }
}
void DrawGrid2D(HDC hdcMem, const std::vector<std::vector<bool>>& grid, int cellSize) {
    for (int x = 0; x < cellCount2D; x++) {
        for (int y = 0; y < cellCount2D; y++) {
            RECT cellRect = {
                y * cellSize,
                x * cellSize,
                (y + 1) * cellSize,
                (x + 1) * cellSize
            };

            FillRect(hdcMem, &cellRect, grid[x][y] ? hBrushAlive2D : hBrushDead2D);

            
        }
    }

    if (cellBorder2D) {
        // граница
        int yMax = cellCount2D * cellSize;
        int xMax = cellCount2D * cellSize;
        int xPos, yPos;
        for (int x = 0; x < cellCount2D; x++) {
            yPos = x * cellSize;
            MoveToEx(hdcMem, 0, yPos, NULL);
            LineTo(hdcMem, yMax, yPos);
        }
        for (int y = 0; y < cellCount2D; y++) {
            xPos = y * cellSize;
            MoveToEx(hdcMem, xPos, 0, NULL);
            LineTo(hdcMem, xPos, xMax);
        }
    }
}

void UpdateGrid1D() {
    std::vector<bool> newGrid1D = grid1D;

    for (int i = 0; i < cellCount1D * cellCount1D; ++i) {
        // получаем 3-битный шаблон: левый, текущий, правый
        int left = (i == 0) ? 0 : grid1D[i - 1];
        int curr = grid1D[i];
        int right = (i == cellCount1D * cellCount1D - 1) ? 0 : grid1D[i + 1];

        // сформировать индекс от 0 до 7
        int pattern = (left << 2) | (curr << 1) | right;

        // проверить соответствующий бит в числе rule (бит номер pattern)
        newGrid1D[i] = (rule1D >> pattern) & 1;
    }
    grid1D = newGrid1D;
}

void UpdateGrid2D() {
    std::vector<std::vector<bool>> newGrid2D = grid2D;
    int grid2Dheight = grid2D.size();
    int grid2Dwidth = grid2D[0].size();
    for (size_t i = 0; i < grid2D.size(); i++) {
        for (size_t j = 0; j < grid2D[i].size(); j++) {
            int liveNeighbors = 0;

            for (int x = -1; (x <= 1); x++) {
                for (int y = -1; (y <= 1); y++) {
                    if ((x == 0) && (y == 0)) continue;

                    if (i + x >= 0 && i + x < grid2Dheight && j + y >= 0 && j + y < grid2Dwidth && grid2D[i + x][j + y]) liveNeighbors++;
                }
            }

            if (grid2D[i][j]) {
                if (liveNeighbors < 2 || liveNeighbors > 3)
                    newGrid2D[i][j] = false;
            }
            else if (liveNeighbors == 3) newGrid2D[i][j] = true;
        }
    }

    grid2D = newGrid2D;
}

void ClearGrid1D() {
    for (size_t i = 0; i < grid1D.size(); i++) {
        grid1D[i] = false;
    }
}

void ClearGrid2D() {
    for (size_t i = 0; i < grid2D.size(); i++) {
        for (size_t j = 0; j < grid2D[i].size(); j++) {
            grid2D[i][j] = false;
        }
    }
}

void RandomGrid1D() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);

    for (size_t i = 0; i < grid1D.size(); i++) {
        grid1D[i] = distrib(gen);
    }
}

void RandomGrid2D() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);

    for (size_t i = 0; i < grid2D.size(); i++) {
        for (size_t j = 0; j < grid2D[i].size(); j++) {
            grid2D[i][j] = distrib(gen);
        }
    }
}

void DrawFromTemplate(POINT pt, const Pattern& pattern) {
    for (size_t dy = 0; dy < pattern.rows; ++dy) {
        for (size_t dx = 0; pattern.data[dy][dx] != '\0'; ++dx) {
            if (pattern.data[dy][dx] == '#' && pt.x + dx < cellCount2D && pt.y + dy < cellCount2D) {
                grid2D[pt.y + dy][pt.x + dx] = true;
            }
        }
    }
}

// Still Lifes
const Pattern block = {
    {
        "##",
        "##"
    },
    2
};

const Pattern beehive = {
    {
        ".##.",
        "#..#",
        ".##."
    },
    3
};

const Pattern loaf = {
    {
        ".##.",
        "#..#",
        ".#.#",
        "..#."
    },
    4
};

const Pattern boat = {
    {
        "##.",
        "#.#",
        ".#."
    },
    3
};

const Pattern tub = {
    {
        ".#.",
        "#.#",
        ".#."
    },
    3
};

// Oscillators
const Pattern blinker = {
    {
        "###"
    },
    1
};

const Pattern toad = {
    {
        ".###",
        "###."
    },
    2
};

const Pattern beacon = {
    {
        "##..",
        "##..",
        "..##",
        "..##"
    },
    4
};

const Pattern pulsar = {
    {
        "..###...###..",
        ".............",
        "#....#.#....#",
        "#....#.#....#",
        "#....#.#....#",
        "..###...###..",
        ".............",
        "..###...###..",
        "#....#.#....#",
        "#....#.#....#",
        "#....#.#....#",
        ".............",
        "..###...###..",
    },
    13
};

// Spaceships
const Pattern glider = {
    {
        ".#.",
        "..#",
        "###"
    },
    3
};

const Pattern lwss = {
    {
        "#..#.",
        "....#",
        "#...#",
        ".####"
    },
    4
};

const Pattern mwss = {
    {
        "..#...",
        "#...#.",
        ".....#",
        "#....#",
        ".#####"
    },
    5
};

const Pattern hwss = {
    {
        "..##...",
        "#....#.",
        "......#",
        "#.....#",
        ".######"
    },
    5
};
