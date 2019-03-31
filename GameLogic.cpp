#include<cstdlib>
#include<ctime>
#include"GameLogic.h"
#include"string"
USING_NS_CC;
using namespace ui;
using namespace std;
int num = 0;
bool secondTime = false;
Card* c1 = nullptr;
Card* c2 = nullptr;
Button* btn1 = nullptr;
Button* btn2 = nullptr;

Table* Table::mIns = nullptr;

Card::Card() {
	m_iIndex = num++;
}

Table::Table() {
	srand(time(nullptr));

	mIns = this;
	m_iRow = 4;
	m_iColumn = 4;
	c1 = nullptr;
	c2 = nullptr;
	m_iCorrectCnt = 0;

	m_cCardCnt = new Card*[m_iRow];
	for (int i = 0; i < m_iRow; i++) {
		m_cCardCnt[i] = new Card[m_iColumn];
	}
}

bool Table::init() {
	if (!Layer::init()) {
		return false;
	}

	for (int i = 0; i < m_iRow; i++) {
		for (int j = 0; j < m_iColumn; j++) {
			swap(m_cCardCnt[i][j], m_cCardCnt[rand() % m_iRow][rand() % m_iColumn]);
		}
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//¥d¤ù
	m_CardBtn = new Button**[m_iRow];
	for (int i = 0; i < m_iRow ; i++) {
		m_CardBtn[i] = new Button*[m_iColumn];
		for (int j = 0; j < m_iColumn; j++) {
			m_CardBtn[i][j] = Button::create("CardBack.jpg", "CardBackSelected.jpg ", "Card" + to_string(m_cCardCnt[i][j].m_iIndex / 2) + ".jpg");
			m_CardBtn[i][j]->setPosition(Vec2(origin.x + 130 + j * 75, origin.y + visibleSize.height - 50 - i * 70));
			m_CardBtn[i][j]->addTouchEventListener(CC_CALLBACK_2(Table::CardBtnTouch, Table::mIns));
			m_CardBtn[i][j]->setVisible(false);
			m_CardBtn[i][j]->setUserData(&m_cCardCnt[i][j]);
			this->addChild(m_CardBtn[i][j], 5);
		}
	}

	return true;
}

void Table::CardBtnTouch(Ref* sender, Widget::TouchEventType event_type) {
	if (event_type == Widget::TouchEventType::ENDED) {
		if (!secondTime) {
			btn1 = (Button*)sender;
			btn1->setEnabled(false);
			c1 = (Card*)btn1->getUserData();
			secondTime = true;
		}
		else {
			btn2 = (Button*)sender;
			btn2->setEnabled(false);
			c2 = (Card*)btn2->getUserData();
			secondTime = false;
			TouchEnabledAllCardBtn(false);
			this->scheduleOnce(schedule_selector(Table::UpdateTimer), 0.5f);
		}
	}
	else {

	}
}

void Table::startGame(bool swi) {
	for (int i = 0; i < m_iRow; i++) {
		for (int j = 0; j < m_iColumn; j++) {
			m_CardBtn[i][j]->setVisible(swi);
			m_CardBtn[i][j]->setEnabled(swi);
		}
	}
}

void Table::UpdateTimer(float dt) {
	if (c1->m_iIndex / 2 == c2->m_iIndex / 2) {
		m_iCorrectCnt++;

		if (win()) {
			m_iCorrectCnt = 0;
			startGame(false);
			MyUI::mIns->setTitleWord("You Win!!");
			MyUI::mIns->setSubtitleWord("Congratulations~");
			MyUI::mIns->setStartBtnWord("Again?");
			MyUI::mIns->visTitle(true);
			MyUI::mIns->visStartQuitBtn(true);
		}
	}
	else {
		btn1->setEnabled(true);
		btn2->setEnabled(true);
	}
	TouchEnabledAllCardBtn(true);
}

void Table::TouchEnabledAllCardBtn(bool ena) {
	for (int i = 0; i < m_iRow; i++) {
		for (int j = 0; j < m_iColumn; j++) {
			m_CardBtn[i][j]->setTouchEnabled(ena);
		}
	}
}

bool Table::win() {
	if (m_iCorrectCnt == m_iRow * m_iColumn / 2)
		return true;
	else
		return false;
}