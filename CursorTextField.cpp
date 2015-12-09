#include "CursorTextField.h"    
#include "stdint.h"  
#include "stdio.h"  
#include <string.h>  
#include <malloc.h>  
#include <memory.h> 
const static float DELTA = 0.5f;  

using namespace cocos2d;  
using namespace std;  

CursorTextField::CursorTextField()  
{  
	TextFieldTTF();  

	m_pCursorSprite = NULL;  

}  

CursorTextField::~CursorTextField()  
{  

}  

void CursorTextField::onEnter()  
{  
	TextFieldTTF::onEnter();  
	listener = EventListenerTouchOneByOne::create();  
	listener->setSwallowTouches(false);  
	listener->onTouchBegan = CC_CALLBACK_2(CursorTextField::onTouchBegan, this);  
	listener->onTouchEnded = CC_CALLBACK_2(CursorTextField::onTouchEnded, this);  
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);  
	this->setDelegate(this);  
}  

CursorTextField * CursorTextField::textFieldWithPlaceHolder(Node * node , const char *placeholder, const char *fontName, float fontSize)  
{  
	auto pRet = new CursorTextField();  
	pRet->parentNode = node;  
	if (pRet && ((TextFieldTTF*)pRet)->initWithPlaceHolder(placeholder, fontName, fontSize))  
	{  
		pRet->autorelease();  
		if (placeholder)  
		{  
			pRet->setPlaceHolder(placeholder);  
		}  
		pRet->init();  
		pRet->initCursorSprite(fontSize);  
		pRet->setHorizontalAlignment(kCCTextAlignmentLeft);  
		return pRet;  
	}  
	CC_SAFE_DELETE(pRet);  
	return NULL;  
}  

bool CursorTextField::init(){  
	this->inputMaxLength = 16;  
	this->nLenCount = 0;  
	memset(codeNumType, 0, sizeof(codeNumType));  
	this->codeCur = 0;  
	this->startCur = 0;  
	this->endCur = 0;  
	inpuText = "";  
	return true;  
}  
void CursorTextField::initCursorSprite(const int mHeight)  
{  
	int column = 2;  
	int nHeight = 20;  
	int pixels[50][2];  
	for (int i = 0; i < nHeight; ++i)  
	{  
		for (int j = 0; j < column; ++j)  
		{  
			pixels[i][j] = 0xffffffff;  
		}  
	}  
	Texture2D* texture = new Texture2D();  
	texture->initWithData(pixels, 20, Texture2D::PixelFormat::RGB888, 4, mHeight, CCSizeMake(column, nHeight));  
	m_pCursorSprite = Sprite::createWithTexture(texture);  
	texture->autorelease();  
	if (m_pCursorSprite == nullptr)  
	{  
		CCLOG("NULL");  
	}  
	Size winSize = getContentSize();  
	m_pCursorSprite->setVisible(false);  
	parentNode->addChild(m_pCursorSprite);  
	m_pCursorAction = RepeatForever::create(Sequence::create(FadeOut::create(0.25f), FadeIn::create(0.25f), NULL));  
	m_pCursorSprite->runAction(m_pCursorAction);  
}  

void CursorTextField::setPosition(float &x, float &y)  
{  
	Point posi(x, y);  
	setPosition(posi);  
}  

void CursorTextField::setPosition(const Point& pos)  
{  
	TextFieldTTF::setPosition(pos);  
	// ���ù��λ��  
	if (NULL != m_pCursorSprite)  
	{  
		Size winSize = getContentSize();  
		m_cursorPos = ccp(0, 0/*winSize.height / 2*/);  
		m_cursorPos = m_cursorPos + pos;  
		m_pCursorSprite->setPosition(m_cursorPos.x, m_cursorPos.y + m_pCursorSprite->getContentSize().height / 2.0);  
	}  
}  


