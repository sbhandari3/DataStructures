#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Job.h"
#include "IntegerQueue.h"

//-----------------------------------------------------------------------------
// The following function may be of use in assembling the initial backup array.
// You may use it as is, alter it as you see fit, or delete it altogether.
//-----------------------------------------------------------------------------

// getjob()
// Reads two numbers from file in, and returns a new Job with those numbers
// as arrival and duration.
Job getJob(FILE* in){
   int a, d;
   fscanf(in, "%d %d\n", &a, &d);
   return newJob(a, d);
}

//-----------------------------------------------------------------------------
// The following stub for function main() contains a possible algorithm for 
// this project.  Follow it if you like.  Note that there are no instructions 
// included below for writing to either of the output files.  You must 
// intersperse those commands as necessary.
//-----------------------------------------------------------------------------

// main()
int main(int argc, char* argv[]){

   // check command line arguments
   /*FILE *in, *out1, *out2;
   int n, m, time;
   Queue queue = newQueue();
   if( argc != 2 ){
      printf("Usage: %s <input <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   } 
   // open files for reading and writing
   in = fopen(argv[1], "r");
   if( in==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }
   out1 = fopen(strcat(argv[1], ".rpt"), "w");
   out2 = fopen(strcat(argv[1], ".trc"), "w");
   // read in m jobs from input file and place them in backup array
   fscanf(in, "%d", &m);
   for(int i = 0; i < m; i ++){
      enque(queue, getJob(in));
      lengthOfArray++;
   }
   fprintf(out2, "Trace file: %s.trc\n", argv[1]);
   fprintf(out2, "%d Jobs:\n", m);
   char* str = QueueToString(queue);
   fprintf(out2, "%s\n", str);
   // declare and initialize an array of m-1 processor Queues along with
   // any necessary storage queues
   for( n=1; n<m; n++){
      time = 0;
      Queue sim[n+1];
      for(int i=0; i<n+1;i++)
         sim[i]= newQueue();
      fprintf(out2, "*****************************\n");
      fprintf(out2, "%d processor:\n", n);
      fprintf(out2, "*****************************\n");
      sim[0]=queue;
      while(getFinish(((pek(sim[0])))) == -1 || lengt(sim[0]) !=m){
         if(time == 0){
            fprintf(out2, "time = %d", time);
            for(int x = 0; x < n+1; x ++)
               fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
            time = getArrival((pek(sim[0])));
            enque(sim[1], deque(sim[0]));
            Job temp = pek(sim[1]);
            computeFinishTime(temp, time);
         }
         else if(getFinish(pek(sim[0])) != -1){
            int small = getIndex(sim);
            time = getFinish(((pek(sim[small]))));
            enque(sim[0], deque(sim[small]));
            fprintf(out2, "time = %d", time);
            for(int x = 0; x < n+1; x ++)
               fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
         }
         else{
            fprintf(out2, "time = %d", time);
            for(int x = 0; x < n+1; x ++)
               fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
            int small = getIndex(sim);
            if(lengt(sim[small]) == 0){
               time = getArrival(((pek(sim[0]))));
               enque(sim[small], deque(sim[0]));
               Job temp = (pek(sim[small]));
               computeFinishTime(temp,time);
               fprintf(out2, "time = %d", time);
               for(int x = 0; x < n+1; x ++)
                  fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
               small = getIndex(sim);
               time = getFinish((((pek(sim[small])))));
               enque(sim[0], deque(sim[small]));
               fprintf(out2, "time = %d", time);
               for(int x = 0; x < n+1; x ++)
                  fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
               small = getIndex(sim);
               time = getArrival(((pek(sim[0]))));
               enque(sim[small], deque(sim[0]));
               temp = (pek(sim[small]));
               computeFinishTime(temp, time);
               fprintf(out2, "time = %d", time);
               for(int x = 0; x < n+1; x ++)
                  fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
               time = getFinish(((pek(sim[small+1]))));
               enque(sim[0], deque(sim[small+1]));
               fprintf(out2, "time = %d", time);
               for(int x = 0; x < n+1; x ++)
                  fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
               small = getIndex(sim);
               time = getFinish(((pek(sim[small-1]))));
               enque(sim[0], deque(sim[small-1]));
               fprintf(out2, "time = %d", time);
               for(int x = 0; x < n+1; x ++)
                  fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
            }
            else if(getArrival((pek(sim[0]))) <= getFinish((Job)(pek(sim[0])))){
               time = getArrival((pek(sim[0])));
               enque(sim[small], deque(sim[0]));
               fprintf(out2, "time = %d", time);
               for(int x = 0; x < n+1; x ++)
                  fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
               time = getFinish((pek(sim[small])));
               enque(sim[0], deque(sim[small]));
               Job temp = pek((sim[small]));
               computeFinishTime(temp, time);
               fprintf(out2, "time = %d", time);
               for(int x = 0; x < n+1; x ++)
                  fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
            }
            else{
               Job temp = pek((sim[small]));
               computeFinishTime(temp, time);
               fprintf(out2, "time = %d", time);
               for(int x = 0; x < n+1; x ++)
                  fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
               time = getFinish(((pek(sim[small]))));
               enque(sim[0], deque(sim[small]));
               fprintf(out2, "time = %d", time);
               for(int x = 0; x < n+1; x ++)
                  fprintf(out2, "%d: %s", x, QueueToString(sim[x]));
            }
         }
      }
      if(n == 1){
         fprintf(out1, "Report file: %s.rpt\n", argv[1]);
         fprintf(out1, "%d Jobs:\n", m);
         fprintf(out1, "%s\n", QueueToString(sim[0]));
         fprintf(out1, "************************************************");
      }
      float averageWait=0;
      int totalWait=0;
      int maxWait=0;
      int max=0;
      Queue hold = newQueue();
      while(lengt(sim[0]) != 0){
         max = getWaitTime(((pek(sim[0]))));
         if(maxWait < max)
            maxWait = max;
         totalWait += getWaitTime(((pek(sim[0]))));
         enque(hold, deque(sim[0]));
      }
      averageWait =(float)totalWait/m;
      fprintf(out1, "%d processor: totalWait=%d maxWait=%d averageWait=%f", n, totalWait, maxWait, averageWait);
      while(lengt(hold) != 0){
         resetFinishTime(pek(hold));
         enque(queue, deque(hold));
      }
      fprintf(out1, "\n");
   }
   fclose(in);
   fclose(out1);
   fclose(out2);
}
    
   // loop: run simulation with n processors for n=1 to n=m-1 {
   // 
   //    place Job indices from backup array into storage queue
   // 
   //    loop: process all Jobs in this simulation {
   //
   //       determine the time of the next arrival or finish event and update time
   //
   //       if any Jobs finish now, then complete them in the order they appear in 
   //       the queue array, i.e. lowest index first.
   //
   //       if any Jobs arrive now, then assign them to a processor queue 
   //       of minimum length and with lowest index in the queue array.
   //
   //    } end loop
   //
   //    compute the total wait, maximum wait, and average wait for 
   //    all Jobs, then reset finish times for next simulation
   //
   // } end loop
   //
   // free all heap memory, close input and output files

  
}*/
   return(EXIT_SUCCESS);
}
