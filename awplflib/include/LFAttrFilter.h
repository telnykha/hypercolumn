//---------------------------------------------------------------------------
#ifndef __LF_ATTR_FILTER__
#define __LF_ATTR_FILTER__
/*
#include <string>
#include "LF.h"
#include "LFStrong.h"
#include "LFCSBoost.h"
*/
#define NAME_SIZE 32

class TCSAdaBoostSign;

class TLFAttrCascadeDetector : public ILFAttrDetector
{
protected:
	virtual bool DoClassify(TLFImage* pImage, TLFRoi* pRoi, SLFAttrResult& result);
public :
	TLFAttrCascadeDetector();
};

class TLFAttrSeriesDetector : public ILFAttrDetector
{
private:
   TLFAttrCascadeDetector    *m_infant_detector; 
   TLFAttrCascadeDetector    *m_do_6_detector; 
   TLFAttrCascadeDetector	*m_do_11_detector;
   TLFAttrCascadeDetector	*m_do_17_detector;
protected:
	virtual bool DoClassify(TLFImage* pImage, TLFRoi* pRoi, SLFAttrResult& result);
public :
	TLFAttrSeriesDetector();
	virtual ~TLFAttrSeriesDetector();
	bool Load(const char* pXmlFileName);
};

using namespace std;

typedef enum names { unknown = 0, adult, child } ClassName;
/*
        �������� ���������, ���������� �� ���� ������� ���������������
        ���� TCSStrong. ���� �� ��� ��������� ������� � ������� ��������,
        ������ � ��� ����������.
        ������� ����������� ����� �����������, ���� ��� ��������������
        ������������� �� �� ��� ���� �������. ���� ��� ��������������
        ��������� ���������� �������, �� ����� ������� �� ����������.
*/
class TCSSeparate : public ILFAttrClassifier
{
private:
    TCSStrong* m_Detector;
    TCSStrong* m_Detector1;
protected:
    virtual bool DoClassify(TLFImage* pImage, TLFRoi* pRoi, SLFAttrResult& result);
public:
    TCSSeparate();
    virtual ~TCSSeparate();
    //
    virtual void  SetThreshold1(double value);
    virtual void  SetThreshold2(double value);
	virtual const char* GetName() {return "TCSSeparate";}
    virtual ILFAttrClassifier* LoadFromNode(TiXmlElement* parent);
	virtual bool SaveToNode(TiXmlElement* parent);
};
/*
������������� (�������) ��������� TAttrCSStrongSign, ����������� �� ����� �������
�������������� ����  TCSStrongSign.
*/
class TAttrCSStrongSign : public ILFAttrClassifier
{
private:
        TCSStrongSign* m_Detector;
protected:
    virtual bool DoClassify(TLFImage* pImage, TLFRoi* pRoi, SLFAttrResult& result);
public:
        TAttrCSStrongSign();
        virtual ~TAttrCSStrongSign();
        // ��������� �������
        virtual void  SetThreshold1(double value);
        virtual void  SetThreshold2(double value);
        virtual const char* GetName () {return "TAttrCSStrongSign";}
        virtual ILFAttrClassifier* LoadFromNode(TiXmlElement* parent);
 		virtual bool SaveToNode(TiXmlElement* parent);

        TCSStrongSign* GetDetector()
        {
                return m_Detector;
        }
};

#endif // __LF_ATTR_FILTER__