void CursorTextField::setCursorPositionX(float x) // ���ù��xλ��  
{  
	Point pt = getPosition(); // ��ȡ�����λ��  
	m_pCursorSprite->setPositionX(pt.x + x);  
}  
// �ѹ����ӵ��������һ��Ĳ���  
void CursorTextField::AddCursor(Node *node)  
{  
	if (NULL != node && NULL != m_pCursorSprite)  
	{  
		node->addChild(m_pCursorSprite);  
		m_pCursorSprite->setPositionY(getContentSize().height / 2.0);  
		m_pCursorSprite->runAction(m_pCursorAction);  
	}  
}  

bool CursorTextField::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)  
{  
	m_beginPos = pTouch->getLocation();  
	return true;  
}  

Rect CursorTextField::getRect()  
{  
	Size size = inputFrameSize;
	return  Rect(0, 0, size.width, size.height);  
}  

//��ȡ���������  
const char* CursorTextField::getInputText(){  
	const char* text = m_pInputText.c_str();  
	return text;  
}  

std::string CursorTextField::getInputTextStringUTF()
{
	return m_pInputText;
}

//�������������  
void CursorTextField::setInpuntText(char* text){  
	m_pInputText = text;  
	setString(text);  
	m_pCursorSprite->setPositionX(this->getPosition().x);  
	memset(codeNumType, 0, sizeof(codeNumType));  
	codeCur = 0;  
	startCur = 0;  
	endCur = 0;  
	inpuText = "";  
}  

//����������� һ���ַ�����ȳ���������� �ַ������Զ���������  
void CursorTextField::setInputSize(Size size){  
	this->inputFrameSize = size;  
}  

//�����������ʾ������ַ�����Unicode  
void CursorTextField::setInputMaxLength(float length){  
	this->inputMaxLength = length;  
}  

//�жϵ���¼����Ƿ���Ӧ�������Χ��  
bool CursorTextField::isInTextField(cocos2d::Touch *pTouch)  
{  
	return getRect().containsPoint(convertTouchToNodeSpaceAR(pTouch));  
}  

void CursorTextField::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)  
{  
	Point endPos = pTouch->getLocation();  
	// �ж��Ƿ�Ϊ����¼�  
	if (::abs(endPos.x - m_beginPos.x) > DELTA ||  
		::abs(endPos.y - m_beginPos.y))  
	{  
		// ���ǵ���¼�  
		m_beginPos.x = m_beginPos.y = -1;  
		return;  
	}  

	// �ж��Ǵ����뷨���ǹر����뷨  
	isInTextField(pTouch) ? openIME() : closeIME();  
}  

//�����ֻ�����ʱ��Ӧ�¼�  
bool CursorTextField::onTextFieldAttachWithIME(cocos2d::TextFieldTTF *pSender)  
{  
	if (m_pInputText.empty()) {  
		return false;  
	}  
	m_pCursorSprite->setPositionX(this->getPosition().x + getContentSize().width);  
	return false;  
}  

//�����������ʱ��Ӧ  
//@param pSender �����¼�����  
//@param text ��������  
//@param  �����ֽڳ���  


