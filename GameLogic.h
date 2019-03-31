#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_
#include"ui\UIButton.h"

#include"MyUI.h"
USING_NS_CC;
using namespace ui;
using namespace std;

struct Card {
	int m_iIndex;
	Card();
};

class Table : public cocos2d::Layer {
private:
	int m_iRow;
	int m_iColumn;
	Card** m_cCardCnt;
	int m_iCorrectCnt;
	Button*** m_CardBtn;
public:
	static Table* mIns;
	Table();
	~Table() {
		for (int i = 0; i < m_iRow; i++)
			delete[] m_cCardCnt[i];
		delete[] m_cCardCnt;
		mIns = nullptr;
	}

	virtual bool init();
	
	void CardBtnTouch(Ref* sender, Widget::TouchEventType event_type);
	void startGame(bool swi);
	void UpdateTimer(float dt);
	void TouchEnabledAllCardBtn(bool ena);
	bool win();
};
#endif