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
//		File: LFFeatures.h
//		Purpose: Declares features:
//
//		TLFAFeature			- simply brigness feature
//		TLFSFeature			- simply dispertion feature
//		TLFHFeature			- horizontal gradient feature with norm
//		TLFHAFeature		- just horizontal gradient feature
//		TLFVFeature			- vertical gradient feature with norm
//		TLFVAFeature        - just vertical gradient feature
//		TLFDFeature			- diagonal gradient feature with norm
//		TLFDAFeature        - just diagonal gradient feature
//		TLFCFeature			- center feature with norm
//		TLFCAFeature		- just center feature
//		TLFLBPFeature		- 256 pin binary pattern
//		TLFColorSensor		- color 24 bit feature
//      TLFColorSensor9Bit  - color feature 9 bit
//		TCSSensor			- 512 pin binary pattern (census feature)
//
//      CopyRight 2004-2018 (c) NN-Videolab.net
//M*/
#ifndef _HLFEATURES_H
#define _HLFEATURES_H

/** \defgroup LFFeatures 
*	Implementation set of features of the Locate Framework
*   @{
*/

/*
	average feature. 
*/
class TLFAFeature : public ILFFeature
{
public:
	TLFAFeature();
	TLFAFeature(int sxbase, int sybase, int wbase, int hbase);
	TLFAFeature(ILFFeature* feature);

	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual const char* GetName()
	{
		return "TLFAFeature";
	}
};

/*
	sigma feature 
*/
class TLFSFeature : public ILFFeature
{
public:
	TLFSFeature();
	TLFSFeature(int sxbase, int sybase, int wbase, int hbase);
	TLFSFeature(ILFFeature* feature);

	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual const char* GetName()
	{
		return "TLFSFeature";
	}
};

/*
	SA - feature 
*/
class TLFSAFeature : public ILFFeature
{
public:
	TLFSAFeature();
	TLFSAFeature(int sxbase, int sybase, int wbase, int hbase);
	TLFSAFeature(ILFFeature* feature);

	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual const char* GetName()
	{
		return "TLFSAFeature";
	}
};



/*
	horizontal feature with norm 
*/
class TLFHFeature : public ILFFeature
{
public:
	TLFHFeature();
	TLFHFeature(ILFFeature* feature);
	TLFHFeature(int sxbase, int sybase, int wbase, int hbase);

	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual awpRect GetRect();

	virtual const char* GetName()
	{
		return "TLFHFeature";
	}
};
/*
	horizontal fetature without norm
*/
class TLFHAFeature : public TLFHFeature
{
public:
	TLFHAFeature();
	TLFHAFeature(ILFFeature* feature);
	TLFHAFeature(int sxbase, int sybase, int wbase, int hbase);


	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);
	virtual const char* GetName()
	{
		return "TLFHAFeature";
	}
};

/*
	vertical feature 
*/
class TLFVFeature : public ILFFeature
{
public:
	TLFVFeature();
	TLFVFeature(ILFFeature* feature);
	TLFVFeature(int sxbase, int sybase, int wbase, int hbase);

	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual awpRect GetRect();

	virtual const char* GetName()
	{
		return "TLFVFeature";
	}
};
/*
horizontal fetature without norm
*/
class TLFVAFeature : public TLFVFeature
{
public:
	TLFVAFeature();
	TLFVAFeature(ILFFeature* feature);
	TLFVAFeature(int sxbase, int sybase, int wbase, int hbase);


	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);
	virtual const char* GetName()
	{
		return "TLFVAFeature";
	}
};
/*
	Diagonal feature 
*/
class TLFDFeature : public ILFFeature
{
public:
	TLFDFeature();
	TLFDFeature(ILFFeature* feature);
	TLFDFeature(int sxbase, int sybase, int wbase, int hbase);

	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual awpRect GetRect();

	virtual const char* GetName()
	{
		return "TLFDFeature";
	}
};

/*
	Diagonal feature without norm
*/
class TLFDAFeature : public TLFDFeature
{
public:
	TLFDAFeature();
	TLFDAFeature(ILFFeature* feature);
	TLFDAFeature(int sxbase, int sybase, int wbase, int hbase);

	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

		virtual const char* GetName()
	{
		return "TLFDAFeature";
	}
};

/*
	Center frature 
*/
class TLFCFeature : public ILFFeature
{
public:
	TLFCFeature();
	TLFCFeature(ILFFeature* feature);
	TLFCFeature(int sxbase, int sybase, int wbase, int hbase);

	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual awpRect GetRect();

	virtual const char* GetName()
	{
		return "TLFCFeature";
	}
};

class TLFCAFeature : public TLFCFeature
{
public:
	TLFCAFeature();
	TLFCAFeature(ILFFeature* feature);
	TLFCAFeature(int sxbase, int sybase, int wbase, int hbase);

	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual const char* GetName()
	{
		return "TLFCAFeature";
	}
};

/*
	Local Binary Pattern (LBP) feature 
*/
class TLFLBPFeature : public ILFFeature
{
protected:
	int  CalcValue(awpImage* pImage, double avg = 0);
public:
	TLFLBPFeature();
	TLFLBPFeature(ILFFeature* feature);
	TLFLBPFeature(int sxbase, int sybase, int wbase, int hbase);

	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual awpRect GetRect();

	virtual const char* GetName()
	{
		return "TLFLBPFeature";
	}
};


class TLFColorSensor : public ILFFeature
{
public:
	TLFColorSensor();
	TLFColorSensor(TLFColorSensor* sensor);
	TLFColorSensor(AWPWORD sx, AWPWORD sy, AWPWORD xbase, AWPWORD ybase);
	/*
	calc features value
	*/
	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual const char* GetName()
	{
		return "TLFColorSensor";
	}
};

class TLFColorSensor9Bit : public ILFFeature
{
public:
	TLFColorSensor9Bit();
	TLFColorSensor9Bit(TLFColorSensor9Bit* sensor);
	TLFColorSensor9Bit(AWPWORD sx, AWPWORD sy, AWPWORD xbase, AWPWORD ybase);
	/*
	calc features value
	*/
	virtual unsigned int      uCalcValue(TLFImage* pImage);
	virtual double            fCalcValue(TLFImage* pImage);

	virtual const char* GetName()
	{
		return "TLFColorSensor9Bit";
	}
};

//---------------------------------------------------------------------------
// ������ �������������� Census ��� ������������� �����������
class TCSSensor : public ILFFeature
{
protected:
	// ���������� �������� ��������.
	// ���������� �������� [0..511]
	int  CalcValue(awpImage* pImage, double avg = 0);
public:
	TCSSensor();
	TCSSensor(TCSSensor* sensor);
	TCSSensor(const TCSSensor& Sensor);
	TCSSensor(int sx, int sy, int uw, int uh);

	virtual awpRect GetRect();

	virtual unsigned int     uCalcValue(TLFImage* pImage);
	virtual double           fCalcValue(TLFImage* pImage);

	TCSSensor& operator = ( TCSSensor& Sensor);

	virtual const char* GetName()
	{
		return "CSFeature";
	}
};
//todo: ����� ���� ������� � �������, ������ ����� ����� �� ������� ���������� ������.
 inline double CalcSum(double* pix, int x, int y, int w, int h, int ww )
{
	double* p = pix + x + (y)*ww;

	h = h*ww;

	return (p[0] + p[w + h] - p[h] - p[w]);
}

 class TLFFeatureList : public TLFObjectList
 {
 public:
	 TLFFeatureList();
	 const char* FeatureName(int index);
 };

 /** @} */ /*  end of LFFeatures group */
#endif
