#include "mbed.h"

static void bgThreadTask()
{
   while (true)
   {
      osEvent ose = Thread::signal_wait(0);

      if (ose.value.v == 1)
      {
         printf("\r\nSignal received!\r\n");
         break;
      }
   }
};

int main()
{
   Thread bgThread;

   Callback<void()> bgThreadCB(bgThreadTask);

   bgThread.start(bgThreadCB);
   bgThread.signal_set(1);

   bgThread.join();

   // indicator LED if we get this far
   DigitalOut led2(LED2, 0); // on

   while (true)
   {
      sleep();
   }
}
