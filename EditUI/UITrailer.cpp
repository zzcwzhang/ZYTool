#include "UI.h"
UITrailer::UITrailer()
{
	bStop = false;
	delayTime = 0;
	curTimeIndex = -1;
	form = nullptr;
	speed = 0;
	m_time = 0;
}

UITrailer::~UITrailer()
{
	timeLines.clear();
}

void UITrailer::loadData(DataStream *dis)
{
	this->speed = dis->readByte();
	int count = dis->readByte();
	for (int i = 0; i < count; i++)
	{
		UITimeLine *line = UITimeLine::create();
		timeLines.pushBack(line);
		line->trailer = this;
		line->loadData(dis);
	}
}

void UITrailer::updateLogic(float dt)
{
	if(bStop)
	{
		return;
	}
	if(this->delayTime > 0)
	{
		this->delayTime--;
	}
	else
	{
		if(m_time > 0)
		{
			m_time--;
			return;
		}
		m_time = speed;
		int count = timeLines.size();
		for (int i = 0; i < count; i++)
		{
			UITimeLine *line = (UITimeLine*)timeLines.at(i);
			line->updateObjNode(curTimeIndex);
		}

		for (int i = 0; i < count; i++)
		{
			UITimeLine *line = (UITimeLine*)timeLines.at(i);
			line->runScript(curTimeIndex);
		}
		curTimeIndex += 1;
	}
	
}

bool UITrailer::checkTimeIndex(short timeIndex)
{
	return m_time == speed && curTimeIndex == timeIndex;
}

void UITrailer::stop()
{
	bStop = true;
}
void UITrailer::play()
{
	bStop = false;
}

void UITrailer::setSpeed(short speed)
{
	this->speed = speed;
}
//////////////////////////////////////////////////////////////////////////
UITimeLine::UITimeLine()
{

}

UITimeLine::~UITimeLine()
{
	frames.clear();
	scriptIds.clear();
}

void UITimeLine::loadData(DataStream *dis)
{
	int index = dis->readShort();
	this->ctrl = trailer->getForm()->getControl(index);
	int count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		UITrailerFrame *frame = UITrailerFrame::create();
		frames.pushBack(frame);
		frame->line = this;
		frame->loadData(dis);
	}

	count = dis->readByte();
	for (int i = 0; i < count; i++)
	{
		int scriptId = dis->readByte();
		int timeIndex = dis->readShort();
		scriptIds.push_back(scriptId);
		scriptIds.push_back(timeIndex);
	}
}

void UITimeLine::runScript(short timeIndex)
{
	UIScriptData *data = getScriptData((int)(timeIndex));
	if(data == nullptr)
	{
		return;
	}
	if(data->checkRule(ctrl) && data->checkCdts())
	{
		data->runActs(trailer->getForm());
	}
}

