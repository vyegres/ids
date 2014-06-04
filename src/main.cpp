//
//  main.cpp
//  ids_head
//

#include "Core.h"

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: ./ids_head [config.cfg] \n Options:\n  stop\n");
		
		return -1;
	}
	
	Monitor app(argv);
	
	return app.start();
}
