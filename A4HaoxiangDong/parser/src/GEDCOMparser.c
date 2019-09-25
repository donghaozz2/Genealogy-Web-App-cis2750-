/**
* CIS2750 F2017

 * Assignment 1

 * Haoxiang Dong 0850990  hdong04

 * This file contains the implementation of the linked List API 

 * This implementation is based on the List API that I implemented in my Assignment 2 for CIS2520, whcih I took

 * all code is new. 

 * my current CIS2750 professor, Denis Nikitenko.

 */

#include "GEDCOMparser.h"
# include <stdio.h>
# include <stdlib.h>

GEDCOMerror findindiv(GEDCOMobject * obj,char * fileName,List * famlist2,List* peoplelist2);
int findallf(char* fileName,List * famlist2);
void nothing();
int nthings();
char * iput();
char * getfullname(void* toBePrinted);
void putinother(List *otherlist,char* data1);
char* printhead(const GEDCOMobject* obj);

GEDCOMerror findhead(GEDCOMobject * obj,char * fileName);
Submitter* findtheu(char* subname,char *fileName);
GEDCOMerror findthefamily(GEDCOMobject * obj,char * fileName,List* peoplelist2);
char * printSubmitte(Submitter* sub);

GEDCOMerror lastline(char * fileName);


/////////////////////
char * getfullnamec(void* toBePrinted);

GEDCOMerror lastline(char * fileName)
{
	FILE *fp;
	int i=0;
		GEDCOMerror errreturn;
	if((fp=fopen(fileName,"r"))==NULL)
	{

		errreturn.type=1;
		errreturn.line=-1;
		
		return errreturn;
		
	}

	char * data;
	data=malloc(1001);


	char * first;
	
	
	

	char * end="\r \n";
	char back[1000];

	while(!feof(fp))
	{
		fgets(data,1000,fp);
		strcpy(back,data);
		
	
		first=strtok(back,end);
		

		if(strcmp(first,"0")==0)
		{
			
			first=strtok(NULL,end);
			if(strcmp(first,"TRLR")==0)
			{		
				i=i+1;
			}
		}

	}
	free(data);
	fclose(fp);
	if(i==0)
	{
		errreturn.type=2;
		errreturn.line=-1;
		return errreturn;
	}
	errreturn.type=0;
	errreturn.line=0164;
	return errreturn;
}
/*
int main()
{

	GEDCOMobject * obj;
	GEDCOMerror errreturn;
	char * name="shakespeare.ged";
	
	errreturn=createGEDCOM(name,&obj);
	
	char* data;
	data=printGEDCOM(obj);
	puts(data);

	errreturn.type=1;
	errreturn.line=164;
	
	name=printError(errreturn);
	
	return 0;

}
*/



GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj)
{

	GEDCOMerror errreturn;
	ErrorCode backerr;

	if(fileName==NULL)
	{
		
		backerr=1;
		errreturn.type=backerr;
		errreturn.line=-1;
		
		return errreturn;

	}

	int fm=0;
	List famlist2=initializeList(&iput,&nothing,&nthings);
	fm=findallf(fileName,&famlist2);
	
	List famlist=initializeList(&printFamily,&deleteFamily,&nthings);
	
	List peoplelist2=initializeList(&iput,&nothing,&nthings);
	
	for(int y=0;y<fm;y++)
	{
		Family * new= malloc(sizeof(Family));
		
		insertBack(&famlist, (void*)new);
		
	}
	
		
	int x;
	if(fileName!=NULL)
	{
		x= strlen(fileName);
	}
	else
	{
		x=0;
	}
	if(fileName[x-1]!='d'||fileName[x-2]!='e'||fileName[x-3]!='g'||fileName[x-4]!='.'||x==0)
	{
		backerr=1;
		errreturn.type=backerr;
		errreturn.line=-1;
		return errreturn;
	}
	
	GEDCOMobject * tmpcal= malloc(sizeof(GEDCOMobject));
	tmpcal->families=famlist;
	
	 errreturn=lastline(fileName);
	 if(errreturn.type!=0)return errreturn;

	errreturn=findhead(tmpcal,fileName);


	
	
		
	if(errreturn.type!=0)return errreturn;
	
	
	
	errreturn=findindiv(tmpcal,fileName,&famlist2,&peoplelist2);
	
	
	if(errreturn.type!=0)return errreturn;
	
	if(fm!=0)
	{
		errreturn=findthefamily(tmpcal,fileName,&peoplelist2);

		if(errreturn.type!=0)return errreturn;
		
	
	}
	/*
	int t=0;
	t=getLength(tmpcal->individuals);
	printf("tmp %d\n",t);
	t=getLength(tmpcal->families);
	printf("fam %d\n",t);
*/

	

	
	*obj=tmpcal;
	
/////////////////////////////////////////////////
	

	/////////////////////////////////////////////
	return errreturn;
}
char* printGEDCOM(const GEDCOMobject* obj)
{
	if(obj==NULL)
	{
		return NULL;
	}
	char* data;
	List p;
	int x=0;
	int tot=0;
	
	
	data=printhead(obj);


	if(data!=NULL)
	{
		x=strlen(data);
		tot=x+tot;
		free(data);
	}
	p=obj->individuals;

		data=toString(p);

	

	if(data!=NULL)
	{
		x=strlen(data);
	
		tot=x+tot;
		free(data);
	}
	
	
	
	p=obj->families;

		data=toString(p);

	if(data!=NULL)
	{
		x=strlen(data);
		tot=x+tot;
		free(data);
	}
	
	char* back;
	back=malloc(tot+9000);

	data=printhead(obj);
	
	if(data!=NULL)
	{
		strcpy(back,data);
		free(data);
	}
	p=obj->individuals;

		data=toString(p);


	if(data!=NULL)
	{
		strcat(back,data);
		free(data);
	}
	p=obj->families;

		data=toString(p);


	if(data!=NULL)
	{
		strcat(back,data);
		free(data);
	}
	return back;
}




int findallf(char* fileName,List * famlist2)
{
	FILE *fp;
	int i=0;
	if((fp=fopen(fileName,"r"))==NULL)
	{
		
		return -1;
	}

	char * data;
	data=malloc(1001);


	char * first;
	
	
	fgets(data,1000,fp);

	char * end="\r \n";
	char back[1000];
	char indata[50];


	
	while(!feof(fp))
	{
	
		strcpy(back,data);
		
	
		first=strtok(back,end);
		

		if(first==NULL)
		{
		}
		else if(strcmp(first,"0")==0)
		{
			
			first=strtok(NULL,end);
			if(first!=NULL)
			{
				
				strcpy(indata,first);
			}
			first=strtok(NULL,end);
			if(first==NULL)
			{
			}
			else if(strcmp(first,"FAM")==0)
			{
				char * putlist;
				putlist=malloc(40);
				strcpy(putlist,indata);
				
				
				insertBack(famlist2, putlist);
				
				i=i+1;
			}
		}

		fgets(data,1000,fp);
	}
	free(data);
	fclose(fp);
	return i;
}



char * iput()
{
	return"null";
}
int nthings()
{
	return 1;
}
void nothing(void * toBeDeleted)
{
	if(toBeDeleted==NULL)
	{
		return;
	}
	char * de;
	de=(char*)toBeDeleted;
	free(de);
	return;
	
}








void putinother(List *otherlist,char* data1)
{
	
	char data[900];
	strcpy(data,data1);

	char* first;
	first=strtok(data," ");
	first=strtok(NULL," ");
	if(first==NULL)return;

	int x=0;
	Field * newinpeople;
	newinpeople=malloc(sizeof(Field));
	char * intag;
	x=strlen(first);
	intag=malloc(x+2);
	strcpy(intag,first);
	newinpeople->tag=intag;

	first=strtok(NULL,"\r\n");
	if(first==NULL)return;
	char * invalue;
	x=strlen(first);
	invalue=malloc(x+2);
	strcpy(invalue,first);
	newinpeople->value=invalue;
	insertBack(otherlist,newinpeople);
	return;
}

