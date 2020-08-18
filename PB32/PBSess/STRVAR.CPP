#include "proboard.hpp"

#include <stdio.h>
#include <stdlib.h>


static
 char *varnames[] = { /*  0 */ "NAME",
                      /*  1 */ "CITY",
                      /*  2 */ "NODE",
                      /*  3 */ "SYSDIR",
                      /*  4 */ "STARTDIR",        // Obsolete
                      /*  5 */ "UPDIR",
                      /*  6 */ "PVTDIR",
                      /*  7 */ "BAUD",
                      /*  8 */ "PORT",            // Obsolete
                      /*  9 */ "FIRSTNAME",
                      /* 10 */ "LASTNAME",
                      /* 11 */ "TMLEFT",
                      /* 12 */ "TMONLINE",
                      /* 13 */ "LEVEL",
                      /* 14 */ "DATE",
                      /* 15 */ "TIME",
                      /* 16 */ "HANDLE",
                      /* 17 */ "MNUDIR",
                      /* 18 */ "TXTDIR",
                      /* 19 */ "MSGDIR",
                      /* 20 */ "SYSOPNAME",
                      /* 21 */ "PASSWORD",
                      /* 22 */ "NLDIR",
                      /* 23 */ "PEXDIR",
                      /* 24 */ "CURFILEAREA#",
                      /* 25 */ "CURMSGAREA#",
                      /* 26 */ "CURFILEAREA",
                      /* 27 */ "CURMSGAREA",
                      /* 28 */ "CURMENU",
                      /* 29 */ "NUMUSERS",
                      /* 30 */ "ID",
                      /* 31 */ "USERREC",
                      /* 32 */ "#1",
                      /* 33 */ "#2",
                      /* 34 */ "#3",
                      /* 35 */ "#4",
                      /* 36 */ "#5",
                      /* 37 */ "#6",
                      /* 38 */ "#7",
                      /* 39 */ "#B1",
                      /* 40 */ "#B2",
                      /* 41 */ "#B3",
                      /* 42 */ "#B4",
                      /* 43 */ "#B5",
                      /* 44 */ "#B6",
                      /* 45 */ "#B7",
                      /* 46 */ "NUMMSG",
                      /* 47 */ "LOWMSG",
                      /* 48 */ "HIGHMSG",
                      /* 49 */ "TOTALMSG",
                      /* 50 */ "LASTDATE",
                      /* 51 */ "LASTTIME",
                      /* 52 */ "TOTALCALLS",
                      /* 53 */ "VERSION",
                      /* 54 */ "VOICEPHONE",
                      /* 55 */ "DATAPHONE",
                      /* 56 */ "COUNTRY",
                      /* 57 */ "NUMYELLS",
                      /* 58 */ "CURFILEAREADIR",
                      /* 59 */ "CURFILEGROUP#",
                      /* 60 */ "CURMSGGROUP#",
                      /* 61 */ "CURFILEGROUP",
                      /* 62 */ "CURMSGGROUP",
                      /* 63 */ "LANGUAGE",
                      NULL };


