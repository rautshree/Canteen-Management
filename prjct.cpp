#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
using namespace std;
//***************************************************************
// CLASS USED IN PROJECT
//****************************************************************
class item
{
int itemno;
char name[50];
float price,qty,tax,dis;
public:
void create_item()
{
cout<<"\nPlease Enter The Item No. ";
cin>>itemno;
cout<<"\n\nPlease Enter The Name of The item ";
cin>>name;
cout<<"\nPlease Enter The Price of The item ";
cin>>price;
cout<<"\nPlease Enter The Discount (%) ";
cin>>dis;
}
void show_item()
{
cout<<"\nThe item No. "<<itemno;
cout<<"\nThe Name of The item : ";
puts(name);
cout<<"\nThe Price of The item : "<<price;
cout<<"\nDiscount : "<<dis;
}
int retitemno()
{
return itemno;
}
float retprice()
{
return price;
}
char* retname()
{
return name;
}
int retdis()
{
return dis;
}
}; //class ends here

//***************************************************************
// global declaration for stream object, object
//****************************************************************
fstream fp;
item it;
//***************************************************************
// function to write in file
//****************************************************************
void write_item()
{
char nitem;
do
{
fp.open("canteen.dat",ios::out|ios::app);
it.create_item();
fp.write((char*)&it,sizeof(item));
fp.close();
cout<<"\n\nThe Item Has Been Created ";
cout<<"\nDo you want to create new item (Y/N)";
cin>> nitem;
}while(nitem=='y'||nitem=='Y');
getch();
}
//***************************************************************
// function to read  records from file
//****************************************************************
void display_all()
{
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
fp.open("canteen.dat",ios::in);
while(fp.read((char*)&it,sizeof(item)))
{
it.show_item();
cout<<"\n\n====================================\n";
getch();
}
fp.close();
getch();
}
//***************************************************************
// function to read specific record from file
//****************************************************************
void display_sp(int n)
{
int flag=0;
fp.open("canteen.dat",ios::in);
while(fp.read((char*)&it,sizeof(item)))
{
if(it.retitemno()==n)
{
it.show_item();
flag=1;
}
}
fp.close();
if(flag==0)
cout<<"\n\nrecord not exist";
getch();
}
//***************************************************************
// function to modify record of file
//****************************************************************
void modify_item()
{
int no,found=0;
cout<<"\n\n\tTo Modify ";
cout<<"\n\n\tPlease Enter The Item No.";
cin>>no;
fp.open("canteen.dat",ios::in|ios::out);
while(fp.read((char*)&it,sizeof(item)) && found==0)
{
if(it.retitemno()==no)
{
it.show_item();
cout<<"\nPlease Enter The New Details of Item"<<endl;
it.create_item();
int pos=-1*sizeof(it);
fp.seekp(pos,ios::cur);
fp.write((char*)&it,sizeof(item));
cout<<"\n\n\t Record Updated";
found=1;
}
}
fp.close();
if(found==0)
cout<<"\n\n Record Not Found ";
getch();
}
//***************************************************************
// function to delete record of file
//****************************************************************
void delete_item()
{
int no;
cout<<"\n\n\n\tDelete Record";

cout<<"\n\nPlease Enter The Item no. of The Item You Want To Delete";
cin>>no;
fp.open("canteen.dat",ios::in|ios::out);
fstream fp2;
fp2.open("Temp.dat",ios::out);
fp.seekg(0,ios::beg);
while(fp.read((char*)&it,sizeof(item)))
{
if(it.retitemno()!=no)
{
fp2.write((char*)&it,sizeof(item));
}
}
fp2.close();
fp.close();
remove("canteen.dat");
rename("Temp.dat","canteen.dat");
cout<<"\n\n\tRecord Deleted ..";
getch();
}
//***************************************************************
// function to display all products price list
//****************************************************************
void menu()
{
fp.open("canteen.dat",ios::in);
if(!fp)
{
cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
cout<<"\n\n\n Program is closing ....";
getch();
exit(0);
}
cout<<"\n\n\t\t MENU\n\n";
cout<<"====================================================\n";
cout<<"P.NO.\t\tNAME\t\tPRICE\n";
cout<<"====================================================\n";
while(fp.read((char*)&it,sizeof(item)))
{
cout<<it.retitemno()<<"\t\t"<<it.retname()<<"\t\t"<<it.retprice()<<endl;
}
fp.close();
}
//***************************************************************
// function to place order and generating bill for item
//****************************************************************
void place_order()
{
int order_arr[50],quan[50],c=0;
float amt,damt,total=0;
char ch='Y';
menu();
cout<<"\n============================";
cout<<"\n PLACE YOUR ORDER";
cout<<"\n============================\n";
do
{
cout<<"\n\nEnter The Item No.: ";
cin>>order_arr[c];
cout<<"\nQuantity in number : ";
cin>>quan[c];
c++;
cout<<"\nDo You Want To Order Another Item ? (y/n)";
cin>>ch;
}while(ch=='y' ||ch=='Y');
cout<<"\n\nThank You For Placing The Order";getch();
cout<<"\n\n********************************INVOICE************************\n";
cout<<"\nItem No.\tItem Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
for(int x=0;x<=c;x++)
{
fp.open("canteen.dat",ios::in);
fp.read((char*)&it,sizeof(item));
while(!fp.eof())
{
if(it.retitemno()==order_arr[x])
{
amt=it.retprice()*quan[x];
damt=amt-(amt*it.retdis()/100);
cout<<"\n"<<order_arr[x]<<"\t"<<it.retname()
<<"\t"<<quan[x]<<"\t"<<it.retprice()<<"\t"<<amt<<"\t"<<damt;
total+=damt;
}
fp.read((char*)&it,sizeof(item));
}
fp.close();
}
cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
getch();
}
//***************************************************************
// INTRODUCTION FUNCTION
//****************************************************************
void intro()
{
cout<<endl<<endl;
cout<<endl<<endl<<endl;
cout<<"\t\t\t*****************************";
cout<<"\n\t\t\t* CANTEEN MANAGEMENT SYSTEM *";
cout<<"\n\t\t\t*****************************";
cout<<endl<<endl<<endl;
cout<<"\n\nSUBMITTED BY";
cout<<"\t\t\tSUMITED TO"<<endl;
cout<<"\nAjay Jha";
cout<<"\t\t\t Tej Sahi";
cout<<"\n\nPurnima Karki";
cout<<"\t\t\t Department of computer Science and Information Technology";
cout<<"\n\nSrijana Raut";
cout<<"\t\t\t New Summit College, Old-Baneshowr ";
getch();
}
//***************************************************************
// ADMINSTRATOR MENU FUNCTION
//****************************************************************
void admin_menu()
{

char ch2;
cout<<"\n\n\n\tADMIN MENU";
cout<<"\n\n\t1.CREATE ITEM";
cout<<"\n\n\t2.DISPLAY ALL ITEM";
cout<<"\n\n\t3.QUERY ";
cout<<"\n\n\t4.MODIFY ITEM";
cout<<"\n\n\t5.DELETE ITEM";
cout<<"\n\n\t6.VIEW ITEM MENU";
cout<<"\n\n\t7.BACK TO MAIN MENU";
cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
ch2=getche();
switch(ch2)
{
case '1':
write_item();
break;
case '2': display_all();
break;
case '3':
int num;
cout<<"\n\n\tPlease Enter The Item No. ";
cin>>num;
display_sp(num);
break;
case '4': modify_item();break;
case '5': delete_item();break;
case '6': menu();
getch();
case '7':
 break;
default:
cout<<"\a";admin_menu();
}
}
//***************************************************************
// THE MAIN FUNCTION OF PROGRAM
//****************************************************************
int main()
{
char ch;
char yes;
intro();
top:
do
{

cout<<"\n\n\n\tMAIN MENU";
cout<<"\n\n\t01. CUSTOMER";
cout<<"\n\n\t02. ADMINISTRATOR";
cout<<"\n\n\t03. EXIT";
cout<<"\n\n\tPlease Select Your Option (1-3) ";
ch=getch();
switch(ch)
{
case '1':
menu();
cout<<"Do you like to place an order(Y/N)"<<endl;
cin>>yes;
if(yes=='y'||yes=='Y')
{
place_order();
}
else
goto top;
getch();
break;

case '2': admin_menu();
break;
case '3':exit(0);
default :cout<<"\a";
}
}while(ch!='3');
}