GEDCOMerror findthefamily(GEDCOMobject * obj,char * fileName,List* peoplelist2)
{

	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0164;
	List people;
	people=obj->individuals;
	Node * fam;
	Node * fam1;

	List famlist;
	famlist=obj->families;

	Node* tag1;
	tag1=famlist.head;
	int pass=0;

	FILE *fp;

	if((fp=fopen(fileName,"r"))==NULL)
	{
		errreturn.type=0;
		errreturn.line=0164;
		return errreturn;
	}

	int x=0;
 	char * data;
	data=malloc(1001);
	char * first;
	fgets(data,1000,fp);
	char back[1000];

	
	
	Family * newpeople;

	newpeople=tag1->data;

	int eventon=0;
	int peopleon=0;

	List eventlist;
	List fieldevent;
	List childlist;
	List fieldpeople;

	Event* newevent;
	
	char eventname[20];
	
	while(!feof(fp))
	{
		strcpy(back,data);
		
		first=strtok(back," ");
		
		
		if(strcmp(first,"0")==0)
		{
			if(eventon==1)
			{
				newevent->otherFields=fieldevent;
				insertBack(&eventlist,newevent);
				eventon=0;
			}
			if(peopleon==1)
			{
				
				newpeople->events=eventlist;
				newpeople->children=childlist;
				newpeople->otherFields=fieldpeople;
				if(tag1->next!=NULL)
				{
					tag1=tag1->next;
					newpeople=tag1->data;
				}
				
			}
			peopleon=0;

			first=strtok(NULL," ");
			first=strtok(NULL,"\r \n");
			if(first==NULL)
			{

			}
			else if(strcmp(first,"FAM")==0)
			{
				peopleon=1;
				eventlist=initializeList(&printEvent,&deleteEvent,&nthings);
				fieldpeople=initializeList(&printField,&deleteField,&nthings);
				childlist=initializeList(&getfullname,&deleteIndividual,&nthings);
				
			}
		
		}

		if(peopleon==1&&strcmp(first,"1")==0)
		{

			pass=0;
			first=strtok(NULL,"\r \n");
			if(eventon==1)
			{
				newevent->otherFields=fieldevent;
				insertBack(&eventlist,newevent);
				eventon=0;
			}
			if(first==NULL)
			{

			}
			else if(strcmp(first,"HUSB")==0)
			{
				pass=1;
				first=strtok(NULL,"\r \n");
				if(first==NULL)
				{
				}
				else
				{
					fam=people.head;
					fam1=peoplelist2->head;
					char * fam1data;
					
					while(fam1!=NULL&&fam!=NULL)
					{
						fam1data=fam1->data;
						if(strcmp(first,fam1data)==0)
						{
							Individual* target;
							target=fam->data;
							newpeople->husband=target;
						}
						fam=fam->next;
						fam1=fam1->next;
					}
				}
			}
			else if(strcmp(first,"WIFE")==0)
			{
				pass=1;
				first=strtok(NULL,"\n \r");
				if(first==NULL)
				{
				}
				else
				{
					fam=people.head;
					fam1=peoplelist2->head;
					char * fam1data;
					
					while(fam1!=NULL&&fam!=NULL)
					{
						fam1data=fam1->data;
						if(strcmp(first,fam1data)==0)
						{
							Individual* target;
							target=fam->data;
							newpeople->wife=target;
						}
						fam=fam->next;
						fam1=fam1->next;
					}
				}
			}
			else if(strcmp(first,"CHIL")==0)
			{
				
				pass=1;
				
				first=strtok(NULL,"\r \n");
				if(first==NULL)
				{
				}
				else
				{
					fam=people.head;
					fam1=peoplelist2->head;
					char * fam1data;
					
					while(fam1!=NULL&&fam!=NULL)
					{
						fam1data=fam1->data;

						if(strcmp(first,fam1data)==0)
						{
							

							Individual* target;
							target=fam->data;
							insertBack(&childlist,target);
							
						}
						fam=fam->next;
						fam1=fam1->next;
					}
				}
			}




			if(pass==0)
			{
				strcpy(eventname,first);
				first=strtok(NULL,"\r \n");
				if(first==NULL)
				{
					eventon=1;
					fieldevent=initializeList(&printField,&deleteField,&nthings);
					newevent=malloc(sizeof(Event));
					strcpy(newevent->type,eventname);
				}
				else
				{
					putinother(&fieldpeople,data);
				}
			}

		}

		else if(eventon==1&&strcmp(first,"2")==0)
		{
			first=strtok(NULL," ");
			if(first==NULL)
			{

			}
			else if(strcmp(first,"DATE")==0)
			{
				first=strtok(NULL,"\n\r");
				if(first!=NULL)
				{
					x=strlen(first);
					char * eventdate;
					eventdate=malloc(x+2);
					strcpy(eventdate,first);
					newevent->date=eventdate;
				}
			}
			else if(strcmp(first,"PLAC")==0)
			{
				first=strtok(NULL,"\n\r");
				if(first!=NULL)
				{
					x=strlen(first);
					char * eventplac;
					eventplac=malloc(x+2);
					strcpy(eventplac,first);
					newevent->place=eventplac;
				}
			}
			else
			{
				putinother(&fieldevent,data);

			}
		}

		fgets(data,1000,fp);
	}
	free(data);
	fclose(fp);
	
	return errreturn;

}




GEDCOMerror findhead(GEDCOMobject * obj,char * fileName)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0164;
	FILE *fp;
	int encods=0;
	int sources=0;
	int versions=0;
	int submits=0;
	int lines=0;
	int line=0;
	int level=0;
	int cha=0;
	
	if((fp=fopen(fileName,"r"))==NULL)
	{
		errreturn.type=1;
		errreturn.line=-1;
		return errreturn;
	}
	
	//puts(fileName);
	Header* newhead=malloc(sizeof(Header));
	char * data;
	data=malloc(1001);
	char * first;
	int x=0;
	fgets(data,1000,fp);
	char back[1000];
	char * subname;
	
	List otherlist=initializeList(&printField,&deleteField,&nthings);
	strcpy(back,data);
	first=strtok(back," ");
	if(strcmp(first,"0")!=0)
	{
		errreturn.type=3;
		errreturn.line=722;
		return errreturn;
	}
	first=strtok(NULL,"\r \n");
	if(strcmp(first,"HEAD")!=0)
	{
		errreturn.type=2;
		errreturn.line=-1;
		return errreturn;
	}
	fgets(data,1000,fp);
	line=2;
	while(!feof(fp))
	{
		
		strcpy(back,data);
		x=strlen(back);
		
		if(x>200){
			errreturn.line=line;
			
			lines=lines+1;
			
		}
		first=strtok(back," ");
		
	//
				cha=atoi(first);
				
				if(cha-level<-1||cha-level>1)
				{
					free(data);
					fclose(fp);
					errreturn.type=4;
					errreturn.line=line;
					return errreturn;
	
				}
				level=cha;
//
		
		//printf("-----------------------------------\n");
		//puts(data);
		
		if(strcmp(first,"0")==0)
		{
			break;
		}
		if(strcmp(first,"1")==0)
		{	
			first=strtok(NULL,"\r \n");

			if(first==NULL)
			{
			
			}
			else if(strcmp(first,"SOUR")==0)
			{
				first=strtok(NULL,"\r\n");
				if(first!=NULL)
				{
					sources=1;
					strcpy(newhead->source,first);
				}
			}
			else if(strcmp(first,"GEDC")==0)
			{
				
				first=strtok(NULL,"\r \n");
				if(first==NULL)
				{
					
					float vid;
					fgets(data,1000,fp);
					line=1+line;
					strcpy(back,data);
					
					
					x=strlen(back);
					
					if(x>200){
						errreturn.line=line;
			
						lines=lines+1;
			
					}
					first=strtok(back," ");
		
	//////////////////////////
					cha=atoi(first);
			/////////////////////////////////////////der	
					if(cha-level<-1||cha-level>1)
					{
						free(data);
						fclose(fp);
						errreturn.type=4;
						errreturn.line=line;
						return errreturn;
	
					}
					level=cha;
					
					
					
					
					first=strtok(NULL," ");
					if(strcmp(first,"VERS")==0)
					{
						versions=1;
						first=strtok(NULL,"\r \n");
						first[3]='\0';
						vid=atof(first);
					}
					else
					{
						vid=5.5;
					}
					newhead->gedcVersion=vid;

				}
			}
			else if(strcmp(first,"CHAR")==0)
			{
				first=strtok(NULL,"\r \n");
				if(first!=NULL)
				{
					encods=1;
					if(strcmp(first,"ANSEL")==0)
					{
						x=0;
					}
					else if(strcmp(first,"UTF-8")==0)
					{
						x=1;
					}
					else if(strcmp(first,"UNICODE")==0)
					{
						x=2;
					}
					else if(strcmp(first,"ASCII")==0)
					{
						x=3;
					}
					newhead->encoding=x;
				}
			}
			else if(strcmp(first,"SUBM")==0)
			{
				
				first=strtok(NULL,"\r \n");
				
				if(first!=NULL)
				{
					submits=1;
					subname=malloc(50);
					strcpy(subname,first);
					
					

				}
				
			}
			
			else
			{
				
				
				putinother(&otherlist,data);
			}

		}
		else
		{
				
				
				putinother(&otherlist,data);
		}
		fgets(data,1000,fp);
		line=1+line;
	}
	free(data);
	fclose(fp);
	if(sources==0)
	{
		errreturn.type=3;
		errreturn.line=854;
		return errreturn;
	}
	if(versions==0)
	{
		errreturn.type=3;
		errreturn.line=860;
		return errreturn;
	}
	if(encods==0)
	{
		errreturn.type=3;
		errreturn.line=866;
		return errreturn;
	}
	if(submits==0)
	{
		errreturn.type=3;
				errreturn.line=888;
		return errreturn;
	}
	if(lines!=0)
	{
		
		errreturn.type=4;

		return errreturn;
	}
	Submitter *subnew;
	
	if(subname==NULL)
	{
		//puts(subname);
		errreturn.type=2;
		errreturn.line=-1;
		return errreturn;
	}
	
	subnew=findtheu(subname,fileName);
	
	if(subnew==NULL||subname==NULL)
	{
		
		errreturn.type=2;
		errreturn.line=-1;
		return errreturn;
	}
	newhead->otherFields=otherlist;
	newhead->submitter=subnew;
	obj->header=newhead;
	obj->submitter=subnew;
	return errreturn;
}



