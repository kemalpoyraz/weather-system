#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

#define SUMMER 10
#define AUTUMN 5
#define SPRING 5
#define WINTER 1

#define FIRST 1
#define THIRD 3
#define SECOND 6

#define LOWPRESS 1
#define MILDPRESS 5
#define HIGHPRES 10

#define TEMP1 1
#define TEMP2 100
#define TEMP3 200
#define TEMP4 300
#define TEMP5 400
#define TEMP6 500
#define TEMP7 600
#define TEMP8 700
#define TEMP9 1000

void makeSuggestion(int, int);

int main()
{
    FILE* temperatureFile = fopen("temperatureEncryptedResult.txt", "r");
    FILE* pressureFile = fopen("pressureEncryptedResult.txt", "r");

    char line[5];
    int temperatureArr[120];
    int pressureArr[120];

    int i = 0;

    int avgTemp = 0;
    int avgPress = 0;
    int sumTemp = 0;
    int sumPress = 0;

    while (fgets(line, sizeof(line), temperatureFile)) {

        temperatureArr[i] = atoi(line);
        //printf("temperature = %d\n", temperatureArr[i]);
        i++;
    }

    i=0;

    while(fgets(line, sizeof(line), pressureFile)) {

        pressureArr[i] = atoi(line);
        //printf("pressure = %d\n", pressureArr[i]);
        i++;
    }

    fclose(pressureFile);
    fclose(temperatureFile);

    i = 0;
    while(i < 120)
    {
        sumTemp += temperatureArr[i];
        sumPress += pressureArr[i];
        i++;
    }

    avgTemp = sumTemp / 120;
    avgPress = sumPress / 120;

    makeSuggestion(avgTemp, avgPress);

    return 0;
}


