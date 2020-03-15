
#include <string.h>
#include <conio.h>
#include <dos.h>
#include <list.h>
#ifndef utilities_h

#define utilities_h
#define null "\0"


enum status {success,error};
enum Boolean {false,true};
class Component;
class ActionEvent{
  protected:
  int type;
  Component *source;
  public :
  enum EventType{KEYBOARD_EVENT=0x01,MOUSE_EVENT=0x02,TIMER_EVENT=0x03};
   ActionEvent(int type){
	this->type=type;
	source=NULL;
			 }
   ActionEvent(){}

   void setSource(Component *comp){
	     source=comp;
				   }
   Component* getSource(){
	    return source;
			  }
   int getType(){
       return type;
		 }
		 };
class KBEvent:public ActionEvent{
 private:
 int scanCode;
 public:
 KBEvent(){}
 KBEvent(KBEvent &kbevt){
    this->scanCode=kbevt.scanCode;
    this->type=kbevt.type;
	   }
 KBEvent(ActionEvent &evt){
     this->type=evt.getType();
     this->scanCode=((KBEvent*)(&evt))->scanCode;
	   }
 KBEvent(int scanCode):ActionEvent(KEYBOARD_EVENT){
  this->scanCode=scanCode;
						   }
 int getKey(){
    return this->scanCode;
	     }


				};
class MSEvent:public ActionEvent{
  private:
  int x,y;
  int click;
  public:
  MSEvent(){}
  MSEvent(int x,int y,int click): ActionEvent(MOUSE_EVENT){
   this->x=x;
   this->y=y;
   this->click=click;
								}
    MSEvent(MSEvent &msevt){
    this->x=msevt.x;
    this->y=msevt.y;
    this->click=msevt.click;
    this->type=msevt.type;
			    }
    MSEvent(ActionEvent &evt){
    this->type=evt.getType();
    this->x=((MSEvent*)(&evt))->x;
    this->y=((MSEvent*)(&evt))->y;
    this->click=((MSEvent*)(&evt))->click;
			      }
  int getX(){
    return this->x;
	    }
  int getY(){
    return this->y;
	    }
  int getClickValue(){
    return this->click;
		     }


				};

   class Queue{
    public:
   struct Node{
    ActionEvent *evt;
    Node *next;

	       };
    protected:
    Node *first;
    Node *rear;
    Node *temp;
    MSEvent  msevt;
    KBEvent  kbevt;
    int size;
    ActionEvent act;
    public:
    Queue(){
       first=NULL;
       rear=NULL;
       size=0;
	    }
    void add(ActionEvent *evt){
       Node *node=new Node;
       if(node==NULL){
	  cout<<"Memory empty!";
	  exit(-1);
		      }
      node->evt=evt;
      node->next=NULL;
      if(rear==NULL)
      first=rear=node;
      else {
      rear->next=node;
      rear=node;}
      size++;
	       }
     ActionEvent* get(){
       if(first==NULL){
	   //nothing to remove
		       }
	else{
	   size--;
	    }
	return (first->evt);
		  }
	    void deleteTempNode(){
		 if(first==rear) {
		   delete (first->evt);
		   delete (first->next);
		   first=rear=NULL;
		   }
		 else{
		     temp=first;
		     first=first->next;
		     if((temp->evt)!=NULL)
		     delete temp->evt;
		     delete temp;
		      }

				  }
	    int isEmpty(){
	   return (size>0)?false:true;
		       }

	    };

/**
 * The class is designed to manipulate strings with ease
 */
class String{
    protected:
     char *str;
     int size;

    public:
    String(){
     str=null;
     size=0;
	    }
    String(char *str){
     this->size=strlen(str);
     this->str=new char[this->size+1];
     strcpy(this->str,str);
		     }
    String (String &string){
       this->size=string.getSize();
       this->str=new char[this->size+1];
       strcpy(this->str,(char*)(string));
			    }
     String reverse(){
       strrev(this->str);
       return str;
		     }

