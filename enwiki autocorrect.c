#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BEFORE 70
#define AFTER 150
int main()
{
   int milon_count=0;
   int i,j,k=0,lll=0,existing=0,textflag=0,fileflag=1,imageflag=1,templateflag=1,italicflag=1,divflag=1,
   codeflag=1,sourceflag=1,doublenewline=1,poemflag=1,
   galleryflag=1,linkflag=1,quoteflag=1,doublequoteflag=1,doublequoteflag2=1,columnsflag=1,
   spaceflag=0,noteflag=1,noteflag2=1,namecount=0,nameflag=0,namespaceflag=0, wiktionflag=1;
   int aftercount=0,contextJump=0, saweng=0,endofcontext=BEFORE;
   char afterword=' ';
   char typo[80];
   char oldtypo[80];
   char pagename[100];
   char *p;
   char *method;
   char *number;
   int place=0;
   char lastchar=0,lastchar2;
   char (*milon)[51];
   char context[BEFORE];
   milon = calloc (22000000, sizeof(char[51]));
   int *exists;
   exists = malloc (22000000 * sizeof(int));

   // to access character i of word w
   FILE *fp1 = fopen("Wikipedia-20220701120534.xml", "r");
   FILE *fp2 = fopen("typos1.txt", "r");
   FILE *fp3 = fopen("file3.txt", "w");

   if (fp1 == NULL || fp2 == NULL || fp3 == NULL )
   {
   puts("Could not open files");
   exit(0);
   }

   j=0;
   k=0;
   char c;
   while ((c = fgetc(fp2)) != EOF) //load main milon
   {
      milon[j][k]=c;
      if(j==22000000)break;
      if(k>49&&c!='\n')continue;
      if(c==',')milon[j][k]=0;
      if(c=='\n'){milon[j][k]=0;milon_count++;j++;k=0;} //end of word - move to next word
      if (c!='\n')k++;
   }
   printf("WOW");

   j=0;
   c=0;
   while (c!=EOF){//word loop
      k=0;typo[0]=0;
   while ((c = fgetc(fp1))!=EOF){//letter loop
      //print after context
      if(aftercount>0){
                        if(aftercount==1&&(unsigned char)c==0xD7)aftercount=0;
                        if(aftercount>0&&c!='\n'){fprintf(fp3, "%c", c); aftercount--;}
                     }

      //save article name: if <title>
      if(context[BEFORE-7]=='<'&&context[BEFORE-6]=='t'&&context[BEFORE-5]=='i'&&
         context[BEFORE-4]=='t'&&context[BEFORE-3]=='l'&&context[BEFORE-2]=='e'&&context[BEFORE-1]=='>')nameflag=1;

      if(nameflag==1){pagename[namecount]=c;namecount++;}
      if(nameflag==1&&context[BEFORE-1]=='<'&&c=='/'){pagename[namecount-2]=0;namecount=0;nameflag=0;}

      //close tags in new article
      if(nameflag==1)
         {divflag=1;codeflag=1;galleryflag=1;templateflag=1;doublenewline=1;
                  columnsflag=1;sourceflag=1;noteflag=1;noteflag2=1;}
      //only search within articles text
      if(context[BEFORE-4]=='<'&&context[BEFORE-3]=='t'&&
         context[BEFORE-2]=='e'&&context[BEFORE-1]=='x'&&c=='t'){textflag=1;}

      if(context[BEFORE-5]=='<'&&context[BEFORE-4]=='/'&&
         context[BEFORE-3]=='t'&&context[BEFORE-2]=='e'&&context[BEFORE-1]=='x'&&c=='t'){typo[0]=0;textflag=0;}

      //only search namespace 0
      if(context[BEFORE-4]=='<'&&context[BEFORE-3]=='n'&&
         context[BEFORE-2]=='s'&&context[BEFORE-1]=='>'&&c=='0'){namespaceflag=1;}

      if(context[BEFORE-4]=='<'&&context[BEFORE-3]=='n'&&
         context[BEFORE-2]=='s'&&context[BEFORE-1]=='>'&&c!='0'){typo[0]=0;namespaceflag=0;}

         //skip files
      if((context[BEFORE-4]=='F'||context[BEFORE-4]=='f')&&context[BEFORE-3]=='i'&&
         context[BEFORE-2]=='l'&&context[BEFORE-1]=='e'){typo[0]=0;fileflag=0;}
      if(fileflag==0&&c=='\n'){fileflag=1;}

         //skip files
      if((context[BEFORE-5]=='I'||context[BEFORE-5]=='i')&&context[BEFORE-4]=='m'&&
         context[BEFORE-3]=='a'&&context[BEFORE-2]=='g'&&context[BEFORE-1]=='e'){typo[0]=0;imageflag=0;}
      if(imageflag==0&&c=='\n'){imageflag=1;}

         //skip templates
      if(context[BEFORE-1]=='{'&&c=='{'){typo[0]=0;doublenewline=0;templateflag=0;}
      if(context[BEFORE-1]=='}'&&c!='}'){templateflag=1;}
      if(context[BEFORE-1]=='\n'&&c=='\n'){doublenewline=1;}
         //skip links
      if(context[BEFORE-1]=='['&&c=='h'){typo[0]=0;linkflag=0;}
      if(linkflag==0&&c==']'){linkflag=1;}
      if(linkflag==0&&c=='\n'){linkflag=1;}

         //skip blockquotes
      if(context[BEFORE-4]==';'&&context[BEFORE-3]=='b'&&
         context[BEFORE-2]=='l'&&context[BEFORE-1]=='o'&&c=='c'){typo[0]=0;k=0;quoteflag=0;}

      if(context[BEFORE-5]==';'&&context[BEFORE-4]=='/'&&
         context[BEFORE-3]=='b'&&context[BEFORE-2]=='l'&&context[BEFORE-1]=='o'&&c=='c'){typo[0]=0;quoteflag=1;}

      if(nameflag==1){quoteflag=1;}

         //skip doublequotes
      if(context[BEFORE-1]=='"'){typo[0]=0;doublequoteflag=0;}
      if(doublequoteflag==0&&c=='"'){doublequoteflag=1;}
      if(doublequoteflag==0&&c=='\n'){doublequoteflag=1;}

         //skip doublequotes2
      if(context[BEFORE-5]=='&'&&context[BEFORE-4]=='q'&&context[BEFORE-3]=='u'&&
         context[BEFORE-2]=='o'&&context[BEFORE-1]=='t'&&c==';'){typo[0]=0;doublequoteflag2=0;}

      if(context[BEFORE-4]=='&'&&context[BEFORE-3]=='q'&&context[BEFORE-2]=='u'&&context[BEFORE-1]=='o'&&c=='t')
         {doublequoteflag2=1;}
      if(doublequoteflag2==0&&c=='\n'){doublequoteflag2=1;}
         //skip italics
      if(context[BEFORE-2]=='\''&&context[BEFORE-1]=='\''){typo[0]=0;italicflag=0;}

      if(context[BEFORE-1]=='\''&&c=='\''){italicflag=1;}
      if(italicflag==0&&c=='\n'){italicflag=1;}

      //skip columns
      if(context[BEFORE-1]=='{'&&c=='|'){typo[0]=0;columnsflag=0;}
      if(context[BEFORE-1]=='|'&&c=='}'){columnsflag=1;}
      //skip notes
      if(context[BEFORE-4]==';'&&context[BEFORE-3]=='r'&&
         context[BEFORE-2]=='e'&&context[BEFORE-1]=='f'){typo[0]=0;noteflag=0;}

      if(context[BEFORE-5]==';'&&context[BEFORE-4]=='/'&&
         context[BEFORE-3]=='r'&&context[BEFORE-2]=='e'&&context[BEFORE-1]=='f'&&c=='&'){noteflag=1;}
      //skip notes
      if(context[BEFORE-3]==';'&&
         context[BEFORE-2]=='!'&&context[BEFORE-1]=='-'&&c=='-'){typo[0]=0;noteflag2=0;}

      if(context[BEFORE-2]=='-'&&context[BEFORE-1]=='-'&&c=='&'){noteflag2=1;}
      //skip div
      if(context[BEFORE-4]==';'&&context[BEFORE-3]=='d'&&
         context[BEFORE-2]=='i'&&context[BEFORE-1]=='v'){typo[0]=0;divflag=0;}

      if(context[BEFORE-5]==';'&&context[BEFORE-4]=='/'&&
         context[BEFORE-3]=='d'&&context[BEFORE-2]=='i'&&context[BEFORE-1]=='v'&&c=='&'){divflag=1;}
      //skip <code>
      if(context[BEFORE-4]==';'&&context[BEFORE-3]=='c'&&
         context[BEFORE-2]=='o'&&context[BEFORE-1]=='d'&&c=='e'){typo[0]=0;codeflag=0;}

      if(context[BEFORE-5]==';'&&context[BEFORE-4]=='/'&&
         context[BEFORE-3]=='c'&&context[BEFORE-2]=='o'&&context[BEFORE-1]=='d'&&c=='e'){codeflag=1;}

      //skip <poem>
      if(context[BEFORE-4]==';'&&context[BEFORE-3]=='p'&&
         context[BEFORE-2]=='o'&&context[BEFORE-1]=='e'&&c=='m'){typo[0]=0;poemflag=0;}

      if(context[BEFORE-5]==';'&&context[BEFORE-4]=='/'&&
         context[BEFORE-3]=='p'&&context[BEFORE-2]=='o'&&context[BEFORE-1]=='e'&&c=='m'){poemflag=1;}
      //skip <gallery>
      if(context[BEFORE-4]==';'&&context[BEFORE-3]=='g'&&
         context[BEFORE-2]=='a'&&context[BEFORE-1]=='l'&&c=='l'){typo[0]=0;galleryflag=0;}

      if(context[BEFORE-5]==';'&&context[BEFORE-4]=='/'&&
         context[BEFORE-3]=='g'&&context[BEFORE-2]=='a'&&context[BEFORE-1]=='l'&&c=='l'){galleryflag=1;}
      //skip <source>
      if(context[BEFORE-4]==';'&&context[BEFORE-3]=='s'&&
         context[BEFORE-2]=='o'&&context[BEFORE-1]=='u'&&c=='r'){typo[0]=0;sourceflag=0;}

      if(context[BEFORE-5]==';'&&context[BEFORE-4]=='/'&&
         context[BEFORE-3]=='s'&&context[BEFORE-2]=='o'&&context[BEFORE-1]=='u'&&c=='r'){sourceflag=1;}


      //save context
      for(i=0;i<BEFORE;i++){context[i]=context[i+1];}
      context[BEFORE-1]=c;


      if(k==79){spaceflag=0;break;}

      if(namespaceflag==1&&textflag==1&&spaceflag==1&&fileflag==1&&imageflag==1&&
         galleryflag==1&&italicflag==1&&columnsflag==1&&sourceflag==1&&doublenewline==1&&
         templateflag==1&&noteflag==1&&noteflag2==1&&divflag==1&&codeflag==1&&
         linkflag==1&&quoteflag==1&&doublequoteflag==1&&doublequoteflag2==1&&wiktionflag==1)
         {typo[k]=c;k++;}

      //ignore short links
      if(typo[k-2]=='.'&&typo[k-1]!=' '&&typo[k-1]!='\n')
         {typo[0]='\0';spaceflag=0;break;}

      //chars to separate words and initialize space
      if (c=='\n'||c==' '||c=='\t')
         {typo[k-1]='\0';spaceflag=1;break;}

      //chars to separate words and check
      if (c=='-'||c=='}'||c=='{'||c=='['||c==','||c=='.'||c=='"'||c==';'||
         c=='^'||c=='~'||c=='#'||c=='='||c=='&'||c==')'||
         c=='|'||c=='<'||c=='>'||c=='?'||c=='^'||c=='_')
      {typo[k-1]='\0';break;}

      //chars to delete words and wait for space
      if(k>0&&(c==':'||c=='%'||c=='('||c=='/'||c=='\\'||c=='@'||c=='$'||c=='!'))
      {typo[0]='\0';spaceflag=0;break;}

      }
      if(strlen(typo)<5)continue;
      int min=0;
      int max=milon_count;
      while(max>=min){
         j=min+(max-min)/2;
         if (strcmp(typo,milon[j]) == 0) {
            exists[j]++;
            p=milon[j]+strlen(milon[j])+1;
            method=p+strlen(p)+1;
            number=method+strlen(method)+1;
            if(strlen(number)==1)place=number[0]-48;
            if(strlen(number)==2)place=number[1]-38;
            fprintf(fp3, "\n$$$%s-><!--%s-->", typo,p);
            for(i=0;i<strlen(p);i++){
               if(i==place)fprintf(fp3, "'''%c'''",p[i]);
               if(i!=place)fprintf(fp3, "%c",p[i]);
            }
            fprintf(fp3, "? (%s) context: $@$@ ~~~</nowiki>&&&== [[%s]] ==###<nowiki>~~~ ",method,pagename);
            aftercount=AFTER;
            contextJump=1;

            //start context line after at least one space
            for(i=0;i<BEFORE-2;i++) {
                     if(context[i]=='\v'||context[i]==' '||
                        context[i]=='\n'||context[i]=='\r')
                        {contextJump=i+1;break;}
               }
            //if there is newline, start after it
            for(i=BEFORE-2;i>0;i--) {
               if(context[i]=='\v'||
                  context[i]=='&'||context[i]==';'||
                  context[i]=='\n'||context[i]=='\r') {
                     contextJump=i+1;break;
               }
            }
            if(context[BEFORE-1]=='\v'||
               context[BEFORE-1]=='&'||context[BEFORE-1]==';'||
               context[BEFORE-1]=='\n'||context[BEFORE-1]=='\r'){
                  endofcontext--;
            }
            //if jumped more than word length, print word
            if((BEFORE-contextJump)<strlen(typo)+3)fprintf(fp3, "jjjjjj");
            //if no jump happened and char before it 0xD7, move one further
            if(contextJump==1&&(unsigned char)context[0]==0xD7)contextJump++;
            for(i=contextJump;i<endofcontext-1;i++)
               {fprintf(fp3, "%c",context[i]);}
            fprintf(fp3," </nowiki></br>@@@'''%s''' <nowiki>",typo);
            endofcontext=BEFORE;
            break;}
         if (strcmp(typo,milon[j])>0){min=j+1;}
         if (strcmp(typo,milon[j])<0){max=j-1;}
      }
   }

   for(i=0;i<22000000;i++){
         if(exists[i])fprintf(fp3, "\n%s - %d", milon[i],exists[i]);}

   fprintf(fp3,"\nFinally!");

   fclose(fp1);
   fclose(fp2);
   fclose(fp3);
   free(exists);
   free(milon);
   return 0;
}
