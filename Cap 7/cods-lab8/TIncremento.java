/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 7 */
/* Codigo: Incremento concorrente de uma variável compartilhada em Java */
/* -------------------------------------------------------------------*/


//classe da estrutura de dados (recurso) compartilhado entre as threads
class S {
  //recurso compartilhado
  private long r;
  //construtor
  public S() { this.r = 0; }

  //operacao sobre o recurso compartilhado
  public void inc() { this.r++; }

  //operacao sobre o recurso compartilhado
  public long get() { return this.r; }
}


//classe que estende Thread e implementa a tarefa de cada thread do programa 
class T extends Thread {
   //identificador da thread
   private int id;
   //objeto compartilhado com outras threads
   private S s;
  
   //construtor
   public T(int tid, S s) { 
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
class TIncremento {
   static final int N = 2;

   public static void main (String[] args) {
      //reserva espaço para um vetor de threads
      Thread[] threads = new Thread[N];
      //cria uma instancia do recurso compartilhado entre as threads
      S s = new S();

      //cria as threads da aplicacao
      for (int i=0; i<threads.length; i++) {
         threads[i] = new T(i, s);
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
