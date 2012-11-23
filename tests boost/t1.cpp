
#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

void workerFunc()
{
   for(int i=0; i<10000000000000;i++){
   
   }
	
}

int main(int argc, char* argv[])
{
    std::cout << "main: startup" << std::endl;
	std::cout<< boost::thread::hardware_concurrency() <<std::endl;
    boost::thread workerThread(workerFunc);
	boost::thread workerThread2(workerFunc);
	boost::thread workerThread3(workerFunc);
	boost::thread workerThread4(workerFunc);
	
	workerThread.join();
	workerThread2.join();
	workerThread3.join();
	workerThread4.join();

    std::cout << "main: waiting for thread" << std::endl;

    

    std::cout << "main: done" << std::endl;

    return 0;
}
