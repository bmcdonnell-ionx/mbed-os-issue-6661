#include "mbed.h"
#include "cmsis.h" // SCnSCB->ACTLR, etc.

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
   // make fault handler report precise crash location
   //   https://github.com/ARMmbed/mbed-os/issues/6661#issuecomment-383149796
   //   https://os.mbed.com/docs/v5.8/tutorials/analyzing-mbed-os-crash-dump.html#debugging-imprecise-bus-faults
   SCnSCB->ACTLR |= SCnSCB_ACTLR_DISDEFWBUF_Msk;

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