QString
StringVar(char *s,int len)
{
   QString tmp;

   len = -len;

   if(s[0]=='%')
   {
      if(getenv(&s[1])) tmp = getenv(&s[1]);

      return tmp;
   }

   for(int i=0;varnames[i];i++)
   {
      char ts[80];

      if(strcmpl(varnames[i],s)) continue;

      switch(i)
      {
          case  0: sprintf(ts,"%*s",len,user.name);
                   tmp = ts;
                   break;
          case  1: sprintf(ts,"%*s",len,user.city);
                   tmp = ts;
                   break;
          case  2: //sprintf(ts,"%*d",len,node_number);
                   //tmp = ts;
                   break;
          case  3: sprintf(ts,"%*s",len,(char *)SysPath);
                   tmp = ts;
                   break;
//          case  4: sprintf(ts,"%*s",len,mypath);
//                   tmp = ts;
//                   break;
          case  5: sprintf(ts,"%*s",len,cfg.uploadPath);
                   tmp = ts;
                   break;
          case  6: sprintf(ts,"%*s",len,cfg.pvtUploadPath);
                   tmp = ts;
                   break;
          case  7: sprintf(ts,"%*ld",len,BaudRate);
                   tmp = ts;
                   break;
//          case  8: sprintf(ts,"%*d",len,port+1);
//                   tmp = ts;
//                  break;
          case  9: sprintf(ts,"%*s",len,(char *)user.FirstName());
                   tmp = ts;
                   break;
          case 10: {
                    for(int i=0;i<(int)strlen(user.name);i++)
                        if(user.name[i]==' ') break;

                    sprintf(ts,"%*s",len,&user.name[i+1]);
                    tmp = ts;
                   }
                   break;
//          case 11: sprintf(ts,"%*d",len,timer.left());
//                   tmp = ts;
//                   break;
//          case 12: sprintf(ts,"%*d",len,timer.online());
//                   tmp = ts;
//                   break;
          case 13: sprintf(ts,"%*u",len,user.level);
                   tmp = ts;
                   break;
          case 14: {
                    QDate d(TODAY);

                    tmp = d.format(DateFormats[user.dateFormat]);
                   } break;
          case 15: {
                    QTime t(NOW);
                    sprintf(ts,"%02d:%02d",t[0],t[1]);
                    tmp = ts;
                   } break;
          case 16: sprintf(ts,"%*s",len,user.alias);
                   tmp = ts;
                   break;
          case 17: sprintf(ts,"%*s",len,cfg.mnuPath);
                   tmp = ts;
                   break;
          case 18: sprintf(ts,"%*s",len,cfg.txtPath);
                   tmp = ts;
                   break;
          case 19: sprintf(ts,"%*s",len,cfg.msgPath);
                   tmp = ts;
                   break;
          case 20: sprintf(ts,"%*s",len,cfg.sysopName);
                   tmp = ts;
                   break;
          case 21: sprintf(ts,"%*s",len,user.passWord);
                   tmp = ts;
                   break;
          case 22: sprintf(ts,"%*s",len,cfg.nodeListDir);
                   tmp = ts;
                   break;
          case 23: sprintf(ts,"%*s",len,cfg.pexPath);
                   tmp = ts;
                   break;
          case 24: sprintf(ts,"%*u",len,user.fileArea);
                   tmp = ts;
                   break;
          case 25: sprintf(ts,"%*u",len,user.msgArea);
                   tmp = ts;
                   break;
//          case 26: {
//                    TpFileArea fa;
//                    if(fa.read(user.fileArea))
//                     sprintf(ts,"%*s",len,fa.name);
//                    else
//                     sprintf(ts,"%*s",len,"* None *");
//
//                    tmp = ts;
//                   } break;
//         case 27: {
//                    TpMsgArea ma;
//                    if(ma.read(user.msgArea))
//                     sprintf(ts,"%*s",len,ma.name);
//                    else
//                     sprintf(ts,"%*s",len,"* None *");
//
//                    tmp = ts;
//                   } break;
          case 28: sprintf(ts,"%*s",len,(char *)MenuStack.CurMenu);
                   tmp = ts;
                   break;
          case 29: sprintf(ts,"%*d",len,TpUser::NumUsers());
                   tmp = ts;
                   break;
//          case 30: {
//                    for(int i=0;i<num_limits;i++)
//                      if(limit[i].level==user.level)
//                        {
//                         sprintf(ts,"%*s",len,limit[i].id);
//                         tmp = ts;
//                        }
//                   }
//                   break;
          case 31: sprintf(ts,"%*d",len,user.record);
                   tmp = ts;
                   break;
          case 32: tmp = "\1";
                   break;
          case 33: tmp = "\2";
                   break;
          case 34: tmp = "\3";
                   break;
          case 35: tmp = "\4";
                   break;
          case 36: tmp = "\5";
                   break;
          case 37: tmp = "\6";
                   break;
          case 38: tmp = "\7";
                   break;
          case 39: tmp = "\x11";
                   break;
          case 40: tmp = "\x12";
                   break;
          case 41: tmp = "\x13";
                   break;
          case 42: tmp = "\x14";
                   break;
          case 43: tmp = "\x15";
                   break;
          case 44: tmp = "\x16";
                   break;
          case 45: tmp = "\x17";
                   break;
          case 46: {
                    TpMsgArea ma;
                    ma.read(user.msgArea);
                    sprintf(ts,"%*ld",len,ma.numMsgs());
                    tmp = ts;
                   }
                   break;
          case 47: sprintf(ts,"%*d",len,0);
                   tmp = ts;
                   break;
          case 48: sprintf(ts,"%*d",len,0);
                   tmp = ts;
                   break;
          case 49: sprintf(ts,"%*ld",len,msgbase.totalMsgs());
                   tmp = ts;
                   break;
          case 50: tmp = user.lastDate.format("DD MMM CCYY");
                   break;
          case 51: tmp = user.lastTime.format("HH:MM");
                   break;
//          case 52: sprintf(ts,"%*ld",len,TotalCalls());
//                   tmp = ts;
//                   break;
          case 53: sprintf(ts,"%*s",len,VERSION);
                   tmp = ts;
                   break;
          case 54: sprintf(ts,"%*s",len,user.voicePhone);
                   tmp = ts;
                   break;
          case 55: sprintf(ts,"%*s",len,user.dataPhone);
                   tmp = ts;
                   break;
          case 56: sprintf(ts,"%*s",len,user.country);
                   tmp = ts;
                   break;
          case 57: sprintf(ts,"%*d",len,NumYells);
                   tmp = ts;
                   break;
//          case 58: {
//                    TpFileArea fa;
//                    if(fa.read(user.fileArea))
//                     sprintf(ts,"%*s",len,fa.filepath);
//                    else
//                     sprintf(ts,"%*s",len,"* None *");
//
//                    tmp = ts;
//                   } break;
           case 59:  tmp = form("%d",user.fileGroup); break;
           case 60:  tmp = form("%d",user.msgGroup); break;
//           case 61:  {
//                        AreaGroup group;
//                        File f(QFileName(SysPath,"FGROUPS.PB"));
//                        f.seek(long(user.fileGroup-1) * sizeof(AreaGroup));
//                        if(f.read(&group,sizeof(AreaGroup)) != sizeof(AreaGroup))
//                           tmp = "";
//                        else
//                           tmp = group.name;
//                      }
//                      break;
//           case 62:  {
//                        AreaGroup group;
//                        File f(QFileName(syspath,"MGROUPS.PB"));
//                        f.seek(long(user.msgGroup-1) * sizeof(AreaGroup));
//                        if(f.read(&group,sizeof(AreaGroup)) != sizeof(AreaGroup))
//                           tmp = "";
//                        else
//                          tmp = group.name;
//                      }
//                      break;

           case 63:  sprintf(ts,"%*s",len,user.language);
                     tmp = ts;
                     break;
      }

    return tmp;
   }

   tmp = "[UNKNOWN:";
   tmp << s;
   tmp << ']';

   return tmp;
}

