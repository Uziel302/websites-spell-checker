#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BEFORE 150
#define AFTER 200
int main()
{
int milon_count=0;
int i=0,j=0,k=0,lll=0,existing=0,textflag=0,namecount=0,templateflag=1,linkflag=1,
nameflag=0,spaceflag=1,namespaceflag=0,galleryflag=1,fileflag=1,fileflag2=1,imageflag=1;
int aftercount=0,contextJump=0,endofcontext=BEFORE;
char typo[80];
char oldtypo[80];
char pagename[100];
char afterword=' ';
char *p;
char lastchar=0,lastchar2=0;
char (*milon)[80];
char context[BEFORE];
milon = malloc (14000000 * sizeof(char[80]));
int *exists;
exists = malloc (14000000 * sizeof(int));
//for(i=0;i<3000000;i++)exists[i]=0;
FILE *fp1 = fopen("hewiki-20200420-pages-meta-current.xml", "r");
FILE *fp2 = fopen("history.txt", "r");
FILE *fp3 = fopen("file3.txt", "w");

if (fp1 == NULL || fp2 == NULL || fp3 == NULL )
{
puts("Could not open files");
exit(0);
}

j=0;
k=0;
char c;
//load main milon
while ((c = fgetc(fp2)) != EOF)
{
milon[j][k]=c;
if(c==',')milon[j][k]=0;
if (c=='\n') {milon[j][k]=0;if(k>2)milon_count++;j++;k=0;}//end of word - move to next word
if (c!='\n')k++;
}
printf("WOW1");
//scanf("%d",&c);

j=0;
c=0;
while (c!=EOF){//word loop
    int found=0;
        k=0;
  //  for(i=0;i<20;i++)typo[i]=0;
//lll++;if(lll==30000)break;

while ((c = fgetc(fp1))!=EOF)//letter loop
{
//print after context
if(aftercount>0){
                    if(aftercount==AFTER&&strlen(typo)!=0)fprintf(fp3," </nowiki></br>@@@'''%s''' <nowiki>",typo);
                    if(aftercount==1&&(unsigned char)c==0xD7)aftercount=0;
                    if(aftercount>0&&c!='\n'){fprintf(fp3, "%c", c); aftercount--;}
                }
//save article name: if <title>
if(context[BEFORE-7]=='<'&&context[BEFORE-6]=='t'&&context[BEFORE-5]=='i'&&
   context[BEFORE-4]=='t'&&context[BEFORE-3]=='l'&&context[BEFORE-2]=='e'&&context[BEFORE-1]=='>')nameflag=1;

if(nameflag==1&&c!='<'){pagename[namecount]=c;namecount++;}
if(nameflag==1&&c=='<'){pagename[namecount]=0;namecount=0;nameflag=0;}

//close tags in new article
if(nameflag==1)
    {templateflag=1;galleryflag=1;spaceflag=1;linkflag=1;fileflag=1;fileflag2=1;imageflag=1;}

//only search within articles text
if(context[BEFORE-4]=='<'&&context[BEFORE-3]=='t'&&
   context[BEFORE-2]=='e'&&context[BEFORE-1]=='x'&&c=='t'){textflag=1;}

if(context[BEFORE-5]=='<'&&context[BEFORE-4]=='/'&&
   context[BEFORE-3]=='t'&&context[BEFORE-2]=='e'&&context[BEFORE-1]=='x'&&c=='t'){textflag=0;}

//only search namespace 0
if(context[BEFORE-4]=='<'&&context[BEFORE-3]=='n'&&
   context[BEFORE-2]=='s'&&context[BEFORE-1]=='>'&&c=='0'){namespaceflag=1;}

if(context[BEFORE-4]=='<'&&context[BEFORE-3]=='n'&&
   context[BEFORE-2]=='s'&&context[BEFORE-1]=='>'&&c!='0'){namespaceflag=0;}

   //skip files
if((context[BEFORE-4]=='F'||context[BEFORE-4]=='f')&&context[BEFORE-3]=='i'&&
   context[BEFORE-2]=='l'&&context[BEFORE-1]=='e'){typo[0]=0;fileflag=0;}
if(fileflag==0&&c=='\n'){fileflag=1;}
   //skip files in hebrew תמונה: קובץ:
if(((unsigned char)context[BEFORE-2]==0xA5||(unsigned char)context[BEFORE-2]==0x94)&&context[BEFORE-1]==':'){typo[0]=0;fileflag2=0;}
if(fileflag2==0&&c=='\n'){fileflag2=1;}
   //skip files
if((context[BEFORE-5]=='I'||context[BEFORE-5]=='i')&&context[BEFORE-4]=='m'&&
   context[BEFORE-3]=='a'&&context[BEFORE-2]=='g'&&context[BEFORE-1]=='e'){typo[0]=0;imageflag=0;}
if(imageflag==0&&c=='\n'){imageflag=1;}
 //skip <gallery>
if(context[BEFORE-4]==';'&&context[BEFORE-3]=='g'&&
   context[BEFORE-2]=='a'&&context[BEFORE-1]=='l'&&c=='l'){typo[0]=0;galleryflag=0;}

if(context[BEFORE-5]==';'&&context[BEFORE-4]=='/'&&
   context[BEFORE-3]=='g'&&context[BEFORE-2]=='a'&&context[BEFORE-1]=='l'&&c=='l'){galleryflag=1;}

  //skip templates
if(context[BEFORE-1]=='{'&&c=='{'){templateflag=0;}
if(context[BEFORE-1]=='\n'&&c=='='){templateflag=1;}

 //skip inner links
if(context[BEFORE-1]=='['&&c=='['){linkflag=0;}
if(context[BEFORE-1]==']'&&c!=']'){linkflag=1;}

//save context
for(i=0;i<BEFORE;i++){context[i]=context[i+1];}context[BEFORE-1]=c;
if(k==79){spaceflag=0;break;}

if(spaceflag==1&&namespaceflag==1&&galleryflag==1&&textflag==1&&templateflag==1&&linkflag==1&&fileflag==1&&fileflag2==1&&imageflag==1)
{ typo[k]=c;}

    //utf8 chars to separate words
if (((unsigned char)lastchar==0xD6&&(unsigned char)c==0xBE)||
    ((unsigned char)lastchar==0xC2&&(unsigned char)c==0xA0))
    {typo[k]='\0';spaceflag=1;break;}
    if ((unsigned char)lastchar2==0xE2&&(unsigned char)lastchar==0x80&&((unsigned char)c==0x93||(unsigned char)c==0x94))
    {typo[k]='\0';spaceflag=1;break;}

//chars to ignore current word
if(c=='&'||c==';'||c==']'){
    typo[0]='\0';spaceflag=0;break;}

//chars to separate words
if (c=='\n' || c==' ' || c=='\t' || c=='-' ||c=='}'||
    c=='{'|| c=='\\'||c=='%'||c=='$'||c=='#'||
    (c>='('&&c<='/')||c=='^'||c=='~'||c=='!'||c==':'||
    c=='|'||(c>='<'&&c<='@')||(c>='['&&c<='_')) {
    typo[k]='\0';spaceflag=1;break;}

if(c==typo[k])k++;
}
if(textflag)typo[k]='\0';
if(strlen(typo)<12)continue;
//skip non hebrew
if((unsigned char)typo[0]!=0xD7)continue;

int min=0;
int max=milon_count;
while(max>=min){
    j=min+(max-min)/2;
    if (strcmp(typo,milon[j]) == 0){exists[j]++;p=milon[j]+strlen(milon[j])+1;
                                      fprintf(fp3, "\n$$$%s->%s? הקשר: $@$@ ~~~</nowiki>&&&== [[%s]] ==###<nowiki>~~~ ",typo,p,pagename);
                                      aftercount=AFTER;
                                      contextJump=1;
                                      //if there is newline, start after it
                                      for(i=BEFORE-2;i>0;i--)
                                          {
                                              if(context[i]=='\t'||context[i]=='\v'||
                                                 context[i]=='&'||context[i]==';'||
                                                 context[i]=='\n'||context[i]=='\r'){contextJump=i+1;break;}
                                          }
                                       if(context[BEFORE-1]=='\v'||
                                                 context[BEFORE-1]=='&'||context[BEFORE-1]==';'||
                                                 context[BEFORE-1]=='\n'||context[BEFORE-1]=='\r'){endofcontext--;}
                                       //if jumped more than word length, print word
                                      if((BEFORE-contextJump)<strlen(typo)+3)fprintf(fp3, "jjjjjj");
                                      //if no jump happened and char before it 0xD7, move one further
                                      if(contextJump==1&&(unsigned char)context[0]==0xD7)contextJump++;
                                      for(i=contextJump;i<endofcontext;i++)
                                         {fprintf(fp3, "%c",context[i]);}
                                      afterword=context[BEFORE-1];
                                      if(context[BEFORE-1]=='\v'||context[BEFORE-1]=='\n'||context[BEFORE-1]=='\r')afterword=' ';
                                      fprintf(fp3," </nowiki></br>@@@'''%s'''%c<nowiki>",typo,afterword);
                                      endofcontext=BEFORE;
                                      break;}
    if (strcmp(typo,milon[j])>0){min=j+1;}
    if (strcmp(typo,milon[j])<0){max=j-1;}
}
/*
if word start with moshe caleb
if(
                                (unsigned char)typo[1]==0x9E||
                                (unsigned char)typo[1]==0x91||
                                (unsigned char)typo[1]==0x9C||
                                (unsigned char)typo[1]==0x9B||
                                (unsigned char)typo[1]==0x94||
                                (unsigned char)typo[1]==0x95||
                                (unsigned char)typo[1]==0xA9
                                )
{
min=0;
max=milon_count;
while(max>=min){
   // if (min==milon_count)break;
    j=min+(max-min)/2;
    if (strcmp(typo+2,milon[j]) == 0)  {exists[j]++; break;}
    if (strcmp(typo+2,milon[j])>0){min=j+1;}
    if (strcmp(typo+2,milon[j])<0){max=j-1;}
}
//remove second prefix
if(
(unsigned char)typo[3]==0x9E||
(unsigned char)typo[3]==0x91||
(unsigned char)typo[3]==0x9C||
(unsigned char)typo[3]==0x9B||
(unsigned char)typo[3]==0x94||
(unsigned char)typo[3]==0x95||
(unsigned char)typo[3]==0xA9)//if second char moshe caleb
{
min=0;
max=milon_count;
while(max>=min){
   // if (min==milon_count)break;
    j=min+(max-min)/2;
    if (strcmp(typo+4,milon[j]) == 0)  {exists[j]++; break;}
    if (strcmp(typo+4,milon[j])>0){min=j+1;}
    if (strcmp(typo+4,milon[j])<0){max=j-1;}
}
}
}*/
}


for(i=0;i<milon_count;i++){
        if(exists[i])fprintf(fp3, "\n%s - %d", milon[i],exists[i]);}

fprintf(fp3,"\nFinally!");

fclose(fp1);
fclose(fp2);
fclose(fp3);
free(exists);
free(milon);
return 0;
}
