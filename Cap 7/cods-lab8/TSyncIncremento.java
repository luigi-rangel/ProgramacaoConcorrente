/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 8 */
/* Codigo: Incremento concorrente de uma variável compartilhada em Java usando monitor */
/* -------------------------------------------------------------------*/


//classe da estrutura de dados (recurso) compartilhado entre as threads
class Ss {
  //recurso compartilhado
  private long r;
  //construtor
  public Ss() { this.r = 0; }

  //operacao sobre o recurso compartilhado
  public synchronized void inc() { this.r++; }

  //operacao sobre o recurso compartilhado
  public synchronized long get() { return this.r; }
}


//classe que estende Thread e implementa a tarefa de cada thread do programa 
class Ts extends Thread {
   //identificador da thread
   private int id;
   //objeto compartilhado com outras threads
   private Ss s;
  
   //construtor
   public Ts(int tid, Ss s) { 
      this.id = tid; 
      this.s = s;
   }

   //metodo main da thread
   public void run() {
      System.out.println("Thread " + this.id + " esta executando...");
      for (int i=0; i<10000000; i++) {
         s.inc();  
      }
      System.out.println("Thread " + this.id + " terminou!"); 
   }
}


//classe da aplicacao
class TSyncIncremento {
   static final int N = 2;

   public static void main (String[] args) {
      //reserva espaço para um vetor de threads
      Thread[] threads = new Thread[N];
      //cria uma instancia do recurso compartilhado entre as threads
      Ss s = new Ss();

      //cria as threads da aplicacao
      for (int i=0; i<threads.length; i++) {
         threads[i] = new Ts(i, s);
      }

      //inicia as threads
      for (int i=0; i<threads.length; i++) {
         threads[i].start();
      }

      //espera pelo termino de todas as threads
      for (int i=0; i<threads.length; i++) {
         try { threads[i].join(); } catch (InterruptedException e) { return; }
      }

      System.out.println("Valor de s = " + s.get()); 
   }
}
