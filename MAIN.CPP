/*  GUIFileProcessingSystem_dosbox - A simple framework/template for GUI dosbox programs.
    Copyright (C) 2017  Michel Thomas

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include "guiutil.h"
#include "util.h"
#include "datastructs.h"
#include "fstream.h"
#include "ctype.h"
extern Button bt;
extern Button bt2;
extern Button bt3;
extern Button bt4;
extern TextField searchtxt;
extern TextField nametxt;
extern TextField gendertxt;
extern TextField addresstxt;
extern TextField empCattxt;
extern TextField IDtxt;
extern TextField statustxt;
extern TextField basicpaytxt;
extern TextField hratxt;
extern TextField datxt;
extern TextField dobtxt;
extern TextField mobtxt;
extern TextField yobtxt;

extern Label Id21;
extern Label Name21;
extern Label Dob21;
extern Label Gender21;
extern Label Address21;
extern Label Status21;
extern Label Basicpay21;
extern Label EmpCat21;
extern Label Hra21;
extern Label Da21;
extern Panel panel;

int active=0;
int editMode=0;

Component *activeComponent=NULL;
struct FileDat{
   Employee emp;
   int currentPosition;
	      }*editState=NULL,*searchState=NULL;
int count(int no){
 int c=0;
   while(no!=0){
      no/=10;
      c++;
		}
      return c;
		 }

void create(){
 if(editState!=NULL)
  delete editState;
  editState=NULL;
   IDtxt.label->setText("\0");
	     nametxt.label->setText("\0");

	     dobtxt.label->setText("\0");

	     mobtxt.label->setText("\0");

	     yobtxt.label->setText("\0");

	     gendertxt.label->setText("\0");
	     addresstxt.label->setText("\0");

	     statustxt.label->setText("\0");

	     basicpaytxt.label->setText("\0");

	     hratxt.label->setText("\0");

	     datxt.label->setText("\0");

	     empCattxt.label->setText("\0");
	     panel.repaint();
	     }
void save(Employee &emp){
 if(editState==NULL){
 ofstream out("Cache.Dat",ios::binary|ios::app);
 out.write((char *)&emp,sizeof(emp));
 out.close();       }
 else{
 fstream f;
 Employee temp;
 int pos=0;
 f.open("Cache.Dat",ios::binary|ios::in|ios::out);

while(f){
     pos=f.tellg();
     f.read((char *)&temp,sizeof(temp));
     if(temp.getId()==editState->emp.getId()){
	    f.seekp(pos);
	    f.write((char *)&emp,sizeof(emp));
	    break;
					      }
	}
 f.close();
 void search(int);
 search(emp.getId());
     }
			   }
void edit(){
 if(searchState!=NULL){

    int deg=0;
    int sign;
    if(editState!=NULL)
     delete editState;

    editState=new FileDat;
    editState->emp=searchState->emp;
    editState->currentPosition=searchState->currentPosition;
    //fill in the textboxes

	     int c=count(searchState->emp.getId());
	     IDtxt.label->setText(ecvt(searchState->emp.getId(),c,&deg,&sign));
	     nametxt.label->setText(searchState->emp.getName());
	       c=count(searchState->emp.getDob());
	     dobtxt.label->setText(ecvt(searchState->emp.getDob(),c,&deg,&sign));
		c=count(searchState->emp.getMob());
	     mobtxt.label->setText(ecvt(searchState->emp.getMob(),c,&deg,&sign));
	      c=count(searchState->emp.getYob());
	     yobtxt.label->setText(ecvt(searchState->emp.getYob(),c,&deg,&sign));
	     char *a=new char[2];
	     *a=searchState->emp.getGender();
	     *((++a)--)='\0';
	     gendertxt.label->setText(a);
	     addresstxt.label->setText(searchState->emp.getAddress());
	      c=count(searchState->emp.getStatus());
	     statustxt.label->setText(ecvt(searchState->emp.getStatus(),c,&deg,&sign));
	      c=count(searchState->emp.getBasicPay());
	     basicpaytxt.label->setText(ecvt(searchState->emp.getBasicPay(),c,&deg,&sign));
	      c=count(searchState->emp.getHRA());
	     hratxt.label->setText(ecvt(searchState->emp.getHRA(),c,&deg,&sign));
	      c=count(searchState->emp.getDA());
	     datxt.label->setText(ecvt(searchState->emp.getDA(),c,&deg,&sign));
	    c=count(searchState->emp.getEmpCat());
	     empCattxt.label->setText(ecvt(searchState->emp.getEmpCat(),c,&deg,&sign));
		panel.repaint();
		}
 else if(editState!=NULL)
 {
   ;//do nothing
 }

	   }
void erase(){

    if(searchState!=NULL){
	 ifstream in("Cache.Dat",ios::binary);
	 ofstream out("Temp.Dat",ios::binary);
	 Employee emp;
	 while(in){
	     in.read((char *)&emp,sizeof(emp));
	     if(searchState->emp.getId()!=emp.getId()){
		   out.write((char *)&emp,sizeof(emp));
						       }
		  }
	   in.close();
	   out.close();
	   remove("Cache.Dat");
	   rename("Temp.Dat","Cache.Dat");
	   delete searchState;
	   searchState=NULL;
	   if(editState!=NULL)
	   delete editState;
	   editState=NULL;
	     Id21.setText("\0");
	     Name21.setText("\0");

	     Dob21.setText("\0");

	     Gender21.setText("\0");
	     Address21.setText("\0");

	     Status21.setText("\0");

	     Basicpay21.setText("\0");

	     Hra21.setText("\0");

	     Da21.setText("\0");

	     EmpCat21.setText("\0");
		  extern Panel searchPanel;
		searchPanel.repaint();
			 }
     else{
	  //do nothing
	 }
	    }
void refreshSearchPanel(){
     int deg=0;
	  int sign;
	     int c=count(searchState->emp.getId());
	     Id21.setText(ecvt(searchState->emp.getId(),c,&deg,&sign));
	     Name21.setText(searchState->emp.getName());
	       c=count(searchState->emp.getDob());
	       String s1=ecvt(searchState->emp.getDob(),c,&deg,&sign);
	       String s2="-";
	       s1=s1+s2;
		c=count(searchState->emp.getMob());
	       s2=ecvt(searchState->emp.getMob(),c,&deg,&sign);
	       s1=s1+s2;
	       s2="-";
	       s1=s1+s2;
		c=count(searchState->emp.getYob());
	       s2=ecvt(searchState->emp.getYob(),c,&deg,&sign);
	       s1=s1+s2;
	     Dob21.setText((char *)s1);
	     char *a=new char[2];
	     *a=searchState->emp.getGender();
	     *((++a)--)='\0';
	     Gender21.setText(a);
	     Address21.setText(searchState->emp.getAddress());
	      c=count(searchState->emp.getStatus());
	     Status21.setText(ecvt(searchState->emp.getStatus(),c,&deg,&sign));
	      c=count(searchState->emp.getBasicPay());
	     Basicpay21.setText(ecvt(searchState->emp.getBasicPay(),c,&deg,&sign));
	      c=count(searchState->emp.getHRA());
	     Hra21.setText(ecvt(searchState->emp.getHRA(),c,&deg,&sign));
	      c=count(searchState->emp.getDA());
	     Da21.setText(ecvt(searchState->emp.getDA(),c,&deg,&sign));
	    c=count(searchState->emp.getEmpCat());
	    char *cat;
	    enum EmpCategory;
	    switch(searchState->emp.getEmpCat()){
	     case AGENT:
	     cat="AGENT";
	     break;
	     case SCIENTIST:
	     cat="SCIENTIST";
	     break;
	     case ANALYST:
	     cat="ANALYST";
	     break;
	     case SECURITY:
	     cat="SECURITY";
	     break;
	     default:
	     cat="N/A";
						}


	     EmpCat21.setText(cat);
		  extern Panel searchPanel;
		searchPanel.repaint();
			  }
void search(int ID){
 Employee emp;
 int found=0;
 ifstream in("Cache.Dat",ios::binary|ios::nocreate);

      while(in){
	in.read((char *)&emp,sizeof(emp));

	 if(emp.getId()==ID){
	     searchState=new FileDat();
	     searchState->emp=emp;
	     searchState->currentPosition=(in.tellg()-sizeof(emp));


	     found=1;
	     break;
			    }
	       }
	   in.close();
	if(found==1){
	    refreshSearchPanel();
		    }
	else{
	   if(searchState!=NULL)
	    delete searchState;
	    searchState=NULL;
	     Id21.setText("\0");
	     Name21.setText("\0");

	     Dob21.setText("\0");

	     Gender21.setText("\0");
	     Address21.setText("\0");

	     Status21.setText("\0");

	     Basicpay21.setText("\0");

	     Hra21.setText("\0");

	     Da21.setText("\0");

	     EmpCat21.setText("\0");
		  extern Panel searchPanel;
		searchPanel.repaint();
	    }
		    }
class EventHandler:public ActionListener{
 public:
      void  actionPerformed(ActionEvent *evt){
	if((Button*)(evt->getSource())==&bt){
		   //create a record
		   create();
		   if(searchState!=NULL){
		       refreshSearchPanel();
					 }
		     setfillstyle(EMPTY_FILL,EGA_BLACK);
		     bar(0,25,getmaxx(),30);
					       }
	else if((Button*)(evt->getSource())==&bt2){
		    //edit a record
		    edit();
		     if(searchState!=NULL){
		       refreshSearchPanel();
					  }
		      setfillstyle(EMPTY_FILL,EGA_BLACK);
		      bar(0,25,getmaxx(),30);
						  }
	else if((Button*)(evt->getSource())==&bt3){
		     erase();
						   }
	else if((Button*)(evt->getSource())==&bt4){
		   Employee emp;
		   emp.setName((char *)*((String*)(nametxt.label)));
		   emp.setGender(*((char *)*((String*)(gendertxt.label))));
		   emp.setAddress((char *)*((String*)(addresstxt.label)));
		   emp.setEmpCat(atoi((char *)*((String*)(empCattxt.label))));
		   emp.setId(atoi((char *)*((String*)(IDtxt.label))));
		   emp.setStatus(atoi((char *)*((String*)(statustxt.label))));
		   emp.setBasicPay(atoi((char *)*((String*)(basicpaytxt.label))));
		   emp.setHRA(atoi((char *)*((String*)(hratxt.label))));
		   emp.setDA(atoi((char *)*((String*)(datxt.label))));
		   int day=atoi((char *)*((String*)(dobtxt.label)));
		   int month=atoi((char *)*((String*)(mobtxt.label)));
		   int year=atoi((char *)*((String*)(yobtxt.label)));
		   emp.setDOB(day,month,year);
		   save(emp);
						   }
       else if((TextField*)(evt->getSource())==&searchtxt){
       if(evt->getType()==ActionEvent::KEYBOARD_EVENT){
	     search(atoi((char *)*((String*)(searchtxt.label))));
						       }
							  }

					      }
					 };
 void Graphics::drawComponent(Component *comp){
   int bt;
   int x,y;
   int h,w;
   int col;
       comp->getBoundaryType(bt);
       comp->getSize(w,h);
       comp->getLocation(x,y);
       comp->getFillColor(col) ;

     setfillstyle(SOLID_FILL,col);
     if(bt!=NO_BOUNDARY)
      bar(x+1,y+1,x+w-1,y+h-1);
     setcolor(EGA_BLACK);
      setlinestyle(SOLID_LINE,0,NORM_WIDTH);
      if(bt!=IMAGINARY&&bt!=NO_BOUNDARY)
      rectangle(x,y,x+w,y+h);



						}
void Llist::  remove(int i,int dt){
	  Node *node;
	  Node *prevNode;
			    node=this->get(i);
	      if( node!=NULL ){
		      if(dt==1){
			    delete node->comp;

				 }
		       if((i-1)>=0){
			     prevNode=this->get(i-1);
			     prevNode->next=node->next;
			     }
			     else{
				     //the first node is to be deleted
				    delete this->first;
				    first=NULL;
				    first=this->get(i+1);
				 }
			       delete node;
				size--;
				       }
			else{
			    //comp does not exist
			    }


				    }


volatile Queue *q;
 Graphics g;
 Window win(&g);
 Panel panel(&g);
 Panel toolBar(&g);
 Panel searchPanel(&g);
 EventHandler evth;
 Button bt(&g);
 Button bt2(&g);
 Button bt3(&g);
 Button bt4(&g);
 Label Dob(&g);
 Label Name(&g);
 Label Gender(&g);
 Label EmpCat(&g);
 Label Address(&g);
 Label Id(&g);
 Label Status(&g);
 Label Paygrade(&g);
 Label Basicpay(&g);
 Label Hra(&g);
 Label Da(&g);
 Label Search(&g);

 Label Dob2(&g);
 Label Name2(&g);
 Label Gender2(&g);
 Label EmpCat2(&g);
 Label Address2(&g);
 Label Id2(&g);
 Label Status2(&g);
 Label Paygrade2(&g);
 Label Basicpay2(&g);
 Label Hra2(&g);
 Label Da2(&g);
 Label Search2(&g);



 Label Dob21(&g);
 Label Name21(&g);
 Label Gender21(&g);
 Label EmpCat21(&g);
 Label Address21(&g);
 Label Id21(&g);
 Label Status21(&g);
 Label Paygrade21(&g);
 Label Basicpay21(&g);
 Label Hra21(&g);
 Label Da21(&g);
 Label Search21(&g);

 TextField nametxt(&g);
 TextField dobtxt(&g);
 Label dash1(&g);
 TextField mobtxt(&g);
 Label dash2(&g);
 TextField yobtxt(&g);
 TextField gendertxt(&g);
 TextField empCattxt(&g);
 TextField addresstxt(&g);
 TextField IDtxt(&g);
 TextField statustxt(&g);
 TextField paygradetxt(&g);
 TextField basicpaytxt(&g);
 TextField hratxt(&g);
 TextField datxt(&g);
 TextField searchtxt(&g);
 MSEvent *msevt;
 KBEvent *kbevt;
  REGS Mouse::in;
 REGS Mouse::out;
 void interrupt (*(Mouse::oldISR_0x74))(...);
 REGS Keyboard::i;
  REGS Keyboard::o;
  int Keyboard::count;
  int Keyboard::counter;
  KBMemory Keyboard::storage;
  void interrupt (*(Keyboard::oldISR_0x09))(...);
 volatile Queue *(Mouse::q);
 String operator +(String str1,String str2);
  String operator +(String str1,String str2){
  String temp;
  temp.size=strlen((char *)(str1))+strlen((char *)(str2))+1;
  temp.str=new char[temp.size];
  strcpy(temp.str,str1.str);
  strcat(temp.str,str2.str);

  return temp;                              }
void init(){
 Mouse::InitDriver(q);
 Keyboard::InitDriver(q);

 bt.setActionListener(&evth);
 bt.setLocation(30,30+5);

 bt.setText("Create");
 bt.setTextColor(EGA_BLACK);
 bt.setButtonColor(EGA_WHITE);
 bt.setChangedStateButtonColor(EGA_BLACK);
 bt.setChangedStateTextColor(EGA_WHITE);
 bt.setSize(60,20);

 bt.setTextSize(1);


 bt.label->setBoundaryType(NO_BOUNDARY);
  bt2.setActionListener(&evth);
 bt2.setLocation(30+70,30+5);

 bt2.setText("Edit");
 bt2.setTextColor(EGA_BLACK);
 bt2.setButtonColor(EGA_WHITE);
 bt2.setChangedStateButtonColor(EGA_BLACK);
 bt2.setChangedStateTextColor(EGA_WHITE);
 bt2.setSize(60,20);

 bt2.setTextSize(1);


 bt2.label->setBoundaryType(NO_BOUNDARY);

 bt3.setActionListener(&evth);
 bt3.setLocation(30+70+70,30+5);

 bt3.setText("Delete");
 bt3.setTextColor(EGA_BLACK);
 bt3.setButtonColor(EGA_WHITE);
 bt3.setChangedStateButtonColor(EGA_BLACK);
 bt3.setChangedStateTextColor(EGA_WHITE);
 bt3.setSize(60,20);

 bt3.setTextSize(1);


 bt3.label->setBoundaryType(NO_BOUNDARY);
  bt4.setActionListener(&evth);
 bt4.setLocation(30+70+70+70,30+5);

 bt4.setText("Save");
 bt4.setTextColor(EGA_BLACK);
 bt4.setButtonColor(EGA_WHITE);
 bt4.setChangedStateButtonColor(EGA_BLACK);
 bt4.setChangedStateTextColor(EGA_WHITE);
 bt4.setSize(60,20);

 bt4.setTextSize(1);


 bt4.label->setBoundaryType(NO_BOUNDARY);
 panel.setLocation(0,25);
 panel.setSize(getmaxx(),getmaxy()-45);
 searchPanel.setLocation(345+30,60+5);
 searchPanel.setSize(getmaxx()-(345+30+5),getmaxy()-(60+5)-45);
 searchtxt.setActionListener(&evth);
 searchtxt.setLocation(30+70+70+70+70+70+55,30+5);
 searchtxt.setSize(200,20);
 searchtxt.label->setBoundaryType(NO_BOUNDARY);
 searchtxt.label->setSize(1);
 searchtxt.label->setLocation((30+70+70+70+70+70+55)+2,30+5+4);
 Search.setBoundaryType(NO_BOUNDARY);
 Search.setSize(1);
 Search.setLocation(30+70+70+70+70+70,30+5+10);
 Search.Component::setSize(30,20);
 Search.setText("Search");


 IDtxt.setLocation(145,getmaxy()/2-165);
 IDtxt.setSize(70,20);
 IDtxt.label->setBoundaryType(NO_BOUNDARY);
 IDtxt.label->setSize(1);
 IDtxt.label->setLocation(145+2,getmaxy()/2-165+4);

  Id.setBoundaryType(NO_BOUNDARY);
  Id.setSize(1);
  Id.setLocation(5,getmaxy()/2-160);
  Id.Component::setSize(30,20);
  Id.setText("Employee ID");

  Id2.setBoundaryType(NO_BOUNDARY);
  Id2.setSize(1);
  Id2.setLocation(345+30+5,getmaxy()/2-160);
  Id2.Component::setSize(90,20);
  Id2.setText("Employee ID:");

  Id21.setBoundaryType(NO_BOUNDARY);
  Id21.setSize(1);
  Id21.setLocation(345+30+5+95,getmaxy()/2-160);
  Id21.Component::setSize(50,20);




 nametxt.setLocation(145,getmaxy()/2-135);
 nametxt.setSize(200,20);
  nametxt.label->setBoundaryType(NO_BOUNDARY);
  nametxt.label->setSize(1);
  nametxt.label->setLocation(145+2,getmaxy()/2-135+4);

  Name.setBoundaryType(NO_BOUNDARY);
  Name.setSize(1);
  Name.setLocation(5,getmaxy()/2-130);
  Name.Component::setSize(30,20);
  Name.setText("Name");

  Name2.setBoundaryType(NO_BOUNDARY);
  Name2.setSize(1);
  Name2.setLocation(345+30+5,getmaxy()/2-130);
  Name2.Component::setSize(30,20);
  Name2.setText("Name:");

  Name21.setBoundaryType(NO_BOUNDARY);
  Name21.setSize(1);
  Name21.setLocation(345+30+5+30+5+5,getmaxy()/2-130);
  Name21.Component::setSize(180,20);


  dobtxt.setLocation(145,getmaxy()/2-105);
  dobtxt.setSize(30,20);
  dobtxt.label->setBoundaryType(NO_BOUNDARY);
  dobtxt.label->setSize(1);
  dobtxt.label->setLocation(145+2,getmaxy()/2-105+4);

  dash1.setBoundaryType(NO_BOUNDARY);
  dash1.setSize(1);
  dash1.setLocation(145+30+2,getmaxy()/2-105+5+2);
  dash1.Component::setSize(5,20);
  dash1.setText("-");

  mobtxt.setLocation(145+30+2+5+2,getmaxy()/2-105);
  mobtxt.setSize(30,20);
  mobtxt.label->setBoundaryType(NO_BOUNDARY);
  mobtxt.label->setSize(1);
  mobtxt.label->setLocation((145+30+2+5+2)+2,getmaxy()/2-105+4);

  dash2.setBoundaryType(NO_BOUNDARY);
  dash2.setSize(1);
  dash2.setLocation(145+30+2+5+2+30+2,getmaxy()/2-105+5+2);
  dash2.Component::setSize(5,20);
  dash2.setText("-");

  yobtxt.setLocation(145+30+2+5+2+30+2+5+2,getmaxy()/2-105);
  yobtxt.setSize(50,20);
  yobtxt.label->setBoundaryType(NO_BOUNDARY);
  yobtxt.label->setSize(1);
  yobtxt.label->setLocation((145+30+2+5+2+30+2+5+2)+2,getmaxy()/2-105+4);

    Dob.setBoundaryType(NO_BOUNDARY);
  Dob.setSize(1);
  Dob.setLocation(5,getmaxy()/2-100);
    Dob.Component::setSize(70,20);
    Dob.setText("Date of Birth");

    Dob2.setBoundaryType(NO_BOUNDARY);
  Dob2.setSize(1);
  Dob2.setLocation(345+35,getmaxy()/2-100);
    Dob2.Component::setSize(102,20);
    Dob2.setText("Date of Birth:");

      Dob21.setBoundaryType(NO_BOUNDARY);
     Dob21.setSize(1);
     Dob21.setLocation(345+35+102+5+5,getmaxy()/2-100);
     Dob21.Component::setSize(70,20);




  gendertxt.setLocation(145,getmaxy()/2-75);
  gendertxt.setSize(20,20);
  gendertxt.label->setBoundaryType(NO_BOUNDARY);
  gendertxt.label->setSize(1);
  gendertxt.label->setLocation(145+2,getmaxy()/2-75+4);


    Gender.setBoundaryType(NO_BOUNDARY);
    Gender.setSize(1);
  Gender.setLocation(5,getmaxy()/2-70);
    Gender.Component::setSize(70,20);
    Gender.setText("Gender");

     Gender2.setBoundaryType(NO_BOUNDARY);
    Gender2.setSize(1);
  Gender2.setLocation(345+35,getmaxy()/2-70);
    Gender2.Component::setSize(50,20);
    Gender2.setText("Gender");

    Gender21.setBoundaryType(NO_BOUNDARY);
    Gender21.setSize(1);
    Gender21.setLocation(345+35+55,getmaxy()/2-70);
    Gender21.Component::setSize(50,20);
   

  addresstxt.setLocation(145,getmaxy()/2-45);
  addresstxt.setSize(200,20);
  addresstxt.label->setBoundaryType(NO_BOUNDARY);
  addresstxt.label->setSize(1);
  addresstxt.label->setLocation(145+2,getmaxy()/2-45+4);


    Address.setBoundaryType(NO_BOUNDARY);
    Address.setSize(1);
    Address.setLocation(5,getmaxy()/2-40);
    Address.Component::setSize(70,20);
    Address.setText("Address");

    Address2.setBoundaryType(NO_BOUNDARY);
    Address2.setSize(1);
    Address2.setLocation(345+35,getmaxy()/2-40);
    Address2.Component::setSize(60,20);
    Address2.setText("Address:");

    Address21.setBoundaryType(NO_BOUNDARY);
    Address21.setSize(1);
    Address21.setLocation(345+35+65+5,getmaxy()/2-40);
    Address21.Component::setSize(170,20);



  empCattxt.setLocation(145,getmaxy()/2-15);
  empCattxt.setSize(50,20);
  empCattxt.label->setBoundaryType(NO_BOUNDARY);
  empCattxt.label->setSize(1);
  empCattxt.label->setLocation(145+2,getmaxy()/2-15+4);


    EmpCat.setBoundaryType(NO_BOUNDARY);
    EmpCat.setSize(1);
    EmpCat.setLocation(5,getmaxy()/2-10);
    EmpCat.Component::setSize(70,20);
    EmpCat.setText("Employee Category");

    EmpCat2.setBoundaryType(NO_BOUNDARY);
    EmpCat2.setSize(1);
    EmpCat2.setLocation(345+35,getmaxy()/2-10);
    EmpCat2.Component::setSize(135,20);
    EmpCat2.setText("Employee Category:");

    EmpCat21.setBoundaryType(NO_BOUNDARY);
    EmpCat21.setSize(1);
    EmpCat21.setLocation(345+35+150,getmaxy()/2-(10));
    EmpCat21.Component::setSize(50,20);
  


  statustxt.setLocation(145,getmaxy()/2-(15-30));
  statustxt.setSize(30,20);
  statustxt.label->setBoundaryType(NO_BOUNDARY);
  statustxt.label->setSize(1);
  statustxt.label->setLocation(145+2,getmaxy()/2-(15-30)+4);


    Status.setBoundaryType(NO_BOUNDARY);
    Status.setSize(1);
    Status.setLocation(5,getmaxy()/2-(15-30-5));
    Status.Component::setSize(70,20);
    Status.setText("Status");

    Status2.setBoundaryType(NO_BOUNDARY);
    Status2.setSize(1);
    Status2.setLocation(345+35,getmaxy()/2-(15-30-5));
    Status2.Component::setSize(50,20);
    Status2.setText("Status:");


     Status21.setBoundaryType(NO_BOUNDARY);
    Status21.setSize(1);
    Status21.setLocation(345+35+55,getmaxy()/2-(15-30-5));
    Status21.Component::setSize(70,20);








  basicpaytxt.setLocation(145,getmaxy()/2-(15-30-5-5-20));
  basicpaytxt.setSize(100,20);
  basicpaytxt.label->setBoundaryType(NO_BOUNDARY);
  basicpaytxt.label->setSize(1);
  basicpaytxt.label->setLocation(145+2,getmaxy()/2-(15-30-5-5-20)+4);


    Basicpay.setBoundaryType(NO_BOUNDARY);
    Basicpay.setSize(1);
    Basicpay.setLocation(5,getmaxy()/2-((15-30-5-5-20-5)));
    Basicpay.Component::setSize(70,20);
    Basicpay.setText("Basic Pay");

    Basicpay2.setBoundaryType(NO_BOUNDARY);
    Basicpay2.setSize(1);
    Basicpay2.setLocation(345+35,getmaxy()/2-((15-30-5-5-20-5)));
    Basicpay2.Component::setSize(70,20);
    Basicpay2.setText("Basic Pay:");

    Basicpay21.setBoundaryType(NO_BOUNDARY);
    Basicpay21.setSize(1);
    Basicpay21.setLocation(345+35+75+5,getmaxy()/2+(50));
    Basicpay21.Component::setSize(70,20);



  hratxt.setLocation(145,getmaxy()/2-(15-30-5-5-20-20-10));
  hratxt.setSize(70,20);
  hratxt.label->setBoundaryType(NO_BOUNDARY);
  hratxt.label->setSize(1);
  hratxt.label->setLocation(145+2,getmaxy()/2-(15-30-5-5-20-20-10)+4);


    Hra.setBoundaryType(NO_BOUNDARY);
    Hra.setSize(1);
    Hra.setLocation(5,getmaxy()/2-((15-30-5-5-20-20-10-5)));
    Hra.Component::setSize(70,20);
    Hra.setText("HRA");

    Hra2.setBoundaryType(NO_BOUNDARY);
    Hra2.setSize(1);
    Hra2.setLocation(345+35,getmaxy()/2-((15-30-5-5-20-20-10-5)));
    Hra2.Component::setSize(25,20);
    Hra2.setText("HRA:");

     Hra21.setBoundaryType(NO_BOUNDARY);
    Hra21.setSize(1);
    Hra21.setLocation(345+35+30,getmaxy()/2-((15-30-5-5-20-20-15)));
    Hra21.Component::setSize(70,20);


  datxt.setLocation(145,getmaxy()/2-(15-30-5-5-20-20-10-30));
  datxt.setSize(70,20);
  datxt.label->setBoundaryType(NO_BOUNDARY);
  datxt.label->setSize(1);
  datxt.label->setLocation(145+2,getmaxy()/2-(15-30-5-5-20-20-10-30)+4);


    Da.setBoundaryType(NO_BOUNDARY);
    Da.setSize(1);
    Da.setLocation(5,getmaxy()/2-((15-30-5-5-20-20-10-30-5)));
    Da.Component::setSize(70,20);
    Da.setText("DA");

    Da2.setBoundaryType(NO_BOUNDARY);
    Da2.setSize(1);
    Da2.setLocation(345+35,getmaxy()/2-((15-30-5-5-20-20-10-30-5)));
    Da2.Component::setSize(15,20);
    Da2.setText("DA:");

     Da21.setBoundaryType(NO_BOUNDARY);
    Da21.setSize(1);
    Da21.setLocation(345+35+25,getmaxy()/2-((15-30-5-5-20-20-10-10-10-10-5)));
    Da21.Component::setSize(70,20);




 
 toolBar.setLocation(0,30);
 toolBar.setSize(getmaxx(),30);

 toolBar.addComponent(&bt);
 toolBar.addComponent(&bt2);
 toolBar.addComponent(&bt3);
 toolBar.addComponent(&bt4);
 toolBar.addComponent(&searchtxt);
 toolBar.addComponent(&Search);

 searchPanel.addComponent(&Id2);
 searchPanel.addComponent(&Id21);
 searchPanel.addComponent(&Name2);
 searchPanel.addComponent(&Name21);
 searchPanel.addComponent(&Dob2);
 searchPanel.addComponent(&Dob21);
 searchPanel.addComponent(&Gender2);
 searchPanel.addComponent(&Gender21);
 searchPanel.addComponent(&Address2);
 searchPanel.addComponent(&Address21);
 searchPanel.addComponent(&EmpCat2);
 searchPanel.addComponent(&EmpCat21);
 searchPanel.addComponent(&Status2);
 searchPanel.addComponent(&Status21);
 searchPanel.addComponent(&Basicpay2);
 searchPanel.addComponent(&Basicpay21);
 searchPanel.addComponent(&Hra2);
 searchPanel.addComponent(&Hra21);
 searchPanel.addComponent(&Da2);
 searchPanel.addComponent(&Da21);


 panel.addComponent(&searchPanel);


 panel.addComponent(&toolBar);
 panel.addComponent(&nametxt);
 panel.addComponent(&Name);
 panel.addComponent(&Dob);
 panel.addComponent(&dobtxt);
 panel.addComponent(&dash1);
 panel.addComponent(&mobtxt);
 panel.addComponent(&dash2);
 panel.addComponent(&yobtxt);
 panel.addComponent(&Gender);
 panel.addComponent(&gendertxt);
 panel.addComponent(&Address);
 panel.addComponent(&addresstxt);
 panel.addComponent(&EmpCat);
 panel.addComponent(&empCattxt);
 panel.addComponent(&Id);
 panel.addComponent(&IDtxt);
 panel.addComponent(&Status);
 panel.addComponent(&statustxt);
 panel.addComponent(&Basicpay);
 panel.addComponent(&basicpaytxt);
 panel.addComponent(&Hra);
 panel.addComponent(&hratxt);
 panel.addComponent(&datxt);
 panel.addComponent(&Da);
 win.setLocation(0,0);
 win.setSize(getmaxx(),getmaxy());
 win.setTitle("FOO DATABASE");
 win.label->setBoundaryType(IMAGINARY);
 win.label->setHorzSize(50,100);
 win.label->setVertSize(50,100);
// win.label->setFont(SANS_SERIF_FONT);
 win.label->setSize(2);
 win.setPanel(&panel);
 win.setVisible(true);
 setfillstyle(EMPTY_FILL,EGA_BLACK);
 bar(0,25,getmaxx(),30);
 Mouse::setVisible(true);
	   }
void restore(){
 Keyboard::restoreDriver();
 Mouse::restoreDriver();
 g.dispose();
		}
char rectify(char ch){
   switch(ch){
     case '9':ch=' ';break;
     case  2 :ch='1';break;
     case  3 :ch='2';break;
     case  4 :ch='3';break;
     case  5 :ch='4';break;
     case  6 :ch='5';break;
     case  7 :ch='6';break;
     case  8 :ch='7';break;
     case  9 :ch='8';break;
     case 10 :ch='9';break;
     case 11 :ch='0';break;
     case 16 :ch='Q';break;
     case 17 :ch='W';break;
     case 18 :ch='E';break;
     case 19 :ch='R';break;
     case 20 :ch='T';break;
     case 21 :ch='Y';break;
     case 22 :ch='U';break;
     case 23 :ch='I';break;
     case 24 :ch='O';break;
     case 25 :ch='P';break;
     case 30 :ch='A';break;
     case 31 :ch='S';break;
     case 32 :ch='D';break;
     case 33 :ch='F';break;
     case 34 :ch='G';break;
     case 35 :ch='H';break;
     case 36 :ch='J';break;
     case 37 :ch='K';break;
     case 38 :ch='L';break;
     case 44 :ch='Z';break;
     case 45 :ch='X';break;
     case 46 :ch='C';break;
     case 47 :ch='V';break;
     case 48 :ch='B';break;
     case 49 :ch='N';break;
     case 50 :ch='M';break;
	     }
    return ch;
		      }
void processMessage(ActionEvent *evt){
  Component *loc;
       if(evt->getType()==ActionEvent::MOUSE_EVENT){

	  if((msevt=((MSEvent*)evt))!=NULL){


		    if(msevt->getClickValue()==1)
		    {    if(win.hasChild()!=false&&panel.hasChild()!=false){
			       loc=getSourceComponent(msevt->getX(),msevt->getY(),&panel);
			       msevt->setSource(loc);


				if(loc->hasChild()!=true){

			       if(loc->getState()!=Component::ACTIVE&&active!=1){
			      loc->changeState(Component::ACTIVE);


			      activeComponent=loc;
			      active=1;
			       gotoxy(20,20);

			      if((activeComponent!=NULL)&&((activeComponent->isA()).equals("TextField"))){
				 //activate blinker

				 //textfield initiation starts her                                     }
													  }
			       Mouse::setVisible(false);
			       loc->repaint();

			       Mouse::setVisible(true);


											 }



							   }else if((activeComponent!=NULL)&&((activeComponent->isA()).equals("TextField"))&&loc!=activeComponent){
			      activeComponent->changeState(Component::INACTIVE);
			      activeComponent->repaint();
			      //deactivate blinker

			      activeComponent=loc;
			      active=0;                                                                                                                             }


							     }
		    }else if(msevt->getClickValue()==0){
		    if(active==1){
			 if(win.hasChild()!=false&&panel.hasChild()!=false){
			       loc=getSourceComponent(msevt->getX(),msevt->getY(),&panel);
				if(loc==activeComponent){


				if(loc->hasChild()!=true){



				 msevt->setSource(loc);
			       loc->invokeActionListener(msevt);
			      loc->changeState(Component::INACTIVE);

			      Mouse::setVisible(false);
			       loc->repaint();
			      Mouse::setVisible(true);
			      if(!((loc->isA()).equals("TextField"))){
			      active=0;
			      activeComponent->changeState(Component::INACTIVE);
			       activeComponent=NULL;
								     }

			       Mouse::setVisible(true);
							  }
							  }
			      else {   if(!((activeComponent->isA()).equals("TextField"))){
				      activeComponent->changeState(Component::INACTIVE);

				      activeComponent->repaint();
				      activeComponent=NULL;
				      active=0;                              }
				      active=0;
				    }
									   }
				}
							}

		  q->deleteTempNode();
			 }
			   }
      else if(evt->getType()==ActionEvent::KEYBOARD_EVENT) {
	if((kbevt=((KBEvent*)evt))!=NULL){
		 if(activeComponent!=NULL&&((activeComponent->isA()).equals("TextField"))){
		    char ch=kbevt->getKey();

		    char *ch1=new char(2);
		    char *str;
		    *ch1=rectify(ch);
		    *((++ch1)--)='\0';
		     if(*ch1!=14&&*ch1!=28){
		      String s1=ch1;
		      String s2=*((String *)( ((TextField*) (activeComponent))->label));

		    String s3=s2+s1;
		    ((String *)(((TextField*) (activeComponent))->label))->setString((char *)s3);
				  }
		     else if(*ch1==14){
		      String s2=*((String *)( ((TextField*) (activeComponent))->label));
		      str=new char[strlen((char *)(s2))+1];
		      strcpy(str,(char*)s2);
		      str=str+strlen((char *)(s2))-1;

		      *str='\0';
		      str=str-strlen((char *)(s2))+1;
		      ((String *)(((TextField*) (activeComponent))->label))->setString(str);
				       }
		    else if(*ch1==28){

				 kbevt->setSource(activeComponent);
				 activeComponent->invokeActionListener(kbevt);
				      }

		       Mouse::setVisible(false);
		       activeComponent->repaint();
		       Mouse::setVisible(true);
					}
		    q->deleteTempNode();
					  }
	     }


					     }

Component* getSourceComponent(int x,int y,Component *parentComponent ){
  int width,height;
  int xc,yc;
      if(parentComponent->hasChild()){
	    for(int i=0;i<parentComponent->list->getSize();i++){
		(parentComponent->list->get(i))->comp->getLocation(xc,yc);
		(parentComponent->list->get(i))->comp->getSize(width,height);

		   if((x>=xc)&&(x<=xc+width)&&
		   (y>=yc)&&y<=yc+height){
			  return getSourceComponent(x,y,parentComponent->list->get(i)->comp);
					  }


								 }
			   return parentComponent;
				      }
      else {
	   return parentComponent;
	   }
							   }
ActionEvent* retrieveMessage(){
ActionEvent *evt;
  delay(10);//to maintain Synchronization
 evt=(q->get());


	     return evt;
				       }
#define ESC 1
#pragma startup init
#pragma end restore
#define running ((evt=retrieveMessage())->getType()==1)?(((KBEvent*)evt)->getKey()\
==ESC)?0:1 \
\:1

void main(){
 ActionEvent *evt;
    while(running){
	   processMessage(evt);
		  }
	    }