Submitter* findtheu(char* subname,char *fileName)
{
	FILE *fp;
	if((fp=fopen(fileName,"r"))==NULL)
	{

		return NULL;
	}

	char * data;
	data=malloc(1001);
	char * first;
	char * name;
	fgets(data,1000,fp);
	char back[1000];

	Submitter* newsub;
	int u=0;
	List otherlist;
	
	while(!feof(fp))
	{
		strcpy(back,data);
		first=strtok(back," ");
		if(strcmp(first,"0")==0)
		{
			first=strtok(NULL," ");
			name=first;
			first=strtok(NULL,"\n \r");
			if(first==NULL||name==NULL)
			{

			}
			else if(strcmp(first,"SUBM")==0)
			{
				
				if(strcmp(name,subname)==0)
				{
					u=1;
					fgets(data,1000,fp);
					newsub=malloc(sizeof(Submitter));
					otherlist=initializeList(&printField,&deleteField,&nthings);
					while(!feof(fp))
					{
						strcpy(back,data);
						first=strtok(back," ");

						if(strcmp(first,"0")==0)
						{
							free(data);
							fclose(fp);
							newsub->otherFields=otherlist;
							return newsub;

						}
						else if(strcmp(first,"1")==0)
						{
							first=strtok(NULL," ");
							if(strcmp(first,"NAME")==0)
							{
								first=strtok(NULL,"\r \n");
								if(first==NULL)return NULL;
								strcpy(newsub->submitterName,first);
							}
							else if(strcmp(first,"ADDR")==0)
							{
								first=strtok(NULL,"\r\n");
								if(first==NULL)return NULL;
								strcpy(newsub->address,first);
							}
							else
							{
								putinother(&otherlist,data);
							}
						}
						else
						{
							putinother(&otherlist,data);
						}

						fgets(data,1000,fp);
					}

				}
			}
		}
		fgets(data,1000,fp);
	}
	
	free(data);
	fclose(fp);
	if(u==0)
	{
		newsub=NULL;
	}
	if(newsub!=NULL)
	{
		
		newsub->otherFields=otherlist;
	}
	return newsub;
}














GEDCOMerror findindiv(GEDCOMobject * obj,char * fileName,List * famlist2,List* peoplelist2)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0164;

	FILE *fp;

	if((fp=fopen(fileName,"r"))==NULL)
	{
		errreturn.type=0;
		errreturn.line=0164;
		return errreturn;
	}
	 
	int peopleon=0;
	int eventon=0;

	char * data;
	data=malloc(1001);


	char * first;
	
	int x=0;
	fgets(data,1000,fp);

	char * end="\r \n";
	char back[1000];
	char eventname[100];
	int pass=0;
	char idc[200];
	char * IDP;

	List famlist;
	famlist=obj->families;

	List peoplelist;
	//list peoplelist2;
	peoplelist=initializeList(&printIndividual,&deleteIndividual,&nthings);
	obj->individuals=peoplelist;
	Individual * newpeople;

	List eventlist;

	List peoplefamlist;

	List fieldpeople;






	List fieldevent;

	Event * newevent;

	Node* fam;
	Node* fam1;

	Family * datafam;

	int t=0;
	while(!feof(fp))
	{
		strcpy(back,data);
		
		first=strtok(back,end);
		
		
		if(strcmp(first,"0")==0)
		{
			if(eventon==1)
			{
				newevent->otherFields=fieldevent;
				insertBack(&eventlist,newevent);
				eventon=0;
			}
			if(peopleon==1)
			{
				t=0;
				//char* date;
				newpeople->events=eventlist;
				newpeople->families=peoplefamlist;
				
				newpeople->otherFields=fieldpeople;

				insertBack(&peoplelist,newpeople);
				obj->individuals=peoplelist;
			}
			peopleon=0;

			first=strtok(NULL,end);
			strcpy(idc,first);
			first=strtok(NULL,end);
			if(first==NULL)
			{

			}
			else if(strcmp(first,"INDI")==0)
			{
				IDP=malloc(90);
				strcpy(IDP,idc);
				insertBack(peoplelist2,IDP);
				peopleon=1;
				

				newpeople= malloc(sizeof(Individual));
				eventlist=initializeList(&printEvent,&deleteEvent,&nthings);
				
				fieldpeople=initializeList(&printField,&deleteField,&nthings);
				
				peoplefamlist=initializeList(&printFamily,&deleteFamily,&nthings);

			}
		
		}

		if(peopleon==1&&strcmp(first,"1")==0)
		{

			pass=0;
			first=strtok(NULL,end);
			
			if(eventon==1)
			{
				newevent->otherFields=fieldevent;
				insertBack(&eventlist,newevent);
				eventon=0;
			}
			if(first==NULL)
			{

			}
			else if(strcmp(first,"NAME")==0)
			{
				pass=1;

				first=strtok(NULL," /");
				
				if (first==NULL) strcpy(first,"NULL");
	
				
				

				x=strlen(first);
				char * gname;
				gname=malloc(x+2);
				strcpy(gname,first);
				newpeople->givenName=gname;
				first=strtok(NULL,"/");
				
				
				if (first==NULL) strcpy(first,"NULL");

				x=strlen(first);
				char * sname;
				sname=malloc(x+2);
				strcpy(sname,first);
				newpeople->surname=sname;

			}
			else if(strcmp(first,"FAMS")==0||strcmp(first,"FAMC")==0)
			{
				pass=1;
				first=strtok(NULL,end);
				if(first==NULL)
				{
				}
				else
				{
			
					
					fam=famlist.head;
					fam1=famlist2->head;
					char * fam1data;
					int e=0;
					t=t+1;
					
					while(fam1!=NULL&&fam!=NULL)
					{
						fam1data=fam1->data;
						if(strcmp(first,fam1data)==0)
						{

							
							datafam=fam->data;
							insertBack(&peoplefamlist,datafam);
							e=e+1;
							
						}
						fam=fam->next;
						fam1=fam1->next;
					}
				}
			}




			if(pass==0)
			{
				strcpy(eventname,first);
				first=strtok(NULL,end);
				if(first==NULL)
				{
					
					eventon=1;
					fieldevent=initializeList(&printField,&deleteEvent,&nthings);
					newevent=malloc(sizeof(Event));
					strcpy(newevent->type,eventname);
					char * nuo=NULL;
					newevent->date=nuo;
					newevent->place=nuo;
					
				}
				else
				{
					putinother(&fieldpeople,data);


				}
			}

		}

		else if(eventon==1&&strcmp(first,"2")==0)
		{
			first=strtok(NULL,end);
			if(first==NULL)
			{

			}
			else if(strcmp(first,"DATE")==0)
			{
				first=strtok(NULL,"\n\r");
				if(first!=NULL)
				{
					x=strlen(first);
					char * eventdate;
					eventdate=malloc(x+2);
					strcpy(eventdate,first);
					newevent->date=eventdate;
				}
			}
			else if(strcmp(first,"PLAC")==0)
			{
				first=strtok(NULL,"\r\n");
				if(first!=NULL)
				{
					x=strlen(first);
					char * eventplac;
					eventplac=malloc(x+2);
					strcpy(eventplac,first);
					newevent->place=eventplac;
				}
			}
			else
			{

				putinother(&fieldevent,data);

			}
		}

		fgets(data,1000,fp);
	}
	free(data);
	fclose(fp);
	obj->individuals=peoplelist;

	return errreturn;


}


/////////////////////////////////////




//////////////////////////////////////

char* printField(void* toBePrinted)
{

	if(toBePrinted==NULL)
	{
		return NULL;
	}

	Field * anfield;
	anfield=(Field*)toBePrinted;
	char * printreturn;
	char * targs;
	char * values;
	int x=0;
	int y=0;
	
	targs=anfield->tag;
	if(targs==NULL)
	{
		return NULL;
	}
	values=anfield->value;
	if(values==NULL)
	{
		return NULL;
	}
	if(targs!=NULL)
	{
		x=strlen(targs);
	}
	else
	{
		x=0;
	}
	if(values!=NULL)
	{
		y=strlen(values);
	}
	else
	{
		y=0;
	}
	
	x=x+y+400;
	printreturn=malloc(x);
	strcpy(printreturn,"Field\n");
	strcat(printreturn,"tag: ");
	strcat(printreturn,targs);
	strcat(printreturn,"\n");
	strcat(printreturn,"value: ");
	strcat(printreturn,values);
	strcat(printreturn,"\n");

	return printreturn;
}
char* printEvent(void* toBePrinted)
{
	
	if(toBePrinted==NULL)
	{
		return NULL;
	}
	char some[1000];
	char * erenturn;
	char * eother;
	erenturn=malloc(9000);
	strcpy(erenturn,"event:\n");

	Event * aevent;
	aevent=(Event*)toBePrinted;

	strcpy(some,aevent->type);
	strcat(erenturn,"type: ");
	strcat(erenturn,some);
	strcat(erenturn,"\n");

	char* date;
	date=aevent->date;
	if(date!=NULL)
	{
		strcpy(some,aevent->date);
		strcat(erenturn,"date: ");
		strcat(erenturn,some);
		strcat(erenturn,"\n");
	}
	date=aevent->place;
	if(date!=NULL)
	{
		strcpy(some,aevent->place);
		strcat(erenturn,"place: ");
		strcat(erenturn,some);
		strcat(erenturn,"\n");	
	}
	List otherlist;
	otherlist=aevent->otherFields;
	eother=toString(otherlist);
	strcat(erenturn,"other: ");
	
	
	if(eother!=NULL)
	{
		strcat(erenturn,eother);
		free(eother);
	}
	strcat(erenturn,"\n");	
	

	return erenturn;

}

