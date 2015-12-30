#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define  PLOG(a) log(#a##"= (%f,%f)",a.x,a.y);
#define ILOG(a) log(#a##" = %d",a);
#define FLOG(a) log(#a##" = %f",a);
#define SLOG(a) log(#a##" = %s",a);
#define FNAME log("%s",__FUNCTION__);
#define COUNT log("count = %d",MyTool::count++);


class MyTool: public Layer
{
public:

	

	static int count;

	static int funcount;

	//static int funCount((*fun));

	bool init();

	MyTool(void);
	~MyTool(void);

	void update(float dt);
	void setControlNode(Node *nd);

	Node* controlNode;
	float tcx;
	float tcy;


	static MyTool* getInstance();

	CREATE_FUNC(MyTool);

	

private:

	static MyTool *instance;

};