void UITimeLine::updateObjNode(short timeIndex)
{
	UITrailerFrame *frame1 = nullptr;
	UITrailerFrame *frame2 = nullptr;
	frame1 = getFrame((int)(timeIndex));
	if (frame1 != nullptr)
	{
		this->ctrl->setPosition(frame1->location);
		ctrl->setRotation(frame1->rot);
		ctrl->setControlScale(frame1->scale);
		ctrl->setControlOpacity(frame1->opacity);
		ctrl->setControlColor(frame1->bkColor);
		if(ctrl->type == Type_Label ||
			ctrl->type == Type_Button||
			ctrl->type == Type_ListView)
		{
			MLabel *label = (MLabel*)ctrl;
			//UIM->setSkin(ctrl,frame1->skinIndex);
		}
		return;
	}
	//ÎÞ¹Ø¼üÖ¡
	int count = frames.size();
	for (int i = 0; i < count; i++)
	{
		UITrailerFrame* f = (UITrailerFrame*)frames.at(i);
		if (f->timeIndex > timeIndex)
		{
			frame1 = (UITrailerFrame*)frames.at(i - 1);
			frame2 = (UITrailerFrame*)frames.at(i);
			break;
		}
	}

	if (frame1 != nullptr && frame2 != nullptr)
	{
		if (frame1->frontTo == frame2->timeIndex)
		{
			float x = 0;
			float y = 0;
			if (frame2->location.x - frame1->location.y == 0.0f)
			{
				x = frame1->location.x;
			}
			else
			{
				x = (frame2->location.x - frame1->location.x) * (timeIndex - frame1->timeIndex) / (frame2->timeIndex - frame1->timeIndex) + frame1->location.x;
			}

			if (frame2->location.y - frame1->location.y == 0.0f)
			{
				y = frame1->location.y;
			}
			else
			{
				y = (frame2->location.y - frame1->location.y) * (timeIndex - frame1->timeIndex) / (frame2->timeIndex - frame1->timeIndex) + frame1->location.y;
			}
			ctrl->setPosition(x, y);

			float sx = 0; 
			float sy = 0;
			if (frame2->scale.x - frame1->scale.x == 0.0f)
			{
				sx = frame1->scale.x;
			}
			else
			{
				sx = (frame2->scale.x - frame1->scale.x) * (timeIndex - frame1->timeIndex) / (frame2->timeIndex - frame1->timeIndex) + frame1->scale.x;
			}

			if (frame2->scale.y - frame1->scale.y == 0.0f)
			{
				sy = frame1->scale.y;
			}
			else
			{
				sy = (frame2->scale.y - frame1->scale.y) * (timeIndex - frame1->timeIndex) / (frame2->timeIndex - frame1->timeIndex) + frame1->scale.y;
			}
			ctrl->setControlScale(Vec2(sx, sy));

			short opacity = 0;
			if (frame2->opacity - frame1->opacity == 0)
			{
				opacity = frame1->opacity;
			}
			else
			{
				opacity = (short)((frame2->opacity - frame1->opacity) * (timeIndex - frame1->timeIndex) / (frame2->timeIndex - frame1->timeIndex) + frame1->opacity);
			}
			ctrl->setControlOpacity(opacity);
			short rot = 0;
			if (frame2->rot - frame1->rot == 0)
			{
				rot = frame1->rot;
			}
			else
			{
				rot = (short)((frame2->rot - frame1->rot) * (timeIndex - frame1->timeIndex) / (frame2->timeIndex - frame1->timeIndex) + frame1->rot);
			}
			ctrl->setRotation(rot);

			short apha;
			if (frame2->bkColor.a - frame1->bkColor.a == 0)
			{
				apha = frame1->bkColor.a;
			}
			else
			{
				apha = (short)((frame2->bkColor.a  - frame1->bkColor.a ) * (timeIndex - frame1->timeIndex) / (frame2->timeIndex - frame1->timeIndex) + frame1->bkColor.a );
			}

			short r;
			if (frame2->bkColor.r - frame1->bkColor.r == 0)
			{
				r = frame1->bkColor.r;
			}
			else
			{
				r = (short)((frame2->bkColor.r  - frame1->bkColor.r ) * (timeIndex - frame1->timeIndex) / (frame2->timeIndex - frame1->timeIndex) + frame1->bkColor.r );
			}

			short g;
			if (frame2->bkColor.g - frame1->bkColor.g == 0)
			{
				g = frame1->bkColor.g;
			}
			else
			{
				g = (short)((frame2->bkColor.g  - frame1->bkColor.g ) * (timeIndex - frame1->timeIndex) / (frame2->timeIndex - frame1->timeIndex) + frame1->bkColor.g );
			}

			short b;
			if (frame2->bkColor.b - frame1->bkColor.b == 0)
			{
				b = frame1->bkColor.b;
			}
			else
			{
				b = (short)((frame2->bkColor.b  - frame1->bkColor.b ) * (timeIndex - frame1->timeIndex) / (frame2->timeIndex - frame1->timeIndex) + frame1->bkColor.b );
			}

			ctrl->setControlColor(Color4B(r,g,b,apha));
		}
		else
		{
			this->ctrl->setPosition(frame1->location);
			ctrl->setRotation(frame1->rot);
			ctrl->setControlScale(frame1->scale);
			ctrl->setControlOpacity(frame1->opacity);
			ctrl->setControlColor(frame1->bkColor);
			if(ctrl->type == Type_Label ||
				ctrl->type == Type_Button||
				ctrl->type == Type_ListView)
			{
				MLabel *label = (MLabel*)ctrl;
				//UIM->setSkin(ctrl,frame1->skinIndex);
			}
		}
	}
	else
	{
		frame1 = (UITrailerFrame*)frames.at(count - 1);
		this->ctrl->setPosition(frame1->location);
		ctrl->setRotation(frame1->rot);
		ctrl->setControlScale(frame1->scale);
		ctrl->setControlOpacity(frame1->opacity);
		ctrl->setControlColor(frame1->bkColor);
		if(ctrl->type == Type_Label ||
			ctrl->type == Type_Button||
			ctrl->type == Type_ListView)
		{
			MLabel *label = (MLabel*)ctrl;
			//UIM->setSkin(ctrl,frame1->skinIndex);
		}
	}
}

UITrailerFrame *UITimeLine::getFrame(int index)
{
	int count = frames.size();
	for (int i = 0; i < count; i++)
	{
		UITrailerFrame *frame = (UITrailerFrame*)frames.at(i);
		if (frame->timeIndex == index)
		{
			return frame;
		}
	}
	return NULL;
}

UIScriptData *UITimeLine::getScriptData(int timeIndex)
{
	int count = scriptIds.size();
	for (int i = 0; i < count; i += 2)
	{
		int scriptId = scriptIds[i];
		int index = scriptIds[i + 1];
		if(index == timeIndex)
		{
			return this->trailer->getForm()->getScriptData(scriptId);
		}
	}
	return nullptr;
}
//////////////////////////////////////////////////////////////////////////
UITrailerFrame::UITrailerFrame()
{

}

UITrailerFrame::~UITrailerFrame()
{

}

void UITrailerFrame::loadData(DataStream *dis)
{
	this->timeIndex = dis->readShort();
	float x = dis->readShort();
	float y = dis->readShort();
	this->location = Vec2(x,y);
	short apha = dis->readShort();
	short r = dis->readShort();
	short g = dis->readShort();
	short b = dis->readShort();
	this->bkColor = Color4B(r,g,b,apha);
	this->opacity = dis->readShort();
	this->rot = dis->readShort();
	this->skinIndex = dis->readShort();
	float sx = dis->readInt()/100.0f;
	float sy = dis->readInt()/100.0f;
	this->scale = Vec2(sx,sy);

	this->frontTo = dis->readShort();
	this->backTo = dis->readShort();
}
//////////////////////////////////////////////////////////////////////////