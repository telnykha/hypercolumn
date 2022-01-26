//---------------------------------------------------------------------------

#ifndef awpInterpolationH
#define awpInterpolationH
#include "awpipl.h"
//---------------------------------------------------------------------------
/*
    ���������� ������������.
    ������� ���������:
    src - �������� �����������  awpImage
    p - �����, ��� ������� ��������� ����� �������� �������  awp2DPoint
    �������� ��������:
    dst - �������� ������� ����������� � awpImage (���� �����, ���� ������,
          ��� AWP_DOUBLE
*/

AWPRESULT awpBilinearInterpolation(awpImage* src, awp2DPoint* p, awpImage* dst);

#endif
