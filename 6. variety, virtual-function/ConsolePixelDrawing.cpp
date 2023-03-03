#include "ConsolePixelDrawing.h"

ConsolePixelFrame::ConsolePixelFrame(int px, int py)
{
	console = GetConsoleWindow();  // �ܼ� �ڵ鷯�� �޾ƿ��� �Լ�
	console_DC = GetDC(console);  // �ܼ��� ����̽� ���ؽ�Ʈ ���� �޾ƿ��� �Լ�
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
	if (num_shapes >= capacity)  // ���� ������ �뷮�� �ʰ��ϸ�
	{
		cout << "ConsolePixelFrame::addShape ==> Expanding capacity to " << capacity * 2 << "shapes " << endl;
		Shape** old_shapes = pShapes;
		pShapes = new Shape * [capacity * 2];  // �뷮 2��� Ȯ��
		if (pShapes == NULL)
		{
			cout << "Error in expanding dynamic array for shapes capacity "
				<< capacity * 2 << "shapes " << endl;
			exit;
		}
		for (int i = 0; i < num_shapes; i++)
		{
			pShapes[i] = old_shapes[i];  // Ȯ���� �޸𸮿� ������ ����
		}
		capacity = capacity * 2;
		delete[] old_shapes;
	}
	pShapes[num_shapes] = pNew_shape;  // ���ο� ���� �߰�
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