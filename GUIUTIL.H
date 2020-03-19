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
#ifndef guiutil_h
#define guiutil_h
#include "util.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <dos.h>


enum Boundary {IMAGINARY,REAL,NO_BOUNDARY};
class Component;


   class Llist{
	 struct Node;
	 private:
	 Node *first;
	 int size;
	 int currentNodeIndex;
	 public:
      struct Node{
      Component *comp;
      Node *next;

	      };
	 Llist(){
	   first=NULL;
	   size=0;
	   currentNodeIndex=0;
	   }
	   int getSize(){
	     return size;
			}
	 void add(Component *comp){
	   Node *node=new Node;
	   node->comp=comp;
	   node->next=first;
	   first=node;

	   size++;
		 }
	 Boolean isEmpty(){
	     if(first==NULL||size==0)
	     return true;
	     else
	     return false;
			 }
	 Node* getFirstNode(){
	    return first;
			    }
	 Node* getCurrentNode(){

	     return this->get(currentNodeIndex);
				}
	 int indexOf(Component *comp){
	     Node *node;
	     if(!(this->isEmpty())){

	     for(int i=0;i<this->getSize();i++){
		  node=this->get(i);
		  if(node->comp==comp){

		       return i;

				       }

					     }
		  return -1;
		  }
	      else{

	       return -1;
		  }

				     }//function ends  here

	 Node* get(int index){
	  Node *currentNode ;
	 if(index<=this->size){
	    currentNode=first;

	    for(int i=0;i<index;i++){
		currentNode=currentNode->next;
				   }  }
				   else {
					 currentNode=NULL;
					}
		return currentNode;
			     }
	  void remove(Component *comp,int dt){
		 Node *node;
		 Node *prevNode;
	     for(int i=0;i<size;i++){
	     node=this->get(i);
	      if( node->comp==comp ){
		      if(dt==1){
			    delete node->comp;
				 }
		       if((i-1)>=0){
			     prevNode=this->get(i-1);
			     prevNode->next=node->next;
			     }
			     else{
				     //the first node is to be deleted
				   first=node->next;

				     delete node;
				 }

				 size--;
				       }
			else{
			    //comp does not exist
			    }
		    }

		       }
	  void remove(int i,int dt);
	       void	 operator ++(){

		this->currentNodeIndex++;

			      }
	   };


/**
*The Graphics Function is used to initialize the graphics system
*/
class Graphics {
   private:
   int gdriver, gmode, errorcode;

