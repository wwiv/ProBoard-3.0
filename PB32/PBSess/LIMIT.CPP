#include "ProBoard.hpp"

void
AdjustLimits()
{
   long kbgranted;
   int i,j;

   for(i=0;i<NumLimits-1;i++)
      for(j=i+1;j<NumLimits;j++)
         if(Limit[i].level<Limit[j].level)
         {
            TpLimit temp;

            temp     = Limit[i];
            Limit[i] = Limit[j];
            Limit[j] = temp;
         }

   for(int n=-1;;)
   {
      for(i=NumLimits-1;i>=0;i--)
         if(user.level>=Limit[i].level)
            n=i;

      if(n<0) return;

      if(Limit[n].maxDownload && user.kbDownloaded>Limit[n].maxDownload)
      {
         if(user.level != Limit[n].fallTo)
         {
            user.level = Limit[n].fallTo;

            continue;
         }
      }

      if(Limit[n].factor)
      {
         kbgranted =   long(user.kbUploaded)*100L / Limit[n].factor
                     + long(user.msgsPosted) * Limit[n].msgFactor
                     + Limit[n].freeKb;
      }
      else
         kbgranted=0x7FFFFFFFL;

      if((long)user.kbDownloaded > kbgranted)
      {
         if(!Limit[n].factor)
            UploadNeeded = 0x7FFF;
         else
            UploadNeeded=int((long(user.kbDownloaded)-kbgranted)*Limit[n].factor/100);

         FreeDownload=0;
      }
      else
      {
         FreeDownload = int(kbgranted-user.kbDownloaded);
         UploadNeeded = 0;

         if(FreeDownload > Limit[n].dailyDownloadLimit)
            FreeDownload = Limit[n].dailyDownloadLimit;
      }

      break;
   }

   TimeLimit     = Limit[n].timeLimit;
   DownloadLimit = Limit[n].dailyDownloadLimit;
   DownloadDelay = Limit[n].preDownloadDelay;

   timer.ChangeLeft(TimeLimit-timer.Used()-user.timeUsed-TimeRemoved);

   MenuStack.Update = TRUE;
}

