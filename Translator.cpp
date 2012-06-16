#include <iostream>
#include <string.h>
#include <math.h>
#include <fstream>
#include <ctype.h> // for isspace() and isdigit()

int const VAR_CNT='z'-'a'+1;
int const MAX_Line_Length=1024;
int const MAX_File_Name=256;

int vars[VAR_CNT];
bool defined[VAR_CNT];


int temp;
char tempchar;

using namespace std;

template <class T>
class Stack;

template <class T>
class Item
{
	friend class Stack<T>;
private:
	Item(T x=0)//constructor
	{
		inf=x;
		link=NULL;
	}
	T inf;
	Item *link;
};

template <class T>
class Stack
{
public:
	Stack(T x);//constructor with parameter
	Stack();//default constructor
	Stack(const Stack<T> &);//copy constructor
	~Stack();//destructor
	Stack & operator=(const Stack<T> &);//Copy assignment operator
	void push(const T &);
	int pop(T &x);
	T top() const;
	bool empty() const;
	void print();
private:
	Item<T> *start;
	void copy(const Stack &);
	void delStack();
};

template <class T>
Stack<T>::Stack(T x)
{
	start=new Item<T>(x);
}

template <class T>
Stack<T>::Stack()
{
	start=NULL;
}

template <class T>
Stack<T>::Stack(const Stack<T> &r )
{
	copy(r);
}

template <class T>
Stack<T>::~Stack()
{
	delStack();
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T> &r)
{
	if(this != &r)//don`t have x=x
		{
			delStack();
			copy(r);
		}
	return *this;
}

template <class T>
void Stack<T>::push(const T &x)
{
	Item<T> *p=new Item<T>(x);
	p->link=start;
	start=p;
}

template <class T>
int Stack<T>::pop(T &x)
{
	Item<T> *p=start;
	if(start !=NULL)
	{
	x=start->inf;
	start=start->link;
	delete p;
	return 1;
	}
	else return 0;//unable to pop an item
}

template <class T>
T Stack<T>::top() const
{
	return (*start).inf;
}

template <class T>
bool Stack<T>::empty() const
{
	return start==NULL;
}

template <class T>
void Stack<T>::print()
{
	while(pop()!=0)
	{
		cout<<x<<endl; // going to predefine ths print() function if needed REM.!
	}
}

template <class T>
void Stack<T>::copy(const Stack<T> &r)
{
	if(r.start !=NULL)//r is not empty
	{
		Item<T> *q=r.start, *q=NULL, *s=NULL;
		start=new Item<T>;
		start->inf=p->inf;
		start-link=q;
		q=start;
		p=p->link;
		while(p !=NULL)
		{
			s=new Item<T>;
			s->inf=p->inf;
			q->link=s;
			q=s;
			p=p->link;
		}
		q->link=NULL;//the last element ponits to NULL of course ;)
	}
	else start=NULL;//if r is empty
}

template <class T>
void Stack<T>::delStack()
{
	Item<T> *p;
	while(start !=NULL)
	{
		p=start;
		start=start->link;
		delete p;
	}
}

// END OF STACK REALIZATION --------------------------------------
int t(char);

void translate(char *s1, char *s2) //s1=the old stack,  s2=the new generated stack
{
	Stack<char> st;
	st.push('(');
	char x;
	int i=-1, j=-1, n=strlen(s1);
	while (i<=n-1)
	{	
		i++;
		if( s1[i]>='0' && s1[i]<='9' )
		{
			j++;
			s2[j]=s1[i];
			
		}
		if( s1[i]>='a' && s1[i]<='z' )
		{
			if (defined[s1[i]-'a']==0)
			{
				cerr<<"Attemp using undeclared variable"<<s1[i];
				exit(1);
			}
			else
			{
				j++;
				s2[j]=vars[s1[i]-'a'];
			}
			
		}
		else
			if(s1[i]=='(') st.push(s1[i]);
			else
				if(s1[i]==')')
				{
					st.pop(x);
					while(x !='(')
					{
						j++;
						s2[j]=x;
						st.pop(x);
					}
				}
				else
					if(s1[i]=='+' || s1[i]=='-' || s1[i]=='*' || s1[i]=='/' || s1[i]=='^' || s1[i]=='%')
					{
						st.pop(x);//pop out from the stack for comparison
						while(x!='(' && t(x)<=t(s1[i]))
						{
							j++;
							s2[j]=x;
							st.pop(x);
						}
						st.push(x);
						st.push(s1[i]);
					}
	}
	st.pop(x);
	while(x !='(')
	{
		j++;
		s2[j]=x;
		st.pop(x);
	}
	j++;
	s2[j]=0;
}

