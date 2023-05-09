#include "MineSweeper.h"

int main()
{
	MineSweeper Mine;
	while (Mine.window.isOpen())
	{
		Mine.Run();
	}
}