char* printFamily(void* toBePrinted)
{
	
	if(toBePrinted==NULL)
	{
		return NULL;
	}
	
	Family* new;
	new=(Family*)toBePrinted;
	char * preturn;
	preturn=malloc(9000);

	char * somename;
	Individual * somepeople;
	
	
	
	if(new->wife!=NULL)
	{
		somepeople=new->wife;

		somename=getfullname(somepeople);

		strcpy(preturn,"\n\none fam\n");
		if(somename!=NULL)
		{
			strcat(preturn,"wife:");
			strcat(preturn,somename);
		}
	

		if(somename!=NULL)
		{
			free(somename);
		}	
	}





	if(new->husband!=NULL)
	{
		somepeople=new->husband;
		somename=getfullname(somepeople);
		if(somename!=NULL)
		{
			strcat(preturn,"husband:");
			strcat(preturn,somename);
		}

		if(somename!=NULL)
		{
			free(somename);
		}
	
}
	
	
	
	
	List child;
	child=new->children;
	somename=toString(child);
	strcat(preturn,"children:");
	
	if(somename!=NULL)
	{
		strcat(preturn,somename);
		free(somename);
	}
	strcat(preturn,"\n");
	List alist;
	alist=new->events;
	somename=toString(alist);
	
	if(somename!=NULL)
	{
				
			strcat(preturn,"events:\n");
			strcat(preturn,somename);
			free(somename);
	}

	
	alist=new->otherFields;
	somename=toString(alist);
	if(somename!=NULL)
	{
			strcat(preturn,"Fields:\n");
			strcat(preturn,somename);
			free(somename);
	}
	
	return preturn;
}

char * getfullname(void* toBePrinted)
{
	
	if(toBePrinted==NULL)
	{
		
		return NULL;
	}
	Individual* new;
	new=(Individual*)toBePrinted;
	char * greturn;
	greturn=malloc(220);
	
	if(new->givenName!=NULL)
	{
		
		strcpy(greturn,new->givenName);
		strcat(greturn," ");
	}
	
	if(new->surname!=NULL)
	{
		
		strcat(greturn,new->surname);
		strcat(greturn,"\n");

	}
	
	return greturn;

}
char * getfullnamec(void* toBePrinted)
{
	
	if(toBePrinted==NULL)
	{
		
		return NULL;
	}
	Individual* new;
	new=(Individual*)toBePrinted;
	char * greturn;
	greturn=malloc(220);
	
strcpy(greturn,"");
	
	if(new->surname!=NULL)
	{
		
		strcat(greturn,new->surname);
		//strcat(greturn,"\n");

	}
	if(new->givenName!=NULL)
	{
		
		strcat(greturn,new->givenName);
		//strcat(greturn," ");
	}
	return greturn;

}
char* printIndividual(void* toBePrinted)
{
	
	
	Individual* new;
	new=(Individual*)toBePrinted;
	char * peoplereturn;
	
	List events1;
	
	List otherFields1;
	events1=new->events;

	otherFields1=new->otherFields;
	
	int x=0;
	char* name;
	name=getfullname(new);
	
	if(name!=NULL)
	{
		x=strlen(name);
	}
	else
	{
		x=0;
	}

	
	char* eventslist;
	eventslist=toString(events1);

	if(eventslist!=NULL)
	{
		x=strlen(eventslist)+x;
	}

	
	char* otherFieldslist;
	otherFieldslist=toString(otherFields1);
	if(otherFieldslist!=NULL)
	{
		x=strlen(otherFieldslist)+x;
	}
	else
	{
	}
	

	
	peoplereturn=malloc(x+900);
	strcpy(peoplereturn,"\n\nonepeople: \n");
	if(name!=NULL)
	{
		strcat(peoplereturn,name);
	}
	if(eventslist!=NULL)
	{
		strcat(peoplereturn,eventslist);
	}

	if(otherFieldslist!=NULL)
	{
		strcat(peoplereturn,otherFieldslist);
	}
	
	if(name!=NULL)
	{
		free(name);
	}
	if(eventslist!=NULL)
	{
		free(eventslist);
	}
/*
		List families1;
	families1=new->families;
	char* familieslist;
	familieslist=toString(families1);
	if(familieslist!=NULL)
	{
		x=strlen(familieslist)+x;
	}
	else
	{
	}
	if(familieslist!=NULL)
	{
		strcat(peoplereturn,familieslist);
	}
	if(familieslist!=NULL)
	{
		free(familieslist);
	}
	*/
	if(otherFieldslist!=NULL)
	{
		free(otherFieldslist);
	}
	return peoplereturn;
}

char* printhead(const GEDCOMobject* obj)
{
	
	Header * phead;
	phead=obj->header;
	if(phead==NULL)
	{
		return NULL;
	}
	char data[9000];
	char* olddata;
	char str[50];

	strcpy(data,"header: \n source: ");

	strcat(data,phead->source);
	strcat(data,"\n gedcVersion: ");

	sprintf(str,"%f",phead->gedcVersion); 
	strcat(data,str);
	strcat(data,"\n encoding: ");
	CharSet some;
	some=phead->encoding;

	switch(some){
		case ANSEL: strcpy(str,"ANSEL\n");break;
		case UTF8: strcpy(str,"UTF8\n");break;
		case UNICODE: strcpy(str,"UNICODE\n");break;
		case ASCII: strcpy(str,"ASCII\n");break;
		default: strcpy(str,"nuknow\n");
	}
	strcat(data,str);
	
	Submitter* sub;
	sub=phead->submitter;
	
	olddata=printSubmitte(sub);
	if(olddata!=NULL)
	{
		
		strcat(data,olddata);
		free(olddata);

	}
	
	char* someth;
	List alist;
	alist=phead->otherFields;
	someth=toString(alist);

	if(someth!=NULL)
	{
		strcat(data,someth);
		free(someth);

	}
	int x=0;
	char* back;
	x=strlen(data);
	back=malloc(x+200);
	strcpy(back,data);
	return back;
}
char * printSubmitte(Submitter* sub)
{
	char data[5000];
	
	strcpy(data,"Submitter:  \n   type:");
	strcat(data,sub->submitterName);
	
	strcat(data,"\naddress:  ");
	strcat(data,sub->address);

	
	char* some;
	List alist;
	alist=sub->otherFields;
	
	some=toString(alist);
	strcat(data,"\n");
	if(some!=NULL)
	{
		strcat(data,some);
		free(some);
	}
	
	int x=0;
	x=strlen(data);
	char * back;
	back=malloc(x+100);
	strcpy(back,data);
	
	return back;
}







////////////////////////////////////////////////////
char* printError(GEDCOMerror err)
{
	ErrorCode err2;
	err2=err.type;
	char * back;
	back=malloc(100);
	int inle=0;
	inle=err.line;
	char str[50];
	sprintf(str,"%d",inle); 

	switch(err2){
		case OK: strcpy(back,"OK");break;
		case INV_FILE: strcpy(back,"invalid file,happen in line ");break;
		case INV_GEDCOM: strcpy(back,"invalid GEDCOM,happen in line ");break;
		case INV_HEADER: strcpy(back,"invalid header,happen in line ");break;
		case INV_RECORD: strcpy(back,"multiple RECORD,happen in line ");break;
		case OTHER_ERROR: strcpy(back,"other invalid things,happen in line ");break;
		default: back="NULL";
	}
	if(err2!=0)
	{

		strcat(back,str);
	}
	return back;
}

