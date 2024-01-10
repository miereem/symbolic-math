#include <windows.h>

#include <math.h>
#include  <float.h>
#include "structures.h"


const unsigned long lineColor = RGB(0, 0, 0);
 unsigned long graphColor = RGB(0xFF, 0, 0xFF);

const short lineWidth = 1;
const short graphWidth = 1;
//const short defaultWidth = 400;
//const short defaultHeight = 400;
const float scale = 0.001;
const char szClassName[] = "Graph of function";
const LPCWSTR xLabel = L"x";
const LPSTR yLabel = L"y";
struct Plots plotsArray;
//const int maxX = 5;
//const int maxY = 10;
//const int minX = -5;
const int indentation = 3;

LRESULT CALLBACK DCDemoGraphProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI winMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nFunsterStil, const short width, const short height);

void plot(struct Plots plots, const short weight, const short height) {
    plotsArray = plots;
    winMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOWNORMAL, weight, height);

}

double maximX(PointArray pointArray) {
    double max = DBL_MIN;
    for (int i = 0; i < pointArray.count; i++) {
        if (fabs(pointArray.points[i].x) > max) {
            max = fabs(pointArray.points[i].x);
        }
    }
    return max;
}
double maxXX(struct Plots plots) {
    double max = DBL_MIN;
    for (int i = 0; i < plots.count; i++) {
        if (maximX(plots.plots[i]) > max) {
            max = maximX(plots.plots[i]);
        }
    }
    return max;
}
double maximY(PointArray pointArray) {
    double max = DBL_MIN;
    for (int i = 0; i < pointArray.count; i++) {
        if (fabs(pointArray.points[i].y) > max) {
            max = fabs(pointArray.points[i].y);
        }
    }
    return max;
}
double maxYY(struct Plots plots) {
    double max = DBL_MIN;
    for (int i = 0; i < plots.count; i++) {
        if (maximY(plots.plots[i]) > max) {
            max = maximY(plots.plots[i]);
        }
    }
    return max;
}


int percent(float Value, int per) {
    return (int) Value * per / 100;
};


int WINAPI winMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nFunsterStil, const short width, const short height) {
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;


    wincl.hInstance = hInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = DCDemoGraphProc;
    wincl.style = CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDC_ARROW);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wincl.lpszClassName = szClassName;

    if (!RegisterClassEx(&wincl))
        return 0;


    hwnd = CreateWindowEx(
            0,
            szClassName,
            szClassName,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            width,
            height,
            NULL,
            NULL,
            hInstance,
            NULL
    );

    ShowWindow(hwnd, nFunsterStil);
    UpdateWindow(hwnd);

    while (GetMessage(&messages, NULL, 0, 0)) {

        TranslateMessage(&messages);

        DispatchMessage(&messages);
    }


    return messages.wParam;
}


LRESULT CALLBACK DCDemoGraphProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int x, y, x0, y0;
    float dx, dy, currentX, currentY, xMiddle, yMiddle;
    HDC hDC;
    PAINTSTRUCT PaintStruct;
    HANDLE hBM;
    RECT Rect;
    HPEN pen;
    switch (message) {

        case WM_PAINT:
            GetClientRect(hwnd, &Rect);
            hDC = BeginPaint(hwnd, &PaintStruct);
            pen = CreatePen(PS_SOLID, lineWidth, lineColor);
            SelectObject(hDC, pen);
            // рисование осей координат
            x0 = percent(PaintStruct.rcPaint.right, indentation);
            y0 = (PaintStruct.rcPaint.bottom - percent(PaintStruct.rcPaint.bottom, indentation));
            yMiddle = y0 / 2;
            MoveToEx(hDC, x0,
                     y0 / 2,
                     NULL);
            LineTo(hDC, PaintStruct.rcPaint.right - percent(PaintStruct.rcPaint.right, indentation),
                   y0 / 2);

            Rect.left = PaintStruct.rcPaint.right - percent(PaintStruct.rcPaint.right, indentation);
            Rect.top = yMiddle;
            DrawText(hDC, xLabel, -1, &Rect, DT_BOTTOM);

            xMiddle = (PaintStruct.rcPaint.right) / 2;
            MoveToEx(hDC, xMiddle, y0, NULL);
            LineTo(hDC, xMiddle,
                   PaintStruct.rcPaint.top + percent(PaintStruct.rcPaint.bottom, indentation));
            Rect.left = PaintStruct.rcPaint.right / 2;
            Rect.top = PaintStruct.rcPaint.top;
            DrawText(hDC, yLabel, -1, &Rect, DT_BOTTOM);
//--------------------------------------------------------------------------------------------
            y0 = y0 / 2;

            double maxX = maxXX(plotsArray) * 2;
            double maxY = maxYY(plotsArray)* 2;
            dx = ((float) (PaintStruct.rcPaint.right - percent(PaintStruct.rcPaint.right, indentation * 2))) / maxX;
            dy = ((float) (PaintStruct.rcPaint.bottom - percent(PaintStruct.rcPaint.bottom, indentation * 2))) /
                 maxY;
            for (int plotN = 0; plotN < plotsArray.count; plotN++) {
                graphColor = RGB(plotN%256, plotN*2%256, plotN*56%256);
                PointArray currentPoints = plotsArray.plots[plotN];
                pen = CreatePen(PS_SOLID, graphWidth, graphColor);
                SelectObject(hDC, pen);
                // Масштаб

                currentX = currentPoints.points[0].x;
                currentY = currentPoints.points[0].y;
                x = xMiddle + currentX * dx;
                y = y0 - currentY * dy;
                MoveToEx(hDC, x, y, NULL);
                LineTo(hDC, x, y);
                for (int i = 0; i < currentPoints.count; i++) {
                    currentX = currentPoints.points[i].x;
                    currentY = currentPoints.points[i].y;
                    x = xMiddle + currentX * dx;
                    y = y0 - currentY * dy;
                    LineTo(hDC, x, y);
                }
            }
            EndPaint(hwnd, &PaintStruct);
            DeleteObject(pen);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}