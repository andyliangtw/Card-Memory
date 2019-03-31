#ifndef _MY_UI_h_
#define _MY_UI_h_
#include"cocos2d.h"
#include"ui\UIButton.h"
USING_NS_CC;
using namespace ui;
using namespace std;

class MyUI : public cocos2d::Layer {
public:
	static MyUI* mIns;
public:
	MyUI() : m_iScore(0) {
		mIns = this;
	}
	~MyUI() {
		mIns = nullptr;
	}

	virtual bool init();
	void StartBtnTouch(Ref* sender, Widget::TouchEventType event_type);
	void QuitBtnTouch(Ref* sender, Widget::TouchEventType event_type);
	void visStartQuitBtn(bool vis);
	void visTitle(bool vis);
	void setStartBtnWord(string str);
	void setTitleWord(string str);
	void setSubtitleWord(string str);
private:
	int m_iScore;
	Label* mTitle;
	Label* mSubtitle;
	Button* mBtnStart;
	Button* mBtnQuit;
};
#endif