
public class simpleThreads {

  private static int gsum=0;
  
  private static class incrementThread implements Runnable {
          
    public void run() {
      for(int i=0; i < 100; i++) {
        gsum=gsum+1;
        System.out.format("incrementThread: gsum=%d\n", gsum);
      }
    }
   
  }

    private static class decrementThread implements Runnable {
          
    public void run() {
      for(int i=0; i < 100; i++) {
        gsum=gsum-1;
        System.out.format("decrementThread: gsum=%d\n", gsum);
      }
    }
   
  }
    
    public static void main(String args[]) throws InterruptedException {
      
        // Delay, in milliseconds before we interrupt thread (default one hour).
        long patience = 1000 * 60 * 60;

        System.out.println("Starting increment and decrement threads");

        Thread inct = new Thread(new incrementThread());
        Thread dect = new Thread(new decrementThread());
        
        inct.start();
        dect.start();
        
        // need a join here to avoide early completion of main thread
        System.out.println("Main will loop until it can join both threads to complete");
    
        // Option 1 - just wait indefinitely
        //inct.join();
        //dect.join();
        
       // Option 2 - loop on aliveness and join with 1000 millisec timout on wait
       long startTime = System.currentTimeMillis();
       while (inct.isAlive()) {
            inct.join(1000);
            
            if (((System.currentTimeMillis() - startTime) > patience) && inct.isAlive()) {
                inct.interrupt();
                inct.join();
            }
       }
       
       startTime = System.currentTimeMillis();
       while (dect.isAlive()) {
            dect.join(1000);
            
            if (((System.currentTimeMillis() - startTime) > patience) && dect.isAlive()) {
                dect.interrupt();
                dect.join();
            }
       }
        
        System.out.println("TEST COMPLETE\n");
    }
  
}
