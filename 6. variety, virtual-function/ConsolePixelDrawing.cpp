#include "ConsolePixelDrawing.h"

ConsolePixelFrame::ConsolePixelFrame(int px, int py)
{
	console = GetConsoleWindow();  // 콘솔 핸들러를 받아오는 함수
	console_DC = GetDC(console);  // 콘솔의 디바이스 콘텍스트 값을 받아오는 함수
	pShapes = new Shape * [MAX_NUM_SHAPES];
	num_shapes = 0;
	capacity = MAX_NUM_SHAPES;
	pos_org_x = px;
	pos_org_y = py;
}

ConsolePixelFrame::~ConsolePixelFrame()
{
	//delete[] shapes;
	//ReleaseDC(console, console_DC);
}

void ConsolePixelFrame::addShape(Shape* pNew_shape)
{
	if (num_shapes >= capacity)  // 도형 개수가 용량을 초과하면
	{
		cout << "ConsolePixelFrame::addShape ==> Expanding capacity to " << capacity * 2 << "shapes " << endl;
		Shape** old_shapes = pShapes;
		pShapes = new Shape * [capacity * 2];  // 용량 2배로 확장
		if (pShapes == NULL)
		{
			cout << "Error in expanding dynamic array for shapes capacity "
				<< capacity * 2 << "shapes " << endl;
			exit;
		}
		for (int i = 0; i < num_shapes; i++)
		{
			pShapes[i] = old_shapes[i];  // 확장한 메모리에 기존값 복사
		}
		capacity = capacity * 2;
		delete[] old_shapes;
	}
	pShapes[num_shapes] = pNew_shape;  // 새로운 도형 추가
	num_shapes++;
}

void ConsolePixelFrame::drawShapes()
{
	cout << "Drawing " << num_shapes << " shapes :" << endl;
	if (num_shapes > 0)
	{
		for (int i = 0; i < num_shapes; i++)
			pShapes[i]->draw(*this);
	}
}

bool ConsolePixelFrame::isValidIndex(int index)
{
	if ((index < 0) || (index >= num_shapes))
	{
		cout << "Error in ConsolePixelFrame::isValidIndex : current number of shapes ("
			<< num_shapes << "), index : " << index << ") !!" << endl;
		return false;
	}
	else
		return true;
}