int t(char c)
{
	int p;
	switch (c)
	{
	case '+': p=2; break;
	case '-': p=2; break;
	case '*': p=1; break;
	case '%': p=1; break; // <-- %
	case '/': p=1; break;
	case '^': p=0; break;
	default: p=-1;
	}
	return p;
}

int value(char *s)
{
	Stack<int> st;
	int x,y,z;
	int i=0, n=strlen(s);
	while(i<n)
	{
		if (s[i]>='0' && s[i]<='9') 
		{
			st.push( (int)s[i]-(int)'0' );
		}
		else
			if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='^' || s[i]=='%')
			{
				st.pop(y);
				st.pop(x);
				switch(s[i])
				{
				case '+': z=x+y; break; 
				case '-': z=x-y; break;
				case '*': z=x*y; break;
				case '%': z=x%y; break; // <-- %
				case '/': z=x/y; break;
				case '^': z=(int)pow ((double)x,y); break;
				}
				st.push(z);
			}
			i++;
	}
st.pop(z);
temp=z;
return z;
}


// THE READING FROM primeren.txt  ----------------------------------

void ignore_spaces (char * & line)
{
	while (*line && isspace(*line)) ++line;
}


void start_program()
{
	for(int i=0; i<VAR_CNT; i++)
	{
		vars[i]=0;
		defined[i]=0;
	}
}

int read_num (char * & line)
{
	++line; ignore_spaces(line);
	if(*line==';') return 0;
	/*
	if(*line != '=')
	{
		cerr<<"Incorect input! Expect '=' "; 
		exit(1);
	}
	*/
	++line; ignore_spaces(line);
	char s3[MAX_Line_Length];
	translate(line,s3);
	return value(s3);
}

void initialization (char * & line)
{
	line+=3; ignore_spaces(line);
	tempchar=(char)*line;    
	defined[(int)tempchar-'a']=1; cout<<"Defined  "<<*line<<endl;
	vars[(int)tempchar-'a']=read_num (line);
	//cout<<tempchar<<"->"<<vars[*line-'a']<<"stoinost "<<(int)*line<<endl; // to see  <-----------------------
		
}



void exec_command (char *line)
{
	ignore_spaces(line);
	if(!*line) return ; // if *line is the last symbol of the line 
		if (!strncmp(line,"print",5))
	{
		line+=5;
		ignore_spaces(line);
		line++;// to jump over '('
		ignore_spaces(line);
		cout<<"Print: "<<*line<<" =  "<<vars[*line-'a']<<endl;
		return;

	}
	
	if (!strncmp(line,"var",3)) initialization(line);
	else
	{
		if(*line >= 'a' && *line <= 'z')
		{
			if(defined[*line-'a']==0)
			{
				cerr<<"Attempt to use undeclared variable "<<*line;
				exit(1);
			}
			else
			{
				vars[*line-'a']=read_num(line);
			}
		}
	}


}



int main()
{
	char line[MAX_Line_Length];
	start_program();
		char file_name[MAX_File_Name];
	cout<<"Enter the name of the input file :";
	cin.getline(file_name,MAX_File_Name);
	ifstream file(file_name, ios::in);
	if (!file)
	{
		cerr<<"Can not open"<<file_name<<endl;
		exit(1);
	}
	while(file.getline(line,MAX_Line_Length)) exec_command(line);
	int n=0;
	cout<<endl<<"List all variables:"<<endl<<endl;
	for (int i=0; i<VAR_CNT;i++)
	{
		//if(defined[i])
			cout<<(char)(i+'a')<<"="<<vars[i]<<" def "<<defined[i]<<endl;
	}
	/*while(n<=VAR_CNT)
	{
	cout<<vars[n]<<" "<< defined[n]<<endl;
	n++;
	};*/
	//cout<<s3;
	return 0;
}