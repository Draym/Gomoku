
#include "Master.h"

int	main()
{
	Master master;

	try
	{
		master.init();
		master.run();
	}
	catch (Exception e)
	{
		e.showError();
		master.quit();
		getchar();
	}
	return 0;
}