Individual* findPerson(const GEDCOMobject* familyRecord, bool (*compare)(const void* first, const void* second), const void* person)
{
	if(familyRecord==NULL||person==NULL)
	{
		return NULL;
	}
	Individual* fpeople;
	Individual* speople;
	fpeople=(Individual*)person;
	List peoplelist;
	peoplelist=familyRecord->individuals;
	Node* head;
	head=peoplelist.head;
	while(head!=NULL)
	{
		speople=head->data;
		if(compare(speople,fpeople))
		{
			return speople;
		}
		head=head->next;
	}

	return NULL;
}
int compareIndividuals(const void* first,const void* second)
{
	if(first==NULL||second==NULL)
	{
		return 1;
	}
	Individual* fpeople;
	Individual* speople;
	fpeople=(Individual*)first;
	speople=(Individual*)second;
	char* fdata;
	char* sdata;
	fdata=getfullname(fpeople);
	sdata=getfullname(speople);
	if(fdata==NULL||sdata==NULL)
	{
		return 1;
	}
	if(strcmp(fdata,sdata)==0)
	{
		free(fdata);
		free(sdata);
		return 0;
	}
	free(fdata);
	free(sdata);
	return 1;
}
/*
List getDescendants(const GEDCOMobject* familyRecord, const Individual* person)
{

	Individual* fpeople;
	Individual* speople;
	Individual* schild;
	List peoplelist;
	printf("11111111111111111111111111111112222222222222222222222233333333333\n");
	if(familyRecord==NULL||person==NULL||person!=NULL)
	{
		peoplelist=initializeList(&printIndividual,&deleteIndividual,&nthings);;
		return peoplelist;
		
	}
	fpeople=(Individual*)person;
	peoplelist=familyRecord->individuals;
	Node* head;
	head=peoplelist.head;
	List child;
	List child2=initializeList(&printIndividual,&deleteIndividual,&nthings);;
	List fam;
	Family * famil;
	Node* head2;
	Node* head3;
	while(head!=NULL)
	{
		speople=head->data;
		if(compareIndividuals(speople,fpeople)==0)
		{
			fam=speople->families;
			head2=fam.head;
			while(head2!=NULL)
			{
				famil=head2->data;
				child=famil->children;
				head3=child.head;
				while(head3!=NULL)
				{
					schild=head3->data;
					insertBack(&child2,schild);


					head3=head3->next;
				}


				head2=head2->next;
			}
			
			
			return child2;




		}
		head=head->next;
	}
	return child2;
	

}
*/
void deleteEvent(void* toBeDeleted)
{
	if(toBeDeleted==NULL)
	{
		return;
	}
	Event* de;
	de=(Event*)toBeDeleted;
	char* deli;
	deli=de->date;
	if(deli!=NULL)
	{
		free(deli);
	}	
	deli=de->place;
	if(deli!=NULL)
	{
		free(deli);
	}	
	List list;
	list=de->otherFields;
	clearList(&list);
	free(de);
	return;
}
void deleteIndividual(void* toBeDeleted)
{
	if(toBeDeleted==NULL)
	{
		return;
	}
	Individual* de;
	de=(Individual*)toBeDeleted;
	char* deli;
	deli=de->givenName;
	if(deli!=NULL)
	{
		free(deli);
	}	
	deli=de->surname;
	if(deli!=NULL)
	{
		free(deli);
	}	
	List list;
	list=de->events;
	clearList(&list);
	list=de->otherFields;
	clearList(&list);
	free(de);
	return;
}
void deleteFamily(void* toBeDeleted)
{
	if(toBeDeleted==NULL)
	{
		return;
	}
	Family* de;
	de=(Family*)toBeDeleted;
	List list;
	list=de->events;
	clearList(&list);
	list=de->otherFields;
	clearList(&list);
	free(de);
	return;
}
void deleteField(void* toBeDeleted)
{
	if(toBeDeleted==NULL)
	{
		return;
	}
	Field* de;
	de=(Field*)toBeDeleted;
	char* deli;
	deli=de->tag;
	if(deli!=NULL)
	{
		free(deli);
	}	
	deli=de->value;
	if(deli!=NULL)
	{
		free(deli);
	}	
	free(de);
	return;
}
void deleteGEDCOM(GEDCOMobject* obj)
{
	if(obj==NULL)
	{
		return;
	}
	if(obj->header!=NULL)
	{
		Header* heard;
		heard=obj->header;
		clearList(&heard->otherFields);
		free(heard);
	}
	if(obj->submitter!=NULL)
	{
		Submitter* sub;
		sub=obj->submitter;
		clearList(&sub->otherFields);
		free(sub);
	}
	clearList(&obj->individuals);
	clearList(&obj->families);
	free(obj);
	return;
}
List onegetDescendants2(const GEDCOMobject* familyRecord, const Individual* person);
List onegetDescendants(const GEDCOMobject* familyRecord, const Individual* person);
void addoneintwo(List *one,List * two);
bool  compareIndividuals2(const void* first,const void* second)
{
	if(first==NULL||second==NULL)
	{
		return false;
	}
	Individual* fpeople;
	Individual* speople;
	fpeople=(Individual*)first;
	speople=(Individual*)second;
	char* fdata;
	char* sdata;
	fdata=getfullname(fpeople);
	sdata=getfullname(speople);
	if(fdata==NULL||sdata==NULL)
	{
		return false;
	}
	if(strcmp(fdata,sdata)==0)
	{
		free(fdata);
		free(sdata);
		return true;
	}
	free(fdata);
	free(sdata);
	return false;
}
List getDescendants(const GEDCOMobject* familyRecord, const Individual* person)
{
	List child;
	
	child=onegetDescendants2(familyRecord,person);
	if(familyRecord==NULL||person==NULL)
	{
		
		return child;
	}
	Node * f;
	Individual* onechild;
	f=child.head; 
	List other;
	Node * s;
	while(f!=NULL)
	{
		if(f->data!=NULL)
		{
			onechild=f->data;
			other=onegetDescendants2(familyRecord, onechild);/////////////////dont need full name
			s=other.head;
			if(s!=NULL&&s->data!=NULL)
			{
				
				addoneintwo(&other,&child);
			}
		}

		///freelist
		
		f=f->next;
	}
	return child;
	
}

List onegetDescendants(const GEDCOMobject* familyRecord, const Individual* person)
{
	Individual* findp;
	List child;
	child=initializeList(&printField,&deleteField,&nthings);
	if(familyRecord==NULL||person==NULL)
	{
		return child;
	}
	

	findp=findPerson(familyRecord, &compareIndividuals2,person);
	if(findp==NULL)
	{
		return child;
	}

	List fams;
	List chi;
	fams=familyRecord->families;

	Node * f;
	f=fams.head;
	Family * tagfam;
	while(f!=NULL)
	{
		tagfam=f->data;
		if(tagfam->wife==findp||tagfam->husband==findp)
		{
			chi=tagfam->children;
			addoneintwo(&chi,&child);
		}
		f=f->next;
	}

	return child;
}
List onegetDescendants2(const GEDCOMobject* familyRecord, const Individual* person)
{
	
	List child;
	child=initializeList(&printField,&deleteField,&nthings);
	if(familyRecord==NULL||person==NULL)
	{
		return child;
	}

	List fams;
	List chi;
	fams=familyRecord->families;

	Node * f;
	f=fams.head;
	Family * tagfam;
	while(f!=NULL)
	{
		tagfam=f->data;
		if(tagfam->wife==person||tagfam->husband==person)
		{
			chi=tagfam->children;
			addoneintwo(&chi,&child);
		}
		f=f->next;
	}

	return child;
}
/*
List onegetDescendants3(const GEDCOMobject* familyRecord, const Individual* person)
{
	
	
	List child;
	child=initializeList(&printField,&deleteField,&nthings);
	if(familyRecord==NULL||person==NULL)
	{
		return child;
	}

	List fams;
	List chi;
	fams=familyRecord->families;

	Node * f;
	f=fams.head;
	Family * tagfam;
	while(f!=NULL)
	{
		tagfam=f->data;
		if(tagfam->wife==person||tagfam->husband==person)
		{
			chi=tagfam->children;
			addoneintwo(&chi,&child);
		}
		f=f->next;
	}

	return child;
}
*/
void addoneintwo(List *one,List * two)
{

	if(one==NULL||two==NULL)
	{
		return;
	}
	if(one->head==NULL)
	{
		return;
	}
	Node *f;

	f=one->head;
	Individual* person;
	while(f!=NULL)
	{
		person=f->data;
		if(person!=NULL)
		{
			insertBack(two,person);
		}

		f=f->next;
	}



	return;
}


GEDCOMerror writeheader(Header * head,FILE * fp);

GEDCOMerror writeEvent(List * events,FILE * fp);
GEDCOMerror writeoneEvent(Event * event,FILE * fp);

GEDCOMerror writeField(List * field,FILE * fp);
GEDCOMerror writeoneField(Field * afield,FILE * fp);

GEDCOMerror writeSubmitter(Submitter * asub,FILE * fp);

GEDCOMerror writeIndividual(List * people,FILE * fp,List * fam);
GEDCOMerror writeoneperson(Individual * person,FILE * fp,List * famList);

GEDCOMerror writeFamily(List * fam,FILE * fp,List * people);
GEDCOMerror writeoneFamily(Family *family,FILE * fp,List * people);

GEDCOMerror writeGEDCOM(char* fileName, const GEDCOMobject* obj)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(fileName==NULL||obj==NULL)
	{
		errreturn.type=6;
		errreturn.line=0;
		return errreturn;
	}
	FILE * fp;
	if((fp=fopen(fileName,"w+"))==NULL)
	{
		errreturn.type=6;
		errreturn.line=0;
		return errreturn;
	}
	Header * oneheader;

	oneheader=obj->header;
	List people;
	List fam;
	people=obj->individuals;
	fam=obj->families;
	Submitter * asub;
	asub=obj->submitter;


	errreturn=writeheader(oneheader,fp);
	if(errreturn.type!=0) return errreturn;

	errreturn=writeIndividual(&people,fp,&fam);
	if(errreturn.type!=0) return errreturn;

	errreturn=writeFamily(&fam,fp,&people);
	if(errreturn.type!=0) return errreturn;

	errreturn=writeSubmitter(asub,fp);
	if(errreturn.type!=0) return errreturn;

	char st[40000];

	strcpy(st,"0 TRLR\n");
	fputs(st,fp);

	fclose(fp);


	return errreturn;
}


GEDCOMerror writeSubmitter(Submitter * asub,FILE * fp)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(asub==NULL)
	{
		errreturn.type=6;
		errreturn.line=0;
		return errreturn;
	}
	char st[40000];

	strcpy(st,"0 @U1@ SUBM\n");
	fputs(st,fp);

	strcpy(st,"1 NAME ");
	strcat(st,asub->submitterName);
	strcat(st,"\n");
	fputs(st,fp);

	if(strlen(asub->address)>2)
	{
		strcpy(st,"1 ADDR ");
		strcat(st,asub->address);
		strcat(st,"\n");
		fputs(st,fp);
	}




	return errreturn;
}