   public:
     Graphics(){
   registerbgidriver(EGAVGA_driver);
   registerbgifont(triplex_font);
   registerbgifont(sansserif_font);
   gdriver=VGA;
   gmode=VGAHI;

    /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode,"" );

   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1); /* terminate with an error code */
   }

	      }

   void drawComponent(Component *comp);
   void drawLine(int x1,int y1,int x2,int y2){
      line(x1,y1,x2,y2);
					      }
  
   void drawBar(int x1,int y1,int x2,int y2){
	bar(x1,y1,x2,y2);
		 }
   

   void dispose(){
   /* clean up */
   closegraph();

		 }

};//Graphics class ends here

 class ActionListener {
   public:virtual void  actionPerformed(ActionEvent *evt){

						          }
			};
 class Component{
	protected:

	Graphics* g;
	ActionListener *handler;
	int x,y;
	int boundaryType;
	int width,height;
	int fillColor;
	int outlineColor;
	int visible;
	int state;
	int parent;

	public :
	Llist *list;
	enum ComponentState{INACTIVE,ACTIVE};
	 Component(){
	 x=0;
	 y=0;
	 width=200;
	 height=100;
	 fillColor=EGA_WHITE;
	 outlineColor=EGA_DARKGRAY;
	 state=INACTIVE;
	 handler=NULL;
	// parent=false;
			    }
	Component(Graphics* g){
	 x=0;
	 y=0;
	 width=200;
	 height=100;
	 fillColor=EGA_WHITE;
	 outlineColor=EGA_DARKGRAY;
	 this->g=g;
	 visible=0;
	 boundaryType=REAL;
	 state=INACTIVE;
	 handler=NULL;
	// parent=false;
		  }
	friend Component* getSourceComponent(int,int,Component*);
	virtual Boolean  hasChild(){
	   // return parent;
				   }
	 Component(int x,int y,int width,int height,int bt,int fillcolor,int outlineColor,Graphics* g){
		       this->x=x;
		       this->y=y;
		       this->width=width;
		       this->height=height;
		       this->fillColor=fillColor;
		       this->outlineColor=outlineColor;
		       this->g=g;
		       visible=0;
		       boundaryType=bt;
		       state=INACTIVE;
		       handler=NULL;
		    }

		    void setBoundaryType(int bt){
		       this->boundaryType=bt;
					  }
		   void getBoundaryType(int &bt){
			 bt=this->boundaryType;
					  }
		  void setActionListener(ActionListener *handler){
			this->handler=handler;
								 }
		  ActionListener* getActionListener(){
		       return handler;
						     }
		 virtual void  changeState(int state){

						     }
		 virtual String isA(){

				     }
		  int getState(){
		   return this->state;
				}

		  void invokeActionListener(ActionEvent *evt){
		     
		       if(handler!=NULL)
		       handler->actionPerformed(evt);
							    }


	 void setfillColor(int col){

	     this->fillColor=col;
	                           }
	 void getFillColor(int& col ){
	   col=this->fillColor;
			             }
	 void setoutLineColor(int col){
	    this->outlineColor=col;
			              }
	 void getOutLineColor(int& col){
	    col=this->outlineColor;
				       }
	 void setLocation(int x,int y){
		 this->x=x;
		 this->y=y;

			              }
	 void getLocation(int& x,int& y){
	      x=this->x;
	      y=this->y;
			                }
	 void setGraphics(Graphics* g){
		 this->g=g;
				      }
	 void setSize(int width,int height){
		  this->width=width;
		  this->height=height;
			                   }
	 void getSize(int& width,int& height){
		  width=this->width;
		  height=this->height;

		                             }
	 void virtual setVisible(Boolean c){
	    //abstract

	                                    }

	 void virtual repaint(){
	     paint();
		               }

	     private:
	      void virtual paint(){
	     //abstract
		                  }

		};
class Label:public String,public Component{
   protected:
		 //Coordinates of the text
   int font;             //DEFAULT_FONT,TRIPLEX_FONT,etc.
   int direction;        //HORIZ_DIR or VERT_DIR
   int size;             //1,2,3 etc.
   int color;            //BLUE,RED,etc.
   int horzJustify;      //LEFT_TEXT etc.
   int vertJustify;       //BOTTOM_TEXT etc.
   int multx,divx;       //horizontal scale factors
   int multy,divy;       //vertical scale factors
   int labelType;
   public :
   enum LabelType{STATIC_IMMUTABLE,DYNAMIC_MUTABLE};
   Label(Graphics *g):String(),Component(g)
   {
   //an empty string

		   //position
    font=DEFAULT_FONT;     //font
    direction=HORIZ_DIR;   //horizontal or vertical
    size=2;                //character size ie dimension
    color=EGA_BLACK;           //character color
    horzJustify=LEFT_TEXT; //horizontal positioning
    vertJustify=TOP_TEXT;  //vertical positioning
    multx=1;divx=1;        //horizontal scale factors
    multy=1;divy=1;        //vertical scale factors
    labelType=STATIC_IMMUTABLE;
		     }
   
    void setLabelType(int type){
       labelType=type;
			       }
    int getLabelType(){
      return labelType;
		       }
    void setText(char *str){
	   String::String(str);

			    }
  
   Boolean hasChild(){
	  return false;
		     }
   String isA(){
       return String("Label");
		}
 