#pragma warning( disable : 4761 )

QString
ReplaceStringVars(char *s)
{
   QString tmp;
   QString varname;
   QString lenstr;
   bool invar = false;
   bool inlen = false;

   for(;*s;s++)
      switch(*s)
      {
         case '@':
         	{
               if(!invar)
               {
                  if(*(s+1) == '<')
                  {
                     invar = true;
                     inlen = false;
                     s++;
                     varname.clear();
                     lenstr.clear();
                     continue;
                  }
                 else
                  {
                     tmp << '@';
                  }
               }
            }
         	break;

      	case '>':
      		{
            	if(invar)
               {
               	if(*(s+1) == '@')
                  {
                  	s++;
                     tmp << StringVar(varname,inlen ? atoi(lenstr) : 0);
                  	invar = false;
                  	inlen = false;
                  }
               	continue;      // We don't want '>' chars in varnames
               }
            }
            break;

      	case ':':
         	{
            	if(invar)
               {
               	inlen = true;
                  continue;
               }
            }
            break;

      	default:
         	{
            	if(invar)
               {
               	if(inlen)
                  	lenstr  << (*s);
                  else
                  	varname << (*s);
               }
               else
               {
                  tmp << char((*s == '|') ? '\n' : (*s));
               }
            }
            break;
     }

 return tmp;
}
