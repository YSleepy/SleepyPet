#include<QApplication>

#include "SleepyPetTest.h"

int main(int argc,char*argv[])
{
	QApplication application(argc,argv);
	//SleepyPet sleepy_pet;
	
	SleepyPetTest sleepy_pet;
	sleepy_pet.show();
	
	
	return application.exec();
}
