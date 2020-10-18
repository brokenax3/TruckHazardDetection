#include <wiringPi.h>
#include <iostream>
#include <fstream>

int ldrtime();
using namespace std;
long brightness;
int prevstate = -1;
int currentstate = 0;

int main(){
	
	while(1){
		brightness = 0;
		// Get average of 10 values to prevent spikes and add some delay
		for(int i = 0; i < 5; i++){
			brightness += ldrtime();
		}
		
		brightness = brightness/5;
		//cout << brightness << endl;
		if(brightness < 1200000){
			
			currentstate = 1;	// Bright
		}else{
			
			currentstate = 0;	// Dark
		}
		
		if(prevstate != currentstate){
			//cout << "Wrote : " << currentstate << endl;
			
			ofstream myfile;
			myfile.open("ledLeft.txt");
			if(myfile.is_open()){
				printf("Wrote : %d\n", currentstate);
				myfile << currentstate << endl;
			}
			myfile.close();
			prevstate = currentstate;
		}
	}
	return 0;

}	

int ldrtime(){
	int count = 0;
	wiringPiSetup();

	pinMode(7,OUTPUT);
	digitalWrite(7,LOW);

	delay(10);

	pinMode(7,INPUT);

	while(digitalRead(7) == 0){
		count++;

	}

	return count;
}