bool CursorTextField::onTextFieldInsertText(cocos2d::TextFieldTTF* sender, const char * text, size_t nLen)  
{  
	int j = 0 ;  
	std::string mytext = text;  
	for (j = 0; j < mytext.size();)  
	{  
		std::string sText = m_pInputText.c_str();  
		wchar_t* wText = new wchar_t[200];  
		char t[200];  
		memset(t, 0, sizeof(t));  
		strcpy(t, sText.c_str());  
		int unisize = 0;  
		int cou = utf8_to_unicode((uint8_t*)t, (uint16_t **)wText, &unisize);  
		std::string ss = split_text(mytext, 1 , j);  
		j += ss.length();  
		//���ַ����������涨ֵ ��������  
		if (cou >= inputMaxLength)  
		{  
			CC_SAFE_DELETE_ARRAY(wText);  
			return true;  
		}  
		//return true;  
		//���λس�����  
		if (ss == "\n")  
		{  
			CC_SAFE_DELETE_ARRAY(wText);  
			continue;  
		}  
		//��������������  
		m_pInputText.append(ss);  


		//�����ǰ�ַ������  
		inpuText.append(ss);  
		//��ǰ�ַ��ĳ���  
		codeNumType[codeCur++] = ss.length();  
		std::string localText = m_pInputText;  
		setString(m_pInputText);  
		//������ַ����ĳ��ȴ���ָ�����  
		if (getContentSize().width > inputFrameSize.width){  
			//���ڣ���ȡ�ַ�����ֱ���ַ����ĳ���С��ָ�����Ϊֹ  
			setString(inpuText);  
			while (getContentSize().width > inputFrameSize.width){  
				int nnLen = ss.length();  
				if (codeNumType[startCur] == 1){  
					nnLen = 1;  
				}  
				if (codeNumType[startCur] == 3){  
					nnLen = 3;  
				}  
				startCur++;  
				nLenCount += nnLen;  
				float gap = localText.size() - nLenCount;  
				inpuText = localText.substr(nLenCount, gap);  
				setString(inpuText.c_str());  
				float coWidth = getContentSize().width;  
			}  
		}  
		else{  
			//С�ڣ�ֱ��������ʾ���ַ���  
			nLenCount = 0;  
			startCur = 0;  
			setString(m_pInputText);  
		}  
		//���ù��λ��  
		m_pCursorSprite->setPositionX(this->getPosition().x + getContentSize().width);  
		CC_SAFE_DELETE_ARRAY(wText);  
		//AndroidShowtext(mychar, 1);  
	}  
	return true;  
}  


//�����������ʱ��Ӧ  
//@param pSender �����¼�����  
//@param text ɾ������  
//@param  �����ֽڳ���  

bool CursorTextField::onTextFieldDeleteBackward(cocos2d::TextFieldTTF* sender, const char * delText, size_t nLen)  
{  
	// �����ַ������ȼ�ȥnLen�ֽڳ�  
	m_pInputText.resize(m_pInputText.size() - nLen);  
	//��ǰ�ַ�����һ  
	codeNumType[codeCur--] = 0;  
	std::string localText = m_pInputText;  
	setString(m_pInputText);  
	if (getContentSize().width > inputFrameSize.width){  
		//����ָ����ȣ���ȡ�ַ�����ֱ���ַ�������С��ָ�����  
		while (getContentSize().width > inputFrameSize.width){  
			int nnLen = nLen;  
			if (codeNumType[startCur - 1] == 1){  
				nnLen = 1;  
			}  
			if (codeNumType[startCur - 1] == 3){  
				nnLen = 3;  
			}  
			nLenCount -= nnLen;  
			startCur--;  
			if (startCur <= 0)  
				startCur = 0;  
			if (nLenCount <= 0)  
				nLenCount = 0;  
			float gap = localText.size() - nLenCount;  
			const std::string text = localText.substr(nLenCount, gap);  
			setString(text);  
			inpuText = text;  
		}  
	}  
	else{  
		nLenCount = 0;  
		startCur = 0;  
		setString(m_pInputText.c_str());  
	}  
	//���ù��λ��  
	m_pCursorSprite->setPositionX(this->getPosition().x + getContentSize().width);  
	if (m_pInputText.empty()) {  
		m_pCursorSprite->setPositionX(this->getPosition().x);  
	}  
	return true;  
}  

bool CursorTextField::onTextFieldDetachWithIME(cocos2d::TextFieldTTF *pSender)  
{  
	return false;  
}  

void CursorTextField::openIME()  
{  
	m_pCursorSprite->setVisible(true);  
	setString(m_pInputText);  
	((TextFieldTTF *)this)->attachWithIME();  
}  

void CursorTextField::closeIME()  
{  
	m_pCursorSprite->setVisible(false);  
	//auto pTextField = (TextFieldTTF *)pRet;  
	((TextFieldTTF *)this)->detachWithIME();  
}  

void CursorTextField::onExit()  
{  
	TextFieldTTF::onExit();  
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);  
}  

std::string CursorTextField::split_text(std::string name, int len , int start)  
{  
	int i = start;  
	std::string str;  
	if (name[i] < 0)  
	{  
		i++;  
	}  
	//while (name[i] < 0)  
	//{  
	//  i++;  
	//  if (i - start == 2)  
	//  {  
	//      break;  
	//  }  
	//}  
	if (start == i)  
	{  
		str = name.substr(start, 1);  
	}  
	else  
	{  
		str = name.substr(start, 3);  
	}  
	//log("mysubstr   %s", str.c_str());  
	return str;  
}  

