/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 8 */
/* Codigo: Usando facilidades do pacote java.util.concurrent.atomic */
/* -------------------------------------------------------------------*/

import java.util.concurrent.atomic.*;

//classe da estrutura de dados (recurso) compartilhado entre as threads
class Sa {
  //recurso compartilhado
  private AtomicLong r;
  //construtor
  public Sa(long init) { 
     this.r = new AtomicLong(init); 
  }

  //operacao sobre o recurso compartilhado
  public long get() {
    return r.get();
  }

  //operacao sobre o recurso compartilhado
  public void inc(){
    this.r.getAndIncrement();  
  }
}

//classe que estende Thread e implementa a tarefa de cada thread do programa 
class Ta extends Thread {
   //identificador da thread
   private int id;
   //objeto compartilhado com outras threads
   private Sa s;
   
   //construtor
   public Ta(int tid, Sa s) { 
      this.id = tid; 
      this.s = s;
   }

   //metodo main da thread
   public void run() {
      System.out.println("Thread " + this.id + " esta executando...");
      for (int i=0; i<10000000; i++) {
         this.s.inc();  
      }
      System.out.println("Thread " + this.id + " terminou!"); 
   }
}

//classe da aplicacao
class TAtomicIncremento {
   static final int N = 2;

   public static void main (String[] args) {
      //reserva espaço para um vetor de threads
      Thread[] threads = new Thread[N];
      //cria uma instancia do recurso compartilhado entre as threads
      Sa s = new Sa(0); 

      //cria as threads da aplicacao
      for (int i=0; i<threads.length; i++) {
         threads[i] = new Ta(i, s);
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
