#ifndef BMPHANDLER_H_INCLUDED
#define BMPHANDLER_H_INCLUDED

//------------------------------------------------------------
//ͷ�ļ�
#include<stdio.h>
#include<windows.h>
#include<wingdi.h>//���ǰ�����include<windows.h>�����򱨴�

//------------------------------------------------------------
//CBmpHandler��
class CBmpHandler
{
private:
    //ͼ������
    int m_iBmpWidth;//ͼ��Ŀ�
    int m_iBmpHeight;//ͼ��ĸ�
    int m_iBitCount;//ͼ�����ͣ�ÿ����λ��
    int m_iLineSize;//ͼ��ÿ�е��ֽ���
    RGBQUAD* m_stColorTable;//��ɫ��ָ��
    unsigned char* m_szBmpBuf;//ͼ�����ݵ�ָ��

private:
    //˽�к���

public:

//----------------------------------------
//��������

    //���캯��
    CBmpHandler();
    //��������
    ~CBmpHandler();
    //����bmpͼƬ
    bool loadBmp(char* szFileName);
    //����ͼƬ
    bool saveBmpAs(char* szFileName);

//----------------------------------------
//������ͼ���������¹��������������

    //�������ȣ�������Χ-255~255
    bool change_brightness(int iValue);

};

#endif // BMPHANDLER_H_INCLUDED