   void setFont(int f){
      this->font=f;
		  }
   int getFont(){
      return this->font;
		 }
   void setDirection(int d){
      this->direction=d;
			   }
   void setSize(int s){
       this->size=s;
		       }
   void setColor(int col){
	this->color=col;
		 }
   void setHJust(int hj){
	this->horzJustify=hj;
		  }
   void setVJustify(int vj){
      this->vertJustify=vj;
		    }
   void setHorzSize(int m,int d){
      this->size=0;
       this->multx=m;
      this->divx=d;
		     }
   void setVertSize(int m,int d){
       this->size=0;
       this->multy=m;
      this->divy=d;
		     }
    void repaint(){
	paint();

		   }
     void loadTextConfig(){
      settextstyle(font,direction,size);
      setcolor(color);
      settextjustify(horzJustify,vertJustify);
      setusercharsize(multx,divx,multy,divy);
			  }
     void setVisible(Boolean c){
	  if(c==true){
	      Component::visible=1;

		      }
	 else
	 {
		 Component::visible=0;

	  }
	     paint();
		       }

    private:

    void paint(){
    g->drawComponent(this);
      moveto(x,y);
      settextstyle(font,direction,size);
      setcolor(color);
      settextjustify(horzJustify,vertJustify);
      setusercharsize(multx,divx,multy,divy);
      outtext(str);
		}

	     };





 class Panel:public Component{



     public:
     Panel(Graphics *g):Component(g){
	list=new Llist();


	      }
      void addComponent(Component *comp){
	      list->add(comp);
			  }
      void remove(Component *comp,int dt){
	     list->remove(comp,dt);
		   }

     Boolean hasChild(){
	  return list->getSize()>0?true:false;
			 }
    String isA(){
	return String("Panel");
		 }
     void repaint(){
	paint();

		   }
     void setVisible(Boolean c){
	  if(c==true){
	      Component::visible=1;

		      }
	 else
	 {
		 Component::visible=0;

	  }
	     paint();
		       }

    private:

    void paint(){
	   int x,y;   // of the child components
	   int size=list->getSize();
	   Component *comp;
	 (g)->drawComponent(this);  //drawing the panel first
	 for(int i=0;i<size;i++){
	  comp=(list->get(i))->comp;
	
	  comp->setVisible(true);
				 }
		}
	     };

class Window:public Component{
 public:
 Label *label;
 protected:
 int handle;
 String title;
 Panel *panel;
 public :
    Window(Graphics *g):Component(g){
    label=new Label(g);
    this->title=NULL;
				    }
  Window(Graphics *g,Panel *panel):Component(g){
      label=new Label(g);
      this->panel=panel;
      this->title=NULL;
				  }
  void setPanel(Panel *panel){
    this->panel=panel;
			     }
  Panel*  getPanel(){
     return this->panel;
		    }
  void setTitle(String title){
	 this->title=title;
	 label->setText(title);
			     }
  Boolean hasChild(){
     return panel==NULL?false:true;
		    }
  String isA(){
    return String("Window");
	       }
 void repaint(){
	paint();

		   }
     void setVisible(Boolean c){
	  if(c==true){
	      Component::visible=1;

		      }
	 else
	 {
		 Component::visible=0;

	  }
	     paint();
		       }

    private:

