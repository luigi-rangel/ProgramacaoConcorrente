/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 3 */
/* Codigo: Estendendo a classe Thread de Java */


//--PASSO 1: cria uma classe que estende a classe Thread 
class Ola extends Thread {
   private String msg;
   
   //--construtor
   public Ola(String m) { 
      this.msg = m; 
   }

   //--metodo executado pela thread
   public void run() {
      System.out.println(msg); 
   }
}

//--classe do metodo main
class OlaThread {
   static final int N = 10;

   public static void main (String[] args) {
      //--reserva espaço para um vetor de threads
      Thread[] threads = new Thread[N];
    
      //--PASSO 2: cria threads da classe que estende Thread
      for (int i=0; i<threads.length; i++) {
         final String m = "Ola da thread " + i;
         threads[i] = new Ola(m);
      }

      //--PASSO 3: iniciar as threads
      for (int i=0; i<threads.length; i++) {
         threads[i].start();
      }

      //--PASSO 4: esperar pelo termino de todas as threads
      for (int i=0; i<threads.length; i++) {
         try { threads[i].join(); } 
         catch (InterruptedException e) { return; }
      }

      System.out.println("Terminou"); 
   }
}
