#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string.h>
using namespace std;

int const VAR_CNT='z'-'a'+1;
int const MAX_LINE_LENGTH=1024;
int const MAX_FILE_NAME=256;

int vars[VAR_CNT];
bool defined[VAR_CNT];

void ignore_spaces (char * &line)
{
	while (*line && isspace(*line)) ++line;
}

void init()
{
	char file_name[MAX_FILE_NAME];
	cout<<"Enter the name of the input file : ";
	cin.getline(file_name,MAX_FILE_NAME);
	file.open(file_name);
	if (!file)
	{
		cerr<<"Can not open "<<file_name<<endl;
		exit(1);
	}
}

void start_program ()
{
	for(int i=0; i<VAR_CNT; i++)
	{
		vars[i]=0;
		defined[i]=0;
	}
}

int read_num (char * &)

void initialization (char *line)
{
	line+=3;
	ignore_spaces(line);
	defined[*line-'a']=1;
	vars[*line-'a']=read_num(line);

}

void exec_command (char *line)
{
	ignore_spaces(line);
	if(!line) return;
	if(! strncmp(line,"int",3)) initialization(line);
	ignore_spaces(line);
	if (*line<'a' || *line > 'z')
	{
		cerr<<"Incorect input! Expect a character";
		exit(1);
	}
	defined[*line-'a']=1;
	vars[*line-'a']=expresion(line);
}