    int getSize(){
      return this->size;
		  }
    void setString(char *str){

     this->size=strlen(str);

     this->str=new char[this->size+1];
     strcpy(this->str,str);
			      }
   Boolean equals(String str2){
	return (strcmp(this->str,str2)==0)?true:false;

		    }
   Boolean equalsIgnoreCase(String str2){
	return (strcmpi(this->str,str2)==0)?true:false;
					}
   void toLower(){
	strlwr(this->str);
		 }
   void toUpper(){
	strupr(this->str);
		 }
   void trim(){
   char *p;
   while(*p!='\0'){
     p= strchr(this->str,' ');
     int i=0;
     while(*(p+i+1)!='\0'){
     *(p+i)=*(p+i+1);
      i++;
			  }
      *(p+i)=*(p+(i)+1);
      p=strchr(this->str,' ');

	}
	       }


   operator char*(){
     return str;
		    }

   friend  String  operator +(String str1,String str2);

    ~String(){

     delete str;
	     }


	     };





  /**
  * Mouse Driver v1.0
  */
  #define MSINT 0x74 //Mouse service
   class Mouse{
   private:
   static volatile Queue *q;
   static  void interrupt (*oldISR_0x74)(...);
   static union REGS in,out;
    public:
    static void InitDriver(volatile Queue *q){
	  oldISR_0x74 =getvect(MSINT);
	  setvect(MSINT,ISR_0x74);
	  Mouse::q=q;
					      }

    static void restoreDriver(){
	  setvect(MSINT,oldISR_0x74);
			       }
   /**
    * To display the mouse cursor
    */
    static  void   isSupported(int& i){
    in.x.ax=0x00;
    int86(0x33,&in,&out);
    i=out.x.ax;
				      }
    static  void setVisible(Boolean c){
 if(c==true){
   in.x.ax=0x01;
   int86(0x33,&in,&out);
	     }
 else {
   in.x.ax=0x02;
   int86(0x33,&in,&out);
      }
				       }
   /**
    * To get the current coordinates of the mouse
    * @param &x the variable to receive the abscissa
    * @param &y the variable to receive the ordinate
    * @param &click the variable to receive the mouse button status
    * click=0 if the button is not pressed
    * click=1 if the left button is pressed
    * click=2 if the right button is pressed
    * click=3 if the centre button is pressed
    */
   static  void getMousePosition(int &x,int &y,int &click){
		in.x.ax=0x03;
		int86(0x33,&in,&out);
		click=out.x.bx;
		x=out.x.cx;
		y=out.x.dx;
							  }

/**
 * To set the mouse position
 */
   static  void setPosition(int &x,int &y){
	in.x.ax=0x04;
	in.x.cx=x;
	in.x.dx=y;
	int86(0x33,&in,&out);              }
   private :
   static void interrupt ISR_0x74(...){
  int x,y,click;
  (*oldISR_0x74)();
  in.x.ax=0x03;
  int86(0x33,&in,&out);
  click=out.x.bx;
  x=out.x.cx;
  y=out.x.dx;
  MSEvent *mevt=new MSEvent(x,y,click);
  q->add(mevt);
				      }

	};
#define KBINT 0x09
#define PRINT 0x05
 //IRQ1 Keyboard Service
 /**
  * The keyboard driverv1.0
  */
 class Keyboard{
  public :
  enum ActionKeys {ENTER_KEY=13,CTRL_S=19,BK_SPACE=8,ESC=27};
  private :
  static REGS i,o;
  static int sType;
  static int count;
  static  void interrupt (*oldISR_0x09)(...);
  struct KBMemory{
 volatile Queue *queue;
		}static storage;
  static int counter;
  public :
  static initDriver(){
  counter=0;
  oldISR_0x09=getvect(KBINT);
  setvect(KBINT,ISR_0x09);
			}
  static InitDriver(volatile Queue *q){
  storage.queue=q;
  counter=0;
  oldISR_0x09=getvect(KBINT);
  setvect(KBINT,ISR_0x09);
				      }

static void restoreDriver(){
 cout<<"restoring driver";
 setvect(KBINT,oldISR_0x09);
			    }
  private :
  static  void interrupt ISR_0x09(...){
	      (*oldISR_0x09)();
	     if(count%2==0){
		 i.h.ah=0;
		 int86(22,&i,&o);
		 KBEvent *evt=new KBEvent(o.h.ah);
		 (storage.queue)->add(evt);
			   }
		 else{
		 i.h.ah=0;
		 int86(22,&i,&o);
		     }
		 count++;
		 (*oldISR_0x09)();
					}

	       };


#endif