#include "BmpHandler.h"

//���캯��
CBmpHandler::CBmpHandler()
{
}

//��������
CBmpHandler::~CBmpHandler()
{
}

//����ͼƬ
bool CBmpHandler::loadBmp(char* szFileName)
{
    //��bmp�ļ�
    FILE *fp = fopen(szFileName, "rb");

    //û�ж���������ʧ��
    if(!fp)return false;

    //����λͼ�ļ�ͷ�ṹ BITMAPFILEHEADER
    fseek(fp, sizeof(BITMAPFILEHEADER), 0);//BITMAPFILEHEADER��Ҫinclude<wingdi.h>

    //��ȡͼƬ��Ϣ�ṹ BITMAPINFOHEADER
    BITMAPINFOHEADER stInfoHeader;
    fread(&stInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    //��ȡͼ�����
    m_iBmpWidth = stInfoHeader.biWidth;
    m_iBmpHeight = stInfoHeader.biHeight;
    int iSize = stInfoHeader.biSizeImage;
    //��ȡÿ����λ��������һ����ռ�ֽ���
    m_iBitCount = stInfoHeader.biBitCount;
    m_iLineSize = (m_iBmpWidth*m_iBitCount/8+3)/4*4;//����ȷ������4�ı���

    if(m_iBitCount == 8)
    {
        //�ǻҶ�ͼƬ��������ɫ������ռ䣬����ɫ����ڴ�
        m_stColorTable = new RGBQUAD[256];
        fread(m_stColorTable, sizeof(RGBQUAD), 256, fp);
    }

    //����λͼ��������ռ䣬��λͼ���ݽ��ڴ�
    m_szBmpBuf = new unsigned char[m_iLineSize*m_iBmpHeight];
    fread(m_szBmpBuf, 1, m_iLineSize*m_iBmpHeight, fp);

    //�ر��ļ�
    fclose(fp);

    return true;
}

//����ͼƬ
bool CBmpHandler::saveBmpAs(char* szFileName)
{
    //û��ͼ������
    if(!m_szBmpBuf)return false;

    //��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ��ɫ���С1024����ɫͼΪ0
    int iColorTableSize = 0;
    if(m_iBitCount == 8)iColorTableSize = 1024;

    //�Զ�����д����ʽ���ļ�
    FILE* fp = fopen(szFileName, "wb");

    //���ļ�ʧ��
    if(!fp)return false;

    //����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
    BITMAPFILEHEADER stFileHeader;
    stFileHeader.bfType = 0x4D42;//bmp���ͣ�Ϊʲôͷ�ļ���û�к궨��
    stFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + iColorTableSize + (m_iLineSize*m_iBmpHeight);//bfSize��4������֮��
    stFileHeader.bfReserved1 = 0;
    stFileHeader.bfReserved2 = 0;
    stFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + iColorTableSize;//bfOffBits��ǰ3����֮��
    fwrite(&stFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);//д�ļ�ͷ���ļ�

    //����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
    BITMAPINFOHEADER stInfoHeader;
    stInfoHeader.biBitCount = m_iBitCount;
    stInfoHeader.biClrImportant = 0;
    stInfoHeader.biClrUsed = 0;
    stInfoHeader.biCompression = 0;
    stInfoHeader.biHeight = m_iBmpHeight;
    stInfoHeader.biWidth = m_iBmpWidth;
    stInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    stInfoHeader.biSizeImage = m_iLineSize*m_iBmpHeight;
    stInfoHeader.biXPelsPerMeter = 0;
    stInfoHeader.biYPelsPerMeter = 0;
    fwrite(&stInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    //����ǻҶ�ͼ������ɫ��д���ļ�
    if(m_iBitCount == 8)fwrite(m_stColorTable, sizeof(RGBQUAD), 256, fp);

    //дλͼ���ݽ��ļ�
    fwrite(m_szBmpBuf, m_iLineSize*m_iBmpHeight, 1, fp);

    //�ر��ļ�
    fclose(fp);

    return true;
}

//�������ȣ�������Χ-255~255
bool CBmpHandler::change_brightness(int iValue)
{
    //û��ͼƬ��Դ
    if(!m_szBmpBuf)return false;

    //����������Χ
    if(iValue < -255 || iValue > 255)return false;

    for(int i=0;i<m_iBmpHeight;i++)
    {
        for(int j=0;j<m_iBmpWidth;j++)
        {
            //������������
            for(int k=0;k<3;k++)
            {
                //�޸�rgbֵ����int��ʱ������ֹԽ��
                int iTmp = (int)m_szBmpBuf[i*m_iLineSize+j*3+k];
                iTmp += iValue;
                if(iTmp < 0)iTmp = 0;
                if(iTmp > 255)iTmp = 255;
                m_szBmpBuf[i*m_iLineSize+j*3+k] = (char)iTmp;
            }
        }
    }
    return true;
}
