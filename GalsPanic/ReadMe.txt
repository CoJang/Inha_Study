========================================================================
    WIN32 APPLICATION : GalsPanic Project Overview
========================================================================

HBRUSH hBrushCircle = CreateSolidBrush(색);
HBRUSH oldBrush = (HBRUSH) SelectObject(hdc, hBrushCircle);
Ellipse(hdc, 크기);
SelectObject(hdc, oldBrush);
DeleteObject(hBrushCircle);

TransparentBlt(hdc, 사각형, memDC, 사각형, 색);