void makeSuggestion(int avgTemp, int avgPress)
{
    int weatherConstant = 1;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (tm.tm_mon + 1 == 12 || tm.tm_mon + 1 == 1 || tm.tm_mon + 1 == 2)
    {
        weatherConstant = weatherConstant * WINTER;
    }
    else if (tm.tm_mon + 1 == 3 || tm.tm_mon + 1 == 4 || tm.tm_mon + 1 == 5)
    {
        weatherConstant = weatherConstant * SPRING;
    }
    else if (tm.tm_mon + 1 == 6 || tm.tm_mon + 1 == 7 || tm.tm_mon + 1 == 8)
    {
        weatherConstant = weatherConstant * SUMMER;
    }
    else if (tm.tm_mon + 1 == 9 || tm.tm_mon + 1 == 10 || tm.tm_mon + 1 == 11)
    {
        weatherConstant = weatherConstant * AUTUMN;
    }
    else
    {
        printf("\nError: Weather Constant at Seasons\n");
    }

    if (tm.tm_hour >= 2 && tm.tm_hour < 10)
    {
        weatherConstant = weatherConstant * FIRST;
    }
    else if (tm.tm_hour >= 10 && tm.tm_hour < 18)
    {
        weatherConstant = weatherConstant * THIRD;
    }
    else if ((tm.tm_hour >= 18 && tm.tm_hour <= 23) || (tm.tm_hour >= 0 && tm.tm_hour < 2))
    {
        weatherConstant = weatherConstant * SECOND;
    }
    else
    {
    	printf("\nError: Weather Constant at Time of Day\n");
    }

    /*if (avgPress < 985)
    {
    	weatherConstant = weatherConstant * LOWPRESS;
    }
    else if (avgPress >= 985 && avgPress < 1010)
    {
    	weatherConstant = weatherConstant * MILDPRESS;
    }
    else if (avgPress >= 1010)
    {
    	weatherConstant = weatherConstant * HIGHPRES;
    }
    else
    {
    	printf("\nError: Weather Constant at Pressure\n");
    }*/

    if(avgTemp < -10)
    {
        weatherConstant = weatherConstant * TEMP1;
    }
    else if(avgTemp >= -10 && avgTemp < 0)
    {
        weatherConstant = weatherConstant * TEMP2;
    }
    else if(avgTemp >= 0 && avgTemp < 10)
    {
        weatherConstant = weatherConstant * TEMP3;
    }
    else if(avgTemp >= 10 && avgTemp < 15)
    {
        weatherConstant = weatherConstant * TEMP4;
    }
    else if(avgTemp >= 15 && avgTemp < 20)
    {
        weatherConstant = weatherConstant * TEMP5;
    }
    else if(avgTemp >= 20 && avgTemp < 25)
    {
        weatherConstant = weatherConstant * TEMP6;
    }
    else if(avgTemp >= 25 && avgTemp < 30)
    {
        weatherConstant = weatherConstant * TEMP7;
    }
    else if(avgTemp >= 30 && avgTemp < 40)
    {
        weatherConstant = weatherConstant * TEMP8;
    }
    else if (avgTemp >= 40)
    {
    	weatherConstant = weatherConstant * TEMP9;
    }
    else
    {
    	printf("\nError: Weather Constant at Temperature");
    }

    printf("\nWeather Constant: %d\n", weatherConstant);


    if (avgPress < 985)
    {
    	if (weatherConstant < 1200)
    	{
    		system("echo 'It is cold out there, there can be a blizzard.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 1200 || weatherConstant < 3000)
    	{
    		system("echo 'It is cold out there, there can be a snow storm.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 3000 || weatherConstant < 4500)
    	{
    		system("echo 'It is like a spring night chill, can be rainy.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 4500 || weatherConstant < 6000)
    	{
    		system("echo 'Fair, can be sparse rainy.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 6000 || weatherConstant < 10000)
    	{
    		system("echo 'It feels warmish, slight possibility of rain.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 10000 || weatherConstant < 15000)
    	{
    		system("echo 'It is warm, can be drizzle.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 15000 || weatherConstant < 22000)
    	{
    		system("echo 'It is warm out there, there could be rain.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 22000 || weatherConstant < 30000)
    	{
    		system("echo 'It is overwhelmingly hot, there could be precipitation.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 30000)
    	{
    		system("echo 'It is burning hot, there could be rain.' > suggestion.txt");
    	}
    	else
    	{
    		printf("\nError: Low Pressure Suggestion!\n");
    	}
    }
    else if (avgPress >= 985 && avgPress < 1010)
    {
    	if (weatherConstant < 1200)
    	{
    		system("echo 'It is freezing out there.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 1200 || weatherConstant < 3000)
    	{
    		system("echo 'It is cold out there.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 3000 || weatherConstant < 4500)
    	{
    		system("echo 'It feels chilly, partly cloudy.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 4500 || weatherConstant < 6000)
    	{
    		system("echo 'Fair, looks stable.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 6000 || weatherConstant < 10000)
    	{
    		system("echo 'It feels warmish, possibly cloudy.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 10000 || weatherConstant < 15000)
    	{
    		system("echo 'It is warm, looks stable.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 15000 || weatherConstant < 22000)
    	{
    		system("echo 'It is warm out there.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 22000 || weatherConstant < 30000)
    	{
    		system("echo 'It is overwhelmingly hot, be cautious.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 30000)
    	{
    		system("echo 'It is burning hot, try not to go out.' > suggestion.txt");
    	}
    	else
    	{
    		printf("\nError: Mild Pressure Suggestion!\n");
    	}
    }
    else if (avgPress >= 1010)
    {
    	if (weatherConstant < 1200)
    	{
    		system("echo 'It is freezing out there, but cloudless.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 1200 || weatherConstant < 3000)
    	{
    		system("echo 'It is cold out there, there is sun.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 3000 || weatherConstant < 4500)
    	{
    		system("echo 'It feels chilly, partly sunny.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 4500 || weatherConstant < 6000)
    	{
    		system("echo 'Fair, looks sunny.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 6000 || weatherConstant < 10000)
    	{
    		system("echo 'It feels warmish, it is sunny.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 10000 || weatherConstant < 15000)
    	{
    		system("echo 'It is warm and sunny, looks stable.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 15000 || weatherConstant < 22000)
    	{
    		system("echo 'It is hot out there, try not to go out.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 22000 || weatherConstant < 30000)
    	{
    		system("echo 'It is overwhelmingly hot, feels like desert.' > suggestion.txt");
    	}
    	else if (weatherConstant >= 30000)
    	{
    		system("echo 'It is burning hot, there could be drought.' > suggestion.txt");
    	}
    	else
    	{
    		printf("\nError: Regular Pressure Suggestion!\n");
    	}
    }
    else
    {
    	printf("\nError: Suggestion!");
    }
}