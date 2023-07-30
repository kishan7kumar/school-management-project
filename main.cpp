#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
#include<fstream.h>
struct marks_criteria
{
 int sc_min,com_min,arts_min, seat_sc, seat_com, seat_arts;
}crit;

struct administrator
{
	char user_name[10];
	char password[10];
}admin;
class student
{
 char name[20];
 int regno,m_eng,m_math,m_sc,m_sst,m_lang;
 int pref_code,stream;

	public:
	  void new_file();
	  void input_data();
	  void allot_stream();
	  int get_stream();
	  void display();
	  int show_per()
	  {
		 return((m_eng+m_math+m_sc+m_sst+m_lang)/5);
	  }
};
void welcome();
void menu();
int  verify_password();
void assign_user();
void clear();
void input_criteria();
void read_criteria();
void read_student();
void create_eligible_sc();
void create_eligible_com();
void create_eligible_arts();
void read_eligible_sc();
void read_eligible_com();
void read_eligible_arts();
char * stream_name(int strm);
void select_list( char *in_file, char *out_file);
void thanks();

student s;
void main()
{

	clrscr();
	welcome();

fstream fin, fout;
fstream fsc, fcom, farts;
int opt=1, ch;

while(opt!=8)
		 {
		 cout<<"\n\t\t============= MAIN MENU =============\n";
		 cout<<"\n\n\t\t[1] CREATE OR MODIFY ADMISSION";
		 cout<<"\n\n\t\t[2] ENTER STUDENT DATA";
		 cout<<"\n\n\t\t[3] ALLOTMENT OF STREAM";
		 cout<<"\n\n\t\t[4] DISPLAY CRITERIA FOR SELECTION";
		 cout<<"\n\n\t\t[5] DISPLAY ALLOTMENT OF STUDENT'S STREAM";
		 cout<<"\n\n\t\t[6] DISPLAY ALL STUDENT'S REGISTERED";
		 cout<<"\n\n\t\t[7] DISPLAY MERIT LIST";
		 cout<<"\n\n\t\t[8] QUIT";
		 cout<<"\n\t\t========================================\n";
		 cout<<"\n\n\t\tEnter your choice: ";
		 cin>>opt;
		 switch(opt)
		 {
	case 1: clrscr();
			int p;
		  assign_user();
		  p=verify_password();
		  if(p==0)
		  {
			  input_criteria();
		  }
			 else
		  {
			  cout<<"\n\tyou are not a valid user";
			  cout<<"\n\tyou dont have the authority to Create admission criteria\n\n";
		  }

		  break;

case 2:
		 int option;
		 clrscr();
		 cout<<"\n \t\t    ******** STUDENT DATA ******* \n\n\n\t * To Create a new student information file press 1 \n\n\t * To append to the existing student information file press 2 ";
		 cin>>option;
		 if(option==1)
		 {
	  s.new_file();
	  }
	  else
	  {
		 s.input_data();
	  }
		break ;
case 3:
	clrscr();

	fin.open("student" ,ios::in|ios::out);

	fsc.open("elig_sc",ios::out);
	fcom.open("eligcom",ios::out);
	farts.open("eligart",ios::out);

	while(fin.read((char*)& s,sizeof(s)))
	{
			s.allot_stream();
			s.get_stream();
		cout<<"\nApplication Rejected. Not Eligible\n";

			if(s.get_stream()==1)
		 fsc.write((char*)& s,sizeof(s));

			if(s.get_stream()==2)
		 fcom.write((char*)& s,sizeof(s));


			if(s.get_stream()==3)
		 farts.write((char*)& s,sizeof(s));
		 }
		 fin.close();
		 fsc.close();
		 fcom.close();
		 farts.close();
		 cout<<"\n*****************************";
		 cout<<"\n\n\tSTREAM ALLOCATION DONE.";
		 cout<<"\n*****************************";
		 break;

case 4:read_criteria();
		 clrscr();
		 cout<<"the citeria are \n Sc:"<<crit.sc_min;
		 cout<<"\n Com:"<<crit.com_min;
		 cout<<"\n Arts:"<<crit.arts_min;

		 break;

case 5: clrscr();
		 cout<<"*************************** STUDENT ALLOTMENT ***********************";
		 cout<<"\n\n\t Enter 1 for Science\n\t Enter 2 for Commerce\n\t Enter 3 for Arts\n :";
		 cin>>ch;
		 if(ch==1)
		read_eligible_sc();
		 if(ch==2)
		read_eligible_com();
		 if(ch==3)
		read_eligible_arts();
		 break;
case 6:    clrscr();
		read_student();
		break;
case 7: clrscr();
		 {
		char c;
		int k=1;
		cout<<"\n*******************************";
		cout<<"\n*******************************";
		cout<<"\n      MERIT  LIST";
		cout<<"\n      ===========";
		cout<<"\n\tEnter 1 for Merit List of Science";
		cout<<"\n\tEnter 2 for Merit List of Commerce";
		cout<<"\n\tEnter 3 for Merit List of Arts";
		cout<<"\n********************************";
		cout<<"\n********************************";
		cout<<"\n\nenter your choice - ";    cin>>k;
		if (k==1)
		{
			 select_list("elig_sc","sell_sc");
			 fin.open("sell_sc",ios::in);
		}
		if (k==2)
		{
		select_list("eligcom","sellcom");
		fin.open("sellcom",ios::in);
		}
		if (k==3)
		{
		select_list("eligart","sellart");
		fin.open("sellart",ios::in);
		}
		if(k>=1 && k<=3)
		{

			while(fin.read((char*)& s,sizeof(s)))
			{
			s.display();

			cout<<"\n\t Continue (y/n)?";
				cin>>c;
				if(c=='n')
				  break;
			}
		 }
		 fin.close();
		 fin.close();
		 fin.close();
	break;
	}
case 8:
	thanks();
	break;
		}
	 }
}