int CursorTextField::utf8_to_unicode(uint8_t *in, uint16_t **out, int *outsize)  
{  
    uint8_t *p = in;  
    uint16_t *result = NULL;  
    int resultsize = 0;  
    uint8_t *tmp = NULL;  
  
    result = (uint16_t *)malloc(strlen((char *)in) * 2 + 2); /* should be enough */  
    memset(result, 0, strlen((char*)in) * 2 + 2);  
    tmp = (uint8_t *)result;  
  
    while (*p)  
    {  
        if (*p >= 0x00 && *p <= 0x7f)  
        {  
            *tmp = *p;  
            tmp++;  
            *tmp = '\0';  
            resultsize += 1;  
        }  
        else if ((*p & (0xff << 5)) == 0xc0)  
        {  
            uint16_t t = 0;  
            uint8_t t1 = 0;  
            uint8_t t2 = 0;  
  
            t1 = *p & (0xff >> 3);  
            p++;  
            t2 = *p & (0xff >> 2);  
  
            *tmp = t2 | ((t1 & (0xff >> 6)) << 6);//t1 >> 2;  
            tmp++;  
  
            *tmp = t1 >> 2;//t2 | ((t1 & (0xff >> 6)) << 6);  
            tmp++;  
  
            resultsize += 1;  
        }  
        else if ((*p & (0xff << 4)) == 0xe0)  
        {  
            uint16_t t = 0;  
            uint8_t t1 = 0;  
            uint8_t t2 = 0;  
            uint8_t t3 = 0;  
  
            t1 = *p & (0xff >> 3);  
            p++;  
            t2 = *p & (0xff >> 2);  
            p++;  
            t3 = *p & (0xff >> 2);  
  
            //Little Endian  
            *tmp = ((t2 & (0xff >> 6)) << 6) | t3;//(t1 << 4) | (t2 >> 2);  
            tmp++;  
  
            *tmp = (t1 << 4) | (t2 >> 2);//((t2 & (0xff >> 6)) << 6) | t3;  
            tmp++;  
            resultsize += 1;  
        }  
  
        p++;  
    }  
  
    //*tmp = '\0';  
    //tmp++;  
    //*tmp = '\0';  
    //resultsize += 2;  
  
    //*out = result;  
    //*outsize = resultsize;  
    return resultsize;  
}  

int CursorTextField::unicode_to_utf8(uint16_t *in, int insize, uint8_t **out)  
{  
	int i = 0;  
	int outsize = 0;  
	int charscount = 0;  
	uint8_t *result = NULL;  
	uint8_t *tmp = NULL;  

	charscount = insize / sizeof(uint16_t);  
	result = (uint8_t *)malloc(charscount * 3 + 1);  
	memset(result, 0, charscount * 3 + 1);  
	tmp = result;  

	for (i = 0; i < charscount; i++)  
	{  
		uint16_t unicode = in[i];  

		if (unicode >= 0x0000 && unicode <= 0x007f)  
		{  
			*tmp = (uint8_t)unicode;  
			tmp += 1;  
			outsize += 1;  
		}  
		else if (unicode >= 0x0080 && unicode <= 0x07ff)  
		{  
			*tmp = 0xc0 | (unicode >> 6);  
			tmp += 1;  
			*tmp = 0x80 | (unicode & (0xff >> 2));  
			tmp += 1;  
			outsize += 2;  
		}  
		else if (unicode >= 0x0800 && unicode <= 0xffff)  
		{  
			*tmp = 0xe0 | (unicode >> 12);  
			tmp += 1;  
			*tmp = 0x80 | (unicode >> 6 & 0x00ff);  
			tmp += 1;  
			*tmp = 0x80 | (unicode & (0xff >> 2));  
			tmp += 1;  
			outsize += 3;  
		}  

	}  

	*tmp = '\0';  
	*out = result;  
	return outsize;  
}  