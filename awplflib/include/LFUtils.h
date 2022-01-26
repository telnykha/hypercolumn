/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                  Locate Framework  Computer Vision Library
//
// Copyright (C) 2004-2018, NN-Videolab.net, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the NN-Videolab.net or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//      Locate Framework  (LF) Computer Vision Library.
//		File: LFUtils.h
//		Purpose: different utils to work with ROI
//
//      CopyRight 2004-2018 (c) NN-Videolab.net
//M*/
//---------------------------------------------------------------------------
#ifndef RoiUtilsH
#define RoiUtilsH
//---------------------------------------------------------------------------
/** \defgroup LFRoiUtils
*	 (obsolete) Different utils to work with ROI
*   @{
*/


awp2DPoint  awpGetPointsCentroid(awp2DPoint* p, int count);
awpPoint    awpGetPointsCentroid(awpPoint* p, int count);
awpRect     awpResizeRect(awpRect r, double scale);
awpPoint    awpGetLeftTopRectCorner(awpRect r);
awpPoint    awpGetRightBottomRectCorner(awpRect r);
awpRect     awpTranslateRect(awpRect r, awpPoint p);
awpRect     awpTranslateRect(awpRect r, awp2DPoint p);
awpPoint    awpTranslatePoint (awpPoint p, int dx, int dy);
awpPoint    awpTranslatePoint (awp2DPoint p, int dx, int dy);
int awpRectWidth(awpRect r);
int awpRectHeight(awpRect r);
awpRect  awpCreateRect(awpPoint lt, awpPoint rb);
// ��������� �������������� "�����" ����� ��������������
AWPBOOL IsPointInRect(awpPoint p, awpRect r);
//������ ����� ��������������
awpPoint RectCenter (awpRect r);

//"��������" ����� ����������� pImage, ������������� pRoi � ������ ppPoints
void ImageROIToPoints(awpImage* pImage, TROI* pRoi, awp2DPoint** ppPoints, int* count, int thr);
bool GetROIMoments(awpImage* img, TROI* roi, double& m00, double& m01, double& m10,
double& m20, double& m02, double& m11);
// ���������� ROI �� dx dy
TROI TranslateROI(TROI* roi, int dx, int dy);
//�������� ������� ROI �� scale
TROI ResizeROI(TROI* roi, double scale);
// ������������ roi �� �������� ���� ������������ ��������� �����
TROI RotateROI(TROI* roi, double angle, awpPoint center);
//������� �.�. ��������������
bool GetCenterMass(awpImage* pImage, TROI* r, awpPoint* p);
//////
bool IsIntersect(TROI* r1, TROI* r2);



/*
            RoiDistanceAvg
    ��������� ���������� ����� ����� roi
*/
double RoiDistanceAvg(TROI& roi1, TROI& roi2);
/*
            RoiDistanceMin
    ��������� ���������� ����� ����� roi
*/
double RoiDistanceMin(TROI& roi1, TROI& roi2);
/*
            RoiDistanceMax
    ��������� ���������� ����� ����� roi
*/
double RoiDistanceMax(TROI& roi1, TROI& roi2);
/*
            RoiDistance1
    ��������� ���������� ����� ����� roi
*/
double RoiDistance1(TROI& roi1, TROI& roi2);
/*
            RoiDistance2
    ��������� ���������� ����� ����� roi
*/
double RoiDistance2(TROI& roi1, TROI& roi2);

/*
        Points2Rois
    ����������� ������ ����� � ������ roi
*/
int Points2Rois(awpPoint* pPoints, int Num, TROI** ppRois, AWPWORD MinDistance, AWPWORD MaxDistance, double Angle);
/*
        ClusterRois
    ������� ������� roi � ��������
*/
int ClusterRois(TROI* pRois, int Num, TROI** ppClusters);

/*
     AoiRect2Roi
     ����������� �������������, � �������� w = h  � ROI
*/
bool AoiRect2Roi(awpRect r, TROI& roi, double c1 = 0.5, double c2 = 0.25);

// ��������� �������� ������ AOI
awpImage* GetAOISource(awpImage* pImage, awpPoint p1, awpPoint p2);
awpImage* GetAOIImage(awpImage* pImage, awpPoint p1, awpPoint p2);
/** @} */ /*  end of LFRoiUtils group */
#endif