void assign_user()
{
		strcpy(admin.user_name, "kishan");
		strcpy(admin.password, "kishan");

}
int verify_password()
{
	 char u_name[10];
	 char u_pwd[10], temp[2];
	 int x=1;
	 cout<<"\n\nEnter user name :";
	 cin>>u_name;
	 cout<<"\nEnter Password :";
	 cin>>u_pwd;
	 x=strcmp(admin.user_name,u_name);
	 if(x==0)
	 {
	x=strcmp(admin.password,u_pwd);

	 }
	 cin.getline(temp,2);
	 return(x);

}
void student::allot_stream()
{
		int per=(m_eng+m_math+m_sc+m_sst+m_lang)/5;
		read_criteria();

		switch(pref_code)
		{
	  case 1:
			if(per>=crit.sc_min)
			stream=pref_code;
			else
			stream=0;
			break;
	  case 2:
			if(per>=crit.com_min)
			stream=pref_code;
			else
			stream=0;
			break;
	  case 3:
			if(per>=crit.arts_min)
			stream=pref_code;
			else
			stream=0;
			break;
		 }
}
int student::get_stream()
{
	 return(stream);
}


void input_criteria()
{
	  fstream fout;
	  fout.open("criteria" ,ios::in|ios::out);
	  cout<<"\nEnter the required marks for Science stream(in percentage) : ";
	  cin>>crit.sc_min;
	  cout<<"\nEnter no. of seats for Science stream : ";
	  cin>>crit.seat_sc;
	  cout<<"\nEnter the required marks for Commerce stream(in percentage) : ";
	  cin>>crit.com_min;
	  cout<<"\nEnter no. of seats for Commerce stream : ";
	  cin>>crit.seat_com;
	  cout<<"\nEnter the required marks for Arts stream(in percentage) : ";
	  cin>>crit.arts_min;
	  cout<<"\nEnter no. of seats for Arts stream : ";
	  cin>>crit.seat_arts;
	  fout.write((char*)& crit,sizeof(crit));
	  fout.close();
}

void read_criteria()
{
	  fstream fin;
	  fin.open("criteria", ios::in);
	  fin.read((char*)& crit,sizeof(crit));
	  fin.close();

}

void student::input_data()
{   clrscr();
	  fstream fin;
	  fin.open("student",ios::app|ios::out);
	  char t[2], ans;
	  while(1)
	  {
		cout<<"\nEnter the name of the student :";
		gets(name);
		cout<<"\n\nEnter the roll no of the student:";
		cin>>regno;
		cout<<"\n\nEnter marks in Eng:";
		cin>>m_eng;
		 cout<<"\n\nEnter marks in maths :";
		 cin>>m_math;
		 cout<<"\n\nEnter marks in science :";
		 cin>>m_sc;
		 cout<<"\n\nEnter marks in sst :";
		 cin>>m_sst;
		 cout<<"\n\nEnter marks in language :";
		 cin>>m_lang;
		cout<<"============STREAM PREFERED?===========\n";
		cout<<"\t"<<"[1] for science\n";
		cout<<"\t"<<"[2] for commerce\n";
		cout<<"\t"<<"[3] for arts";
		cout<<"\n====================================\n\tEnter your prefered code :";
		cin>>pref_code;
		stream=-1;
		fin.write((char*)&s, sizeof(s));
		cin.getline(t,2);
		cout<<"\n\tEnter More Student? (y/n)";
		cin>>ans;
		if(ans=='n')
	  break;
		}
		fin.close();
}
void student::new_file()
{    clrscr();
		fstream fin;
		fin.open("student",ios::out);
		char t[2], ans;
		while(1)
		{
		 cout<<"\nEnter the name of the student :";
		 gets(name);
		 cout<<"\n\nEnter the roll no of the student :";
		 cin>>regno;
		 cout<<"\n\nEnter marks in English :";
		 cin>>m_eng;
		 cout<<"\n\nEnter marks in maths :";
		 cin>>m_math;
		 cout<<"\n\nEnter marks in science :";
		 cin>>m_sc;
		 cout<<"\n\nEnter marks in sst :";
		 cin>>m_sst;
		 cout<<"\n\nEnter marks in language :";
		 cin>>m_lang;
		 cout<<"\n\n=============== STREAM PREFERED ===========\n";
		 cout<<"\t"<<"[1] for Science\n";
		 cout<<"\t"<<"[2] for Commerce\n";
		 cout<<"\t"<<"[3] for Arts ";
		 cout<<"\n=======================================\n\tENTER PREFERED CODE : ";
		 cin>>pref_code;
		 stream=-1;
		 fin.write((char*)&s, sizeof(s));
		 cin.getline(t,2);
		 cout<<"\n\tENTER MORE STUDENT? (y/n)";
		 cin>>ans;
		 if(ans=='n')
	break;
		 }
		 fin.close();
}
void student::display()
{      cout<<"\n \t        The Following Sudents are Registered ";
		cout<<"\n=====================================\n";
		cout<<"\n\tSTUDENT NAME         : " <<name;
		cout<<"\n\tREGISTRATION NO.     : "<<regno;
		cout<<"\n\tPERCENTAGE OF MARKS  : "<<((m_eng+m_math+m_sc+m_sst+m_lang)/5)<<"%";
		cout<<"\n\tSTREAM APPLIED FOR   : "<<stream_name(pref_code);
		cout<<"\n=====================================\n";
}
void read_student()
{
	  fstream fin;
	  char c;
	  fin.open("student", ios::in);
	  while(fin.read((char*)& s,sizeof(s)))
	  {
		s.display();
		cout<<"\n\tPress any no. to continue ";
		cin>>c;
		cout<<"\n";
	  }
	  fin.close();
}