GEDCOMerror writeEvent(List * events,FILE * fp)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(events==NULL)
	{
		errreturn.type=0;
		errreturn.line=0;
		return errreturn;
	}
	Node * f;
	Event * event;
	f=events->head;
	while(f!=NULL)
	{
		event=f->data;
		if(event!=NULL)
		{
 			errreturn=writeoneEvent(event,fp);
		}
		f=f->next;
	}


	return errreturn;
}
GEDCOMerror writeoneEvent(Event * event,FILE * fp)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(event==NULL)
	{
		errreturn.type=0;
		errreturn.line=0;
		return errreturn;
	}
	char st[40000];

	strcpy(st,"1 ");
	strcat(st,event->type);
	strcat(st,"\n");
	fputs(st,fp);

	if(event->date!=NULL)
	{
		strcpy(st,"2 DATE ");
		strcat(st,event->date);
		strcat(st,"\n");
		fputs(st,fp);
	}

	if(event->place!=NULL)
	{
		strcpy(st,"2 PLAC ");
		strcat(st,event->place);
		strcat(st,"\n");
		fputs(st,fp);
	}

	List field;
	field=event->otherFields;

	errreturn=writeField(&field,fp);

	return errreturn;
}
GEDCOMerror writeField(List * field,FILE * fp)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(field==NULL)
	{
		return errreturn;
	}
	Node * f;
	f=field->head;
	Field * afield;
	while(f!=NULL)
	{
		afield=f->data;
		if(afield!=NULL)
		{
			errreturn=writeoneField(afield,fp);
		}

		f=f->next;
	}


	return errreturn;
}

GEDCOMerror writeoneField(Field * afield,FILE * fp)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(afield==NULL)
	{
		errreturn.type=0;
		errreturn.line=0;
		return errreturn;
	}
	char st[40000];
	if(strcmp(afield->tag,"GIVN")==0||strcmp(afield->tag,"SURN")==0)
	{
		strcpy(st,"2 ");
		strcat(st,afield->tag);
		if(afield->value!=NULL)
		{
			strcat(st," ");
			strcat(st,afield->value);
		}
		strcat(st,"\n");
		fputs(st,fp);

	}
	else if(afield->tag!=NULL)
	{
		strcpy(st,"1 ");
		strcat(st,afield->tag);
		if(afield->value!=NULL)
		{
			strcat(st," ");
			strcat(st,afield->value);
		}
		strcat(st,"\n");
		fputs(st,fp);
	}
	return errreturn;
}


GEDCOMerror writeFamily(List * fam,FILE * fp,List * people)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(fam==NULL)
	{
		errreturn.type=0;
		errreturn.line=0;
		return errreturn;
	}
	char st[40000];
	char st2[30];
	int r=0;
	Node * f;
	Family *family;

	f=fam->head;
//printf("nu11111111111111kk\n");
	while(f!=NULL)
	{
		//printf("nu111111111121111kk\n");
		r=r+1;
		family=f->data;
		if(family!=NULL)
		{
			//printf("nu111111111333333311kk\n");
			strcpy(st,"0 @F");
			sprintf(st2,"%d",r);
			strcat(st,st2);
			strcat(st,"@ FAM");
			strcat(st,"\n");
			fputs(st,fp);
			errreturn=writeoneFamily(family,fp,people);
		}

		f=f->next;
	}

	return errreturn;
}
GEDCOMerror writeoneFamily(Family *family,FILE * fp,List * people)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(family==NULL)
	{
		errreturn.type=0;
		errreturn.line=0;
		return errreturn;
	}
//printf("nu11111111122333333311kk\n");
	char st[40000];
	char st2[30];

	Node * f;
	Node * s;
	int r=0;

	if(family->husband!=NULL)
	{
		//printf("nu111111333111333333311kk\n");
		s=people->head;
		r=0;
		while(s!=NULL)
		{	r=r+1;
			if(s->data==family->husband)
			{
				strcpy(st,"1 HUSB @I");

				sprintf(st2,"%d",r);
				strcat(st,st2);
				strcat(st,"@");
				strcat(st,"\n");
				fputs(st,fp);
			}

			s=s->next;
		}
	}

	if(family->wife!=NULL)
	{
		//printf("nu1111155551333333311kk\n");
		s=people->head;
		r=0;
		while(s!=NULL)
		{	r=r+1;
			if(s->data==family->wife)
			{
				strcpy(st,"1 WIFE @I");

				sprintf(st2,"%d",r);
				strcat(st,st2);
				strcat(st,"@");
				strcat(st,"\n");
				fputs(st,fp);
			}

			s=s->next;
		}
	}


	List peo;
	peo=family->children;
	f=peo.head;
	while(f!=NULL)
	{
		//printf("nu11111199991333333311kk\n");
		r=0;
		s=people->head;
		while(s!=NULL)
		{
			r=r+1;
			if(f->data==s->data)
			{
				strcpy(st,"1 CHIL @I");
				sprintf(st2,"%d",r);
				strcat(st,st2);
				strcat(st,"@");
				strcat(st,"\n");
				fputs(st,fp);
			}

			s=s->next;
		}



		f=f->next;
	}

	//event
	List events;
	events=family->events;
	errreturn=writeEvent(&events,fp);
	///otherFields
	List field;
	field=family->otherFields;

	errreturn=writeField(&field,fp);


	return errreturn;
}



GEDCOMerror writeIndividual(List * people,FILE * fp,List * fam)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(people==NULL)
	{
		errreturn.type=0;
		errreturn.line=0;
		return errreturn;
	}
	char st[40000];
	char st2[30];
	int r=0;
	Node * f;
	Individual * person;

	f=people->head;

	while(f!=NULL)
	{
		
		r=r+1;
		person=f->data;
		if(person!=NULL)
		{
			
			strcpy(st,"0 @I");
			sprintf(st2,"%d",r);
			strcat(st,st2);
			strcat(st,"@ INDI");
			strcat(st,"\n");
			fputs(st,fp);
			errreturn=writeoneperson(person,fp,fam);
		}

		f=f->next;
	}

	return errreturn;
}

GEDCOMerror writeoneperson(Individual * person,FILE * fp,List * famList)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(person==NULL)
	{
		errreturn.type=0;
		errreturn.line=0;
		return errreturn;
	}

	char st[40000];
	char st2[30];
	strcpy(st,"1 NAME ");
	if(person->givenName!=NULL) 
	{
		strcat(st,person->givenName);
		strcat(st," ");
	}
	if(person->surname!=NULL)
	{	
		strcat(st,"/"); 
		strcat(st,person->surname);
		strcat(st,"/");
	}
	strcat(st,"\n");
	fputs(st,fp);


	List fam;
	fam=person->families;
	Node * f;
	Node * s;
	f=fam.head;
	int r=0;
	while(f!=NULL)
	{
		r=0;
		s=famList->head;
		while(s!=NULL)
		{
			r=r+1;
			if(f->data==s->data)
			{
				strcpy(st,"1 FAMS @F");
				sprintf(st2,"%d",r);
				strcat(st,st2);
				strcat(st,"@");
				strcat(st,"\n");
				fputs(st,fp);
			}

			s=s->next;
		}



		f=f->next;
	}


	//event
	///otherFields
	List events;
	events=person->events;
	errreturn=writeEvent(&events,fp);
	///otherFields
	List field;
	field=person->otherFields;

	errreturn=writeField(&field,fp);


	return errreturn;

}
GEDCOMerror writeheader(Header * head,FILE * fp)
{
	GEDCOMerror errreturn;
	errreturn.type=0;
	errreturn.line=0;
	if(head==NULL)
	{
		errreturn.type=6;
		errreturn.line=0;
		return errreturn;
	}

	char st[40000];
	char st2[30];
	CharSet one;
	one=head->encoding;

	strcpy(st,"0 HEAD");
	strcat(st,"\n");
	fputs(st,fp);

	strcpy(st,"1 SOUR ");
	strcat(st,head->source);
	strcat(st,"\n");
	fputs(st,fp);

	strcpy(st,"1 GEDC\n");
	fputs(st,fp);

	strcpy(st,"2 VERS ");
	sprintf(st2,"%f",head->gedcVersion);
	strcat(st,st2);
	strcat(st,"\n");
	fputs(st,fp);

	strcpy(st,"1 CHAR ");
	switch(one){
		case ANSEL: strcat(st,"ANSEL\n");break;
		case UTF8: strcat(st,"UTF-8\n");break;
		case UNICODE: strcat(st,"UNICODE\n");break;
		case ASCII: strcat(st,"ASCII\n");break;
		default: errreturn.type=6;return errreturn;
	}
	fputs(st,fp);

	if(head->submitter!=NULL)
	{
		strcpy(st,"1 SUBM @U1@\n");
		fputs(st,fp);
	}


///otherFields
	List field;
	field=head->otherFields;

	errreturn=writeField(&field,fp);

	return errreturn;
}