    void paint(){

	 (g)->drawComponent(this);  //drawing the window first
	/* setcolor(EGA_BLACK);
	 setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	  g->drawLine(x,y+2,x+width,y+2);
	  g->drawLine(x,y+3,x+width,y+3);
	  g->drawLine(x,y+4,x+width,y+4);
	  g->drawLine(x,y+5,x+width,y+5);
	 g->drawLine(x,y+6,x+width,y+6);        TITLE BAR DESIGN #1
	 g->drawLine(x,y+7,x+width,y+7);
	 g->drawLine(x,y+9,x+width,y+9);  */

	 setcolor(EGA_BLACK);
	 setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	  g->drawLine(x,y+3,x+width,y+3);
	  g->drawLine(x,y+6,x+width,y+6);
	  g->drawLine(x,y+9,x+width,y+9);
	  g->drawLine(x,y+12,x+width,y+12);
	 g->drawLine(x,y+15,x+width,y+15);       // TITLE BAR DESIGN #2
	 g->drawLine(x,y+18,x+width,y+18);
	 g->drawLine(x,y+25,x+width,y+25);
	  setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	 g->drawLine(x,getmaxy()-20,x+width,getmaxy()-20);   //A SEPERATOR
	 if(title!=NULL){


	
	   label->loadTextConfig();

	   int textw=textwidth((char *)(title));
	   int texth=textheight((char *)(title));
	   int midx=(getmaxx()-textw)/2;
	
	   setcolor(EGA_WHITE);
	   g->drawBar(midx-5,0,midx+textw+0,(texth)+5);
	   label->loadTextConfig();
	   label->Component::setSize(textw+0,texth);

	   label->setLocation(midx,(15-(texth-5))/2);
	   label->setVisible(true);
	  
			}
			if(panel!=NULL)
	     panel->repaint();
		}

			     };

class TextField:public Component{
 public:
 Label *label;
 int state;
 TextField(Graphics *g):Component(g){
  label=new Label(g);
	     }
 String isA(){
    return String("TextField");
	     }
  Boolean hasChild(){
     return false;
		    }

 void repaint(){
	paint();

		   }
     void setVisible(Boolean c){
	  if(c==true){
	      Component::visible=1;

		      }
	 else
	 {
		 Component::visible=0;

	  }
	     paint();
		       }
     private:
       void paint(){
	   

		(g)->drawComponent(this);
     
       label->loadTextConfig();
       label->Component::setSize(width,height);
     
       label->setVisible(true);
		    }

				};


class Button:public Component{
  public:
   Label *label;
  protected:

  int state;
  int normalStateTextColor;
  int normalStateButtonColor;
  int changedStateTextColor;
  int changedStateButtonColor;
  public :
  Button(Graphics *g):Component(g){
    label=new Label(g);
    normalStateButtonColor=EGA_WHITE;
    normalStateTextColor=EGA_BLACK;
				   }
  void setText(String text){
     label->setText((char*)text);
			   }
  void setTextFont(int font){
      label->setFont(font);
			    }
  void setLocation(int x,int y){
	  Component::setLocation(x,y);
	  label->setLocation(x+2,y+7);
				}
  void setTextSize(int size){
	 
	  label->setSize(size);
			     }
  void setTextColor(int col){
	
	  label->setColor(col);
		      }
  void setButtonColor(int col){
	  
	  setfillColor(col);
	  setoutLineColor(col);
			}
  void setChangedStateButtonColor(int col){
	changedStateButtonColor=col;

				    }
  void setChangedStateTextColor(int col){
	 changedStateTextColor=col;
					}
    Boolean hasChild() {
	  return false;
			 }
   String isA(){
       return String("Button");
		}

  void changeState(int state){
	 this->state=state;
	 if(state==ACTIVE){
	    setTextColor(changedStateTextColor);
	   
	    setButtonColor(changedStateButtonColor);
	  
			   }
	  else{
	    setTextColor(normalStateTextColor);
	    setButtonColor(normalStateButtonColor);
	       }
			    }
 void repaint(){
	paint();

		   }
     void setVisible(Boolean c){
	  if(c==true){
	      Component::visible=1;

		      }
	 else
	 {
		 Component::visible=0;

	  }
	     paint();
		       }

  private:
  void paint(){
	(g)->drawComponent(this);
       label->setLocation(x+3,y+7);
       label->loadTextConfig();
       label->Component::setSize(width,height);
	label->Component::setoutLineColor(normalStateButtonColor);
	label->Component::setfillColor(normalStateButtonColor);
       label->setVisible(true);


	       }

			    };

 #endif