// TETRIS_in_WTLView.cpp : implementation of the CTETRIS_in_WTLView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "TETRIS_in_WTLView.h"
#include <atltypes.h>

BOOL CTETRIS_in_WTLView::PreTranslateMessage(MSG* pMsg)
{
	pMsg;
	return FALSE;
}

LRESULT CTETRIS_in_WTLView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);

	//TODO: Add your drawing code here

	return 0;
}

LRESULT CTETRIS_in_WTLView::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{

	return 0;
}

LRESULT CTETRIS_in_WTLView::OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	SetTimer(1, _currentTimerFreq);
	for (int i = 0; i < 5;++i)
	{
		_textButtonPosition[i] += CRect{ 0,-BUTTON_HEIGHT,0,BUTTON_HEIGHT };
		_textButtons[i].MoveWindow(_textButtonPosition[i]);
		if (_textButtonPosition[i].top > 500)
		{
			_textButtons[i].DestroyWindow();
			SummonTextBtn(i);
		}
	}
	return 0;
}

LRESULT CTETRIS_in_WTLView::OnCommand(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if (uMsg != 273)
		return 0;

	switch (wParam)
	{
	case 0:
		Beep(524, 100);
		break;
	case 1:
		Beep(588, 100);
		break;
	case 2:
		Beep(660, 100);
		break;
	case 3:
		Beep(698, 100);
		break;
	case 4:
		Beep(784, 100);
		break;
	default:
		break;
	}
	_textButtons[wParam].DestroyWindow();
	SummonTextBtn(wParam);
	return 0;
}

void CTETRIS_in_WTLView::StartGame()
{
	if (_isInGame)
		return;
	_isInGame = true;
	for (auto i : { 0,1,2,3,4 })
		SummonTextBtn(i);
	_currentTimerFreq = 700;
	SetTimer(1, _currentTimerFreq);

}

void CTETRIS_in_WTLView::SummonTextBtn(int btnNum)
{
	auto startPos = btnNum*(BUTTON_WIDTH + 20) + 30;
	_textButtonPosition[btnNum] = { startPos, 0, startPos + BUTTON_WIDTH, 30 };
	_textButtons[btnNum].Create(m_hWnd, _textButtonPosition[btnNum], nullptr, WS_VISIBLE | WS_CHILD, 0, btnNum);
}