List getDescendantListN(const GEDCOMobject* familyRecord, const Individual* person, unsigned int maxGen)
{
	List a;
	a=initializeList(&printField,&deleteField,&nthings);
	List back;
	
	back=initializeList(&printGeneration,&deleteGeneration,&compareGenerations);
		
	int num;
	num=maxGen;
	
	
	if(familyRecord==NULL||person==NULL||num<0)
	{
			return back;
	}
	
	List try;
	try=familyRecord->families;
	if(getLength(try)==0)
	{
		return back;
	}
	try=familyRecord->individuals;
	if(getLength(try)==0)
	{
		return back;
	}

	printf("0001\n");
	List * oneg;
	
	
	
	
	a=onegetDescendants2(familyRecord,person);
	
	
	if(getLength(a)!=0)
	{
		printf("0001.1\n");
		oneg=malloc(sizeof(List));
		*oneg=a;
		insertBack(&back,(void*)oneg);
	}
	if(num==1)
	{
		return back;
	}
	int x=1;
	
	
	Node * f;
	Individual* onechild;
	f=back.head; 

	
	List* other;
	
	Node * s;
	
	List one;
	List two;
	
	while(x!=num&&f!=NULL)
	{
		
		other=f->data;
		s=other->head;
		
		two=initializeList(&printIndividual,&deleteIndividual,&nthings);
		
		while(s!=NULL)
		{
			if(s->data!=NULL)
			{
				
				onechild=s->data;
				
				one=onegetDescendants2(familyRecord, onechild);
				
				if(getLength(one)!=0)
				{
					
					addoneintwo(&one,&two);
				}
				
			}
			s=s->next;
		}
		
		
		if(getLength(two)!=0)
		{
			oneg=malloc(sizeof(List));
			*oneg=two;
			insertBack(&back,(void*)oneg);
		}
		
		f=f->next;
		x=x+1;
	}
	
	
	
	/*
	while(f!=NULL)
	{
		if(f->data!=NULL)
		{
			onechild=f->data;
			other=onegetDescendants2(familyRecord, onechild);/////////////////dont need full name
			s=other.head;
			if(s!=NULL&&s->data!=NULL)
			{
				
				addoneintwo(&other,&child);
			}
		}

		///freelist
		
		f=f->next;
	}
	*/
	return back;

}
List getAncestorListN(const GEDCOMobject* familyRecord, const Individual* person, int maxGen)
{
	List a;
	a=initializeList(&printField,&deleteField,&nthings);
	return a;
}
char* indToJSON(const Individual* ind)
{
	char* back;
	back=malloc(3000);
	if(ind==NULL)
	{
		strcpy(back,"");
		return back;
	}
	strcpy(back,"{\"givenName\":\"");
	if(ind->givenName!=NULL)
	{
		strcat(back,ind->givenName);
	}
	strcat(back,"\",\"surname\":\"");
	if(ind->surname!=NULL)
	{
		strcat(back,ind->surname);
	}
	strcat(back,"\"}");
	return back;
}
ErrorCode validateGEDCOM(const GEDCOMobject* obj)
{
	ErrorCode back=0;
	if(obj==NULL)
	{
		back=2;
		return back;
	}
	
	Header* head;
	head=obj->header;
	if(head==NULL)
	{
		back=2;
		return back;
	}
	Submitter* sub;
	Submitter* sub2;
	sub=obj->submitter;
	sub2=head->submitter;
	if(sub!=sub2||sub==NULL||sub2==NULL)
	{
		if(sub2==NULL)
		{
			back=3;
		}
		else
		{
			back=2;
		}	
		
		return back;
	}
	int x;
	
	x=strlen(sub->submitterName);
	if(x<1)
	{
		back=4;
		return back;
	}
	//x=strlen(sub2->submitterName);
	//if(x<1)
	//{
	//	back=3;
//		return back;
	//}
	
	float fol;
	
	fol=head->gedcVersion;
	if(fol<1)
	{
		back=3;
		return back;
	}
	char coure[250];
	strcpy(coure,head->source);
	
	x=strlen(coure);
	if(x<2)
	{
		back=3;
		return back;
	}
	
	
	
	CharSet one;
	one=head->encoding;
	switch(one){
		case ANSEL: back=0;break;
		case UTF8: back=0;break;
		case UNICODE: back=0;break;
		case ASCII: back=0;break;
		default: back=3; break;
	}
	


	return back;
}
Individual* JSONtoInd(const char* str)
{
	if(str==NULL)
	{
		return NULL;
	}
	int x;
	x=strlen(str);
	if(x<3)
	{
		return NULL;
	}
	if(str[0]!='{'||str[x-1]!='}')
	{
		return NULL;
	}
	//puts(str);
	char* sname=NULL;
	char* gname=NULL;
	char data[3000];
	strcpy(data,str);
	char * first;
	
	

	first=strtok(data,":");
	first=strtok(NULL,"\"");
	if(first!=NULL)
	{
		if(strcmp(first,",")!=0)
		{
			gname=malloc(90);
			//puts(first);
			strcpy(gname,first);
		}
	}
	first=strtok(NULL,":");
	first=strtok(NULL,"\"");
	if(first!=NULL)
	{
		if(strcmp(first,"}")!=0)
		{
			sname=malloc(90);
			//puts(first);
			
			strcpy(sname,first);
		}
	}
	Individual* back;
	back=malloc(sizeof(Individual));
	back->givenName=gname;
	back->surname=sname;
	return back;
}
GEDCOMobject* JSONtoGEDCOM(const char* str)
{
	if(str==NULL)
	{
		return NULL;
	}
	int x;
	x=strlen(str);
	if(x<3)
	{
		return NULL;
	}
	if(str[0]!='{'||str[x-1]!='}')
	{
		return NULL;
	}
	
	char data[3000];
	strcpy(data,str);
	char * first;
	
	
	GEDCOMobject* back;
	back= malloc(sizeof(GEDCOMobject));
	
	Header* newhead;
	newhead = malloc(sizeof(Header));
	
	float f;
	first=strtok(data,":");
	first=strtok(NULL,"\"");
	if(first!=NULL)
	{
		strcpy(newhead->source,first);
	}
	first=strtok(NULL,":");
	first=strtok(NULL,"\"");
	if(first!=NULL)
	{
		sscanf(first, "%f", &f);
		newhead->gedcVersion=f;
	}
	
	CharSet cs;
	
	first=strtok(NULL,":");
	first=strtok(NULL,"\"");
	if(first!=NULL)
	{

			if(strcmp(first,"ANSEL")==0)
			{
				cs=ANSEL;
			}
			else if(strcmp(first,"UTF-8")==0)
			{
				cs=UTF8;
			}
			else if(strcmp(first,"UNICODE")==0)
			{
				cs=UNICODE;
			}
			else if(strcmp(first,"ASCII")==0)
			{
				cs=ASCII;
			}
		
	}
	
	newhead->encoding=cs;
	
	Submitter* sub;
	sub = malloc(sizeof(Header));
	
	first=strtok(NULL,":");
	first=strtok(NULL,"\"");
	if(first!=NULL&&strcmp(first,",")!=0)
	{
		strcpy(sub->submitterName,first);
		
	}
	
	first=strtok(NULL,":");
	first=strtok(NULL,"\"");
	if(first!=NULL&&strcmp(first,"}")!=0)
	{
		strcpy(sub->address,first);
	}
	
	newhead->submitter=sub;
	back->header=newhead;
	back->submitter=sub;
	
	return back;
}
void addIndividual(GEDCOMobject* obj, const Individual* toBeAdded)
{
	if(obj== NULL||toBeAdded==NULL)
	{
		return;
	}
	insertBack(&(obj->individuals),(void*)toBeAdded);
	return;
}
char* iListToJSON(List iList)
{
	char * back;
	back=malloc(6000);
	strcpy(back,"[");

	char * person;
	Individual* per;
	Node * f;
	f=iList.head;

	while(f!=NULL)
	{
		per=f->data;
		if(per!=NULL)
		{
			person=indToJSON(per);
			if(person!=NULL)
			{
				strcat(back,person);
				if(f->next!=NULL)
				{
					strcat(back,",");
				}
				free(person);
			}
		}
		f=f->next;
	}
	strcat(back,"]");
	return back;
}
char* gListToJSON(List gList)
{
	char* back;
	back=malloc(6000);
	if(getLength(gList)==0)
	{
		strcpy(back,"[]");
		return back;
	}
	
	
	strcpy(back,"[");

	char * person;
	List* per;
	Node * f;
	f=gList.head;

	while(f!=NULL)
	{
		per=f->data;
		if(per!=NULL)
		{
			person=iListToJSON(*per);
			if(person!=NULL)
			{
				strcat(back,person);
				if(f->next!=NULL)
				{
					strcat(back,",");
				}
				free(person);
			}
		}
		f=f->next;
	}
	strcat(back,"]");
	
	return back;
}
int compareGenerations(const void* first,const void* second)
{
	return 0;
}
int compareEvents(const void* first,const void* second)
{
	return 0;
}
int compareFamilies(const void* first,const void* second)
{
	return 0;
}
int compareFields(const void* first,const void* second)
{
	return 0;
}
void deleteGeneration(void* toBeDeleted)
{
	return;
}
char* printGeneration(void* toBePrinted)
{
	return NULL;
}
char * tryf()
{
	char * m;
	m=malloc(40);
	strcpy(m,"aaaaalex");
	return m;
}

