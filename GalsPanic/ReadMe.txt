========================================================================
    WIN32 APPLICATION : GalsPanic Project Overview
========================================================================

HBRUSH hBrushCircle = CreateSolidBrush(��);
HBRUSH oldBrush = (HBRUSH) SelectObject(hdc, hBrushCircle);
Ellipse(hdc, ũ��);
SelectObject(hdc, oldBrush);
DeleteObject(hBrushCircle);

TransparentBlt(hdc, �簢��, memDC, �簢��, ��);
