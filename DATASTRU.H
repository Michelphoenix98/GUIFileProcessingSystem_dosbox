#include <util.h>
#include <stdlib.h>


enum EmpCategory {AGENT,SCIENTIST,ANALYST,SECURITY};
class Employee{

protected:
 char name[40];//name of the employee
 unsigned int DOB; //date of birth of the employee
 char gender;//gender M,F
 char address[60];// residential address of the employee
 EmpCategory empCat;


 int ID; //ID of the employee (unique and alphanumeric)
 int status;//current status of the employee
 //int payGrade;//employee class or rank
 float basicPay;//the the basic pay of an employee
 float HRA;//the House-Rent-Allowance
 float DA;//the Dearness Allowance



 public:
 Employee(){ }

 void setEmpCat(int no){
     empCat=no;
			}

  EmpCategory getEmpCat(){
    return empCat;
			 }

 void setName(char* name){

    strcpy(this->name,name);

			 }
 char* getName(){

   return  name;
		}
  void setId(int ID){

    this->ID=ID;
		     }

  int  getId(){
    return  ID;
	      }
  void setDOB(unsigned int day,unsigned int month,unsigned int year){
     this->DOB= 512*(year-1980)+32*month+day;//code to optimize date to 2 bytes
								     }
  unsigned int  getDob(){
	return  ((DOB<<11)>>11);
			 }
  unsigned int getMob(){
	 return  ((DOB<<7)>>12);
			}
 unsigned int getYob(){
	 return (1980+(DOB>>9));
		       }

  void setGender(char gender){
     this->gender=gender;
		              }
  char getGender(){
      return this->gender;
		  }
  void setAddress(char* address){
  
    strcpy(this->address,address);

		                 }
  char* getAddress(){
       return address;
		    }

   void setBasicPay(float basicPay){
      this->basicPay=basicPay;
		                    }
   float getBasicPay(){
	return this->basicPay;
		      }
    void setStatus(int stat){
	  status=stat;
			     }
     int getStatus(){
	   return status;
		    }
   void setHRA(float percent){
	 this->HRA=(percent);
		              }
    int getHRA(){
	   return HRA;
		}
   void setDA(float percent){
	this->DA=(percent);
			    }
   int getDA(){
	   return DA;
	      }


	     };