char* indToJSON2(const Individual* ind)
{
	char* back;
	back=malloc(3000);
	if(ind==NULL)
	{
		strcpy(back,"");
		return back;
	}
	strcpy(back,"|");
	if(ind->givenName!=NULL)
	{
		strcat(back,ind->givenName);
	}
	else
	{
		strcat(back,"---");
	}
	strcat(back,"|");
	if(ind->surname!=NULL)
	{
		strcat(back,ind->surname);
	}
	else
	{
		strcat(back,"---");
	}
	strcat(back,"|");
	
	int a;
	List fan;
	fan=ind->families;
	a=getLength(fan);
	
	
	//strcat(back,",\"famnumber\":\"");
	
	
	char str [30];
	sprintf(str,"%d",a);
	strcat(back,str);
	strcat(back,"|");
	
	//strcat(back,",\"sex\":\"");
	List other;
	other=ind->otherFields;
	char* check;
	Node * f;
	f=other.head;
	Field* some;
	int u=0;
	while(f!=NULL)
	{
		some=f->data;
		check=some->tag;
		if(strcmp(check,"SEX")==0)
		{
			strcat(back,some->value);
			u=1;
		}
		f=f->next;
	}
	if(u==0)
	{
		strcat(back,"---");
	}
	strcat(back,"|");
	
	return back;
}
char* iListToJSON2(List iList)
{
	char * back;
	back=malloc(6000);
	strcpy(back,"|people|");

	char * person;
	Individual* per;
	Node * f;
	f=iList.head;

	while(f!=NULL)
	{
		per=f->data;
		if(per!=NULL)
		{
			person=indToJSON2(per);
			if(person!=NULL)
			{
				strcat(back,person);
				if(f->next!=NULL)
				{
					strcat(back,"|other|");
				}
				free(person);
			}
		}
		f=f->next;
	}
	//strcat(back,"|end|");
	return back;
}








char * gedinaboutpeople(char * name)
{
	char * back;
	back=malloc(8000);
	char * somepeople;
	
	char* fname;
	fname=malloc(40);
	strcpy(fname,"uploads/");
	strcat(fname,name);
	
	GEDCOMobject * obj;
	GEDCOMerror errreturn;
	errreturn=createGEDCOM(fname,&obj);
	if(errreturn.type!=0)
	{
		strcpy(back,"null");
		return back;
	}
	List people;
	people=obj->individuals;
	somepeople=iListToJSON2(people);
	strcpy(back,somepeople);
	//strcat(back,"^p");
	return back;
}
char * gedinformation(char * name)
{
	char* fname;
	fname=malloc(40);
	strcpy(fname,"uploads/");
	strcat(fname,name);
	char * back;
	back=malloc(500);
		
	GEDCOMobject * obj;
	GEDCOMerror errreturn;
	errreturn=createGEDCOM(fname,&obj);
	if(errreturn.type!=0)
	{
		strcpy(back,"null");
		return back;
	}
	strcpy(back,"|");
	strcat(back,name);
	strcat(back,"|");
	Header * heade;
	heade=obj->header;
	
	strcat(back,heade->source);
	strcat(back,"|");
	char str[40];
	
	float vn;
	vn=heade->gedcVersion;
	sprintf(str,"%f",vn); 
	strcat(back,str);
	strcat(back,"|");
	
	CharSet cs;
	cs=heade->encoding;
	switch(cs){
		case ANSEL: strcpy(str,"ANSEL|");break;
		case UTF8: strcpy(str,"UTF8|");break;
		case UNICODE: strcpy(str,"UNICODE|");break;
		case ASCII: strcpy(str,"ASCII|");break;
		default: strcpy(str,"nuknow|");
	}
	strcat(back,str);
	
	Submitter * sub;
	sub=obj->submitter;
	if(strlen(sub->submitterName)>2)
	{
		strcat(back,sub->submitterName);
		strcat(back,"|");
	}
	else
	{
		strcat(back,"---|");
	}
	
	if(strlen(sub->address)>15)
	{
		strcat(back,sub->address);
		strcat(back,"|");
	}
	else
	{
		strcat(back,"---|");
	}
	int nu;
	List count;
	
	count=obj->individuals;
	nu=getLength(count);
	strcpy(str,"");
	sprintf(str,"%d",nu);
	strcat(back,str);
	strcat(back,"|");
	
	count=obj->families;
	nu=getLength(count);
	strcpy(str,"");
	sprintf(str,"%d",nu);
	strcat(back,str);
	strcat(back,"|");
	strcat(back,"^obj");

	
	return back;
}

char * makeadecom(char * str)
{
	char * back;
	back=malloc(30);
	if(str==NULL)
	{
		strcpy(back,"no do not pass");
		return back;
	}

	
	char data[3000];
	strcpy(data,str);
	char * first;
	char * name;
	name=malloc(40);
	
	
	
	

	first=strtok(data,"|");
	
	
	strcpy(name,"uploads/");
	strcat(name,first);
	
	
	first=strtok(NULL,"-");
	puts(first);
	GEDCOMobject * obj;
	obj=JSONtoGEDCOM(first);
	if(obj==NULL)
	{
			strcpy(back,first);
			return back;
	}
	GEDCOMerror errreturn;
	errreturn=writeGEDCOM(name,obj);
	if(errreturn.type!=0)
	{
			strcpy(back,"can not writein file\n");
			return back;
	}
	
	return back;
}

char * gedputdata(char * name)
{
	char* fname;
	fname=malloc(40);
	strcpy(fname,"uploads/");
	strcat(fname,name);
	char * back;
	back=malloc(500);
		
	GEDCOMobject * obj;
	GEDCOMerror errreturn;
	errreturn=createGEDCOM(fname,&obj);
	if(errreturn.type!=0)
	{
		strcpy(back,"null");
		return back;
	}
	strcpy(back,"INSERT INTO FILE (file_Name, source, version, encoding, sub_name, sub_addr, num_individuals, num_families) VALUES ('");
	strcat(back,name);
	strcat(back,"','");
	Header * heade;
	heade=obj->header;
	
	strcat(back,heade->source);
	strcat(back,"','");
	char str[40];
	
	float vn;
	vn=heade->gedcVersion;
	sprintf(str,"%f",vn); 
	strcat(back,str);
	strcat(back,"','");
	
	CharSet cs;
	cs=heade->encoding;
	switch(cs){
		case ANSEL: strcpy(str,"ANSEL','");break;
		case UTF8: strcpy(str,"UTF8','");break;
		case UNICODE: strcpy(str,"UNICODE','");break;
		case ASCII: strcpy(str,"ASCII','");break;
		default: strcpy(str,"nuknow','");
	}
	strcat(back,str);
	
	Submitter * sub;
	sub=obj->submitter;
	if(strlen(sub->submitterName)>2)
	{
		strcat(back,sub->submitterName);
		strcat(back,"'");
	}
	else
	{
		strcat(back,"---'");
	}
	
	if(strlen(sub->address)>15)
	{
		strcat(back,sub->address);
		strcat(back,",'");
	}
	else
	{
		strcat(back,",'---','");
	}
	int nu;
	List count;
	
	count=obj->individuals;
	nu=getLength(count);
	strcpy(str,"");
	sprintf(str,"%d",nu);
	strcat(back,str);
	strcat(back,"','");
	
	count=obj->families;
	nu=getLength(count);
	strcpy(str,"");
	sprintf(str,"%d",nu);
	strcat(back,str);
	strcat(back,"')");
	

	
	return back;
}
//UP DATA DBPEOPLE


char* indToJSON2DB(const Individual* ind, int f1)
{
	char* back;
	back=malloc(3000);
	if(ind==NULL)
	{
		strcpy(back,"");
		return back;
	}
	strcpy(back,"|INSERT INTO INDIVIDUAL (surname, given_name, sex, fam_size, source_file) VALUES ('");
	if(ind->surname!=NULL)
	{
		strcat(back,ind->surname);
	}
	else
	{
		strcat(back,"---");
	}
	strcat(back,"','");
	
	
	if(ind->givenName!=NULL)
	{
		strcat(back,ind->givenName);
	}
	else
	{
		strcat(back,"---");
	}
	strcat(back,"','");

	
	int a;
	List fan;
	fan=ind->families;
	a=getLength(fan);
	
	
	//strcat(back,",\"famnumber\":\"");
	
	

	
	//strcat(back,",\"sex\":\"");
	List other;
	other=ind->otherFields;
	char* check;
	Node * f;
	f=other.head;
	Field* some;
	int u=0;
	while(f!=NULL)
	{
		some=f->data;
		check=some->tag;
		if(strcmp(check,"SEX")==0)
		{
			strcat(back,some->value);
			u=1;
		}
		f=f->next;
	}
	if(u==0)
	{
		strcat(back,"---");
	}
	strcat(back,"','");
	
	
	
		char str [30];
	sprintf(str,"%d",a);
	strcat(back,str);
	strcat(back,"','");
	
	sprintf(str,"%d",f1);
	strcat(back,str);
	strcat(back,"')");
	
	return back;
}
char* iListToJSON2DB(List iList, int f1)
{
	char * back;
	back=malloc(6000);
	strcpy(back,"null");

	char * person;
	Individual* per;
	Node * f;
	f=iList.head;

	while(f!=NULL)
	{
		per=f->data;
		if(per!=NULL)
		{
			person=indToJSON2DB(per,f1);
			if(person!=NULL)
			{
				strcat(back,person);
				if(f->next!=NULL)
				{
					strcat(back,"");
				}
				free(person);
			}
		}
		f=f->next;
	}
	//strcat(back,"|end|");
	return back;
}








char * gedinaboutpeopleDB(char * name, int f1)
{
	char * back;
	back=malloc(8000);
	char * somepeople;
	
	char* fname;
	fname=malloc(40);
	strcpy(fname,"uploads/");
	strcat(fname,name);
	
	GEDCOMobject * obj;
	GEDCOMerror errreturn;
	errreturn=createGEDCOM(fname,&obj);
	if(errreturn.type!=0)
	{
		strcpy(back,"null");
		return back;
	}
	List people;
	people=obj->individuals;
	somepeople=iListToJSON2DB(people,f1);
	strcpy(back,somepeople);
	//strcat(back,"^p");
	return back;
}
