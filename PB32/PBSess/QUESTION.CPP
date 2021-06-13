#include "proboard.hpp"

#include <string.h>
#include <stdlib.h>

static void
adjust_parms(char *s,QString *param)
{
char delimiter;

strip_linefeed(s);

for(int i=0;i<4;i++)
        {
        param[i].clear();
        while(*s==' ' && *s) s++;
        if(*s=='\0') break;
        if(*s=='\"') delimiter=*s++;
                else delimiter=' ';
        for(int j=0;*s!=delimiter && (*s);j++) param[i] << (*s++);
        }
}

#define NUMCOMMANDS 18

int
mQuestionnaire(char *data)
{
char str[300];
char *commands[]={ "ASK" ,
                   "CHANGECOLOR",
                   "OUTPUTANSWER",
                   "POSTINFO",
                   "QUIT",
                   "SETFLAG",
                   "CLEARSCREEN",
                   "DISPLAY",
                   "ENDIF",
                   "IF",
                   "GETCHOICE",
                   "CAPITALISE",
                   "DISPLAYFILE",
                   "EXEC",
                   "LISTANSWER",
                   "MENUCMND",
                   "SETSECURITY",
                   "WAITENTER"
                   };
QString answers[30];
QString param[4];
QFile qf;
QFileName qafile(CurrentLanguage.questPath[0] ? CurrentLanguage.questPath : SysPath,data,".Q-A");
QFileName aswfile(data,".ASW");
int i;
bool capitalise = FALSE;

if(!qf.open(qafile,fmode_read | fmode_text))
    {
    if(strcmpl(data,"NEWUSER"))
      {
       LOG("File %s not found!",(char *)qafile);
       io << "\n\n\1Scriptfile not found! " << S_PRESS_ENTER_TO_CONTINUE;
      }
      return 1;
    }

LOG(2,"Questionnaire: %s",data);

for(;;)
    {
    if(!qf.readLine(str,299)) break;
    adjust_parms(str,param);
    for(i=0;i<NUMCOMMANDS;i++)
          {
          if(param[0].stricmp(commands[i]))
             {
             switch(i)
               {
               case 0: {
                        char s[80];
                        Input(s,atoi(param[1]),capitalise?INPUT_UPFIRST:0);
                        answers[atoi(param[2])-1]=s;
                        io << '\n';
                       } break;
               case 1: Color(atoi(param[1])); break;
               case 2: {
                        QFile f(aswfile,fmode_write | fmode_append | fmode_copen | fmode_text);
                        if(param[2][0]) f << form("%s%s\n",(char *)param[1],(char *)answers[atoi(param[2])-1]);
                                   else f << form("%s\n",(char *)answers[atoi(param[1])-1]);
                       } break;
               case 3: {
                        QDate date(TODAY);
                        QTime time(NOW);
                        QFile f(aswfile,fmode_write | fmode_append | fmode_copen | fmode_text);
                        f << form("*** %s completed questionnaire at %s on %s ***\n",user.name,(char *)date.format("DD MMM YYYY"),(char *)time.format("HH:MM"));
                       } break;
               case 4: return 1;
               case 5: {
                        int flag = -1;

                        strupr(param[1]);
                        if(param[1][1]>='1' && param[1][1]<='8')
                          {
                           switch(param[1][0])
                             {
                              case 'A': flag = param[1][1]-'1'+1;  break;
                              case 'B': flag = param[1][1]-'1'+9;  break;
                              case 'C': flag = param[1][1]-'1'+17; break;
                              case 'D': flag = param[1][1]-'1'+25; break;
                             }
                          }
                         else
                          {
                           if(param[1][0]>='A' && param[1][0]<='Z') flag = param[1][0]-'A'+1;
                           if(param[1][0]>='1' && param[1][0]<='6') flag = param[1][0]-'1'+27;
                          }

                        if(flag<1 || flag>32) break;

                        if(param[2]==QString("ON"))  user.aFlags.setflag(flag);
                        if(param[2]==QString("OFF")) user.aFlags.clearflag(flag);

                        MenuStack.Update = TRUE;
                       } break;
               case 6: Cls();
                       break;
               case 7: {
                        for(int i=0;i<param[1].len();i++) if(param[1][i]=='|') param[1][i]='\n';
                        io << param[1];
                       } break;
               case 9: {
                        if(answers[atoi(param[1])-1]==param[3]) break;
                        do
                         {
                          if(!qf.readLine(str,299)) return 1;
                          adjust_parms(str,param);
                         } while(!param[0].stricmp(commands[8]));
                        } break;
               case 10: {
                         char c = WaitKeys(param[1]);
                         answers[atoi(param[2])-1] = QString(c);
                         io << c << '\n';
                        } break;
               case 11: if(param[1]==QString("ON")) capitalise = TRUE;
                                      else capitalise = FALSE;
                        break;
               case 12: ShowAnsiFile(param[1]);
                        break;
               case 13: mShell(param[1]);
                        break;
               case 14: io << (char *)answers[atoi(param[1])-1] << '\n';
                        break;
               case 15: (*(menufunctions[atoi(param[1])]))(param[2]);
                        break;
               case 16: user.level = atoi(param[1]);
                        MenuStack.Update = TRUE;
                        break;
               case 17: io << "\t\n";
                        break;
               }
             }
          }
        }

   return 0;
}
