#include"ui\UIButton.h"
#include"MyUI.h"
#include"GameLogic.h"
#include"string"
USING_NS_CC;
using namespace ui;
using namespace std;

MyUI* MyUI::mIns = nullptr;

bool MyUI::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//標題
	mTitle = Label::createWithTTF("Card Memory", "fonts/Chalkduster.ttf", 60);
	mTitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - mTitle->getContentSize().height - 20));
	this->addChild(mTitle, 1);

	//副標題
	mSubtitle = Label::createWithTTF("Group 4 Produced", "fonts/Chalkduster.ttf", 14);
	mSubtitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - 135));
	mSubtitle->setColor(Color3B::ORANGE);
	this->addChild(mSubtitle, 1);

	//開始鍵
	mBtnStart = Button::create();
	mBtnStart->setTitleText("Start");
	mBtnStart->setTitleFontName("fonts/Chalkduster.ttf");
	mBtnStart->setTitleFontSize(24);
	mBtnStart->setTitleColor(Color3B::RED);
	mBtnStart->setPosition(Vec2(origin.x + visibleSize.width / 2,
						origin.y + visibleSize.height / 2 - 20));
	mBtnStart->addTouchEventListener(CC_CALLBACK_2(MyUI::StartBtnTouch, MyUI::mIns));
	this->addChild(mBtnStart, 1);
	
	//結束鍵
	mBtnQuit = Button::create();
	mBtnQuit->setTitleText("Quit");
	mBtnQuit->setTitleFontName("fonts/Chalkduster.ttf");
	mBtnQuit->setTitleFontSize(24);
	mBtnQuit->setTitleColor(Color3B::RED);
	mBtnQuit->setPosition(Vec2(origin.x + visibleSize.width / 2,
						origin.y + visibleSize.height / 2 - 60));
	mBtnQuit->addTouchEventListener(CC_CALLBACK_2(MyUI::QuitBtnTouch, MyUI::mIns));
	this->addChild(mBtnQuit, 1);

	return true;
}

void MyUI::StartBtnTouch(Ref* sender, Widget::TouchEventType event_type) {
	if (event_type == Widget::TouchEventType::ENDED) {
		visStartQuitBtn(false);
		visTitle(false);
		Table::mIns->startGame(true);
	}
	else {

	}
}

void MyUI::QuitBtnTouch(Ref* sender, Widget::TouchEventType event_type) {
	if (event_type == Widget::TouchEventType::ENDED) {
		Director::getInstance()->end();
	}
	else {

	}
}

void MyUI::visStartQuitBtn(bool vis) {
	mBtnStart->setVisible(vis);
	mBtnQuit->setVisible(vis);
}

void MyUI::visTitle(bool vis) {
	mTitle->setVisible(vis);
	mSubtitle->setVisible(vis);
}

void MyUI::setTitleWord(string str) {
	mTitle->setString(str);
}

void MyUI::setSubtitleWord(string str) {
	mSubtitle->setString(str);
}

void MyUI::setStartBtnWord(string str) {
	mBtnStart->setTitleText(str);
}