void read_eligible_sc()
{
	 char ans;
	 fstream fout;
	 fout.open("elig_sc",ios::in);
	 fout.seekg(0);
	 while(fout.read((char*)& s,sizeof(s)))
	 {
	 s.display();
	 cout<<"\n\t Continue (y/n)?";
	 cin>>ans;
	 if(ans=='n')
	  break;

	 }
	 fout.close();

}
void read_eligible_com()
{
		char ans;
		fstream fout;
		fout.open("eligcom",ios::in);

		while(fout.read((char*)& s,sizeof(s)))
		{
		  s.display();
		  cout<<"\n\tContinue (y/n)?";
		  cin>>ans;
		  if(ans=='n')
			break;
		}
		fout.close();
}

void read_eligible_arts()
{
		 char ans;
		 fstream fout;
		 fout.open("eligart",ios::in);

		 while(fout.read((char*)& s,sizeof(s)))
		 {
	  s.display();
	  cout<<"\n\t Continue (y/n)?";
	  cin>>ans;
	  if(ans=='n')
		 break;
		 }
		 fout.close();
}
void clear()
{
}
char *stream_name(int strm)
{
    switch(strm)
    {
    case -1:
	     return("Not assigned");
    case 0:
	     return("nill");
    case 1:
	     return("Science");
    case 2:
	     return("Commerce");
    case 3:
	     return("Arts");
	     default:
	       return("None");
    }
}
void select_list( char *in_file, char *out_file)
{
      fstream sel, fin;
      int n=0,i,j;
      student s1[100], t;

	      sel.open(out_file, ios::out);
	      fin.open(in_file, ios::in);
	      while(fin.read((char*)& s1[n],sizeof(s)))
	      {
		n++;

			} clrscr();
			cout<<"\nNo of eligible students ="<<n<<"\n";
			for(i=0;i<n;i++)
			{
		  for(j=i+1;j<=n;j++)
		  {
				if(s1[i].show_per()<s1[j].show_per())
				{
				  t=s1[j];
				  s1[j]=s1[i];
				  s1[i]=t;
				 }
		  }
			}
			for(i=0;i<n;i++)
			{
		  sel.write((char*)& s1[i],sizeof(s));
			 }
		 sel.close();
		 fin.close();

}
void welcome()
  {
	 clrscr();
	 int z;

  cout<<"\n\t&&      &&  &&&&&&&  &&       &&&&&&&  &&&&&&  &&&&   &&&&  &&&&&&&";
  cout<<"\n\t&&      &&  &&       &&       &&       &&  &&  &&  &&&  &&  &&     ";
  cout<<"\n\t&&  &&  &&  &&&&&    &&       &&       &&  &&  &&  &&&  &&  &&&&&  ";
  cout<<"\n\t&&  &&  &&  &&       &&       &&       &&  &&  &&       &&  &&     ";
  cout<<"\n\t&&&&&&&&&&  &&&&&&&  &&&&&&&  &&&&&&&  &&&&&&  &&       &&  &&&&&&&";
  cout<<"\n\n\n(******** COMPUTER SCIENCE PROJECT ON SCHOOL MANAGEMENT ********)";
  cout<<"\n\n\t\t\t\t     BY";
  cout<<"\n\n\t\t\t* KISHAN KUMAR *";
	 cout<<"\n\n\n Press any number and 'Enter' to continue:";
    cin>>z;
}
void thanks()
   {   int w;
    clrscr();
	 cout<<"\n\n\n\n\n\n\t**********  THANK YOU  ********";
	 cout<<"\n\n\t   press any number and 'Enter' to exit";
    cin>>w;
   }
