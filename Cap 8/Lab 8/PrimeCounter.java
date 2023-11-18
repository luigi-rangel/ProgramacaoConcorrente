/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Aluno: Luigi Rangel */
/* Laboratório: 8 */
/* Codigo: Utilizando pool de threads para computação do número de primos em uma sequência */

import java.util.LinkedList;
import java.util.concurrent.atomic.*;

//-------------------------------------------------------------------------------
//Classe que define um pool de threads 
class FilaTarefas {
    private final int nThreads;
    private final MyPoolThreads[] threads;
    private final LinkedList<Runnable> queue;
    private boolean shutdown;

    // construtor
    public FilaTarefas(int nThreads) {
        this.shutdown = false;
        this.nThreads = nThreads;
        queue = new LinkedList<Runnable>();
        threads = new MyPoolThreads[nThreads]; // inicia o pool de threads
        for (int i = 0; i < nThreads; i++) {
            threads[i] = new MyPoolThreads();
            threads[i].start(); // inicia cada thread
        }
    }

    // método para alocar uma tarefa a uma thread
    public void execute(Runnable r) {
        synchronized (queue) {
            if (this.shutdown)
                return;
            queue.addLast(r);
            queue.notify();
        }
    }

    // método para fechar a pool de threads de maneira segura
    public void shutdown() {
        synchronized (queue) {
            this.shutdown = true;
            queue.notifyAll();
        }
        for (int i = 0; i < nThreads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                return;
            }
        }
    }

    // classe interna para implementar pool de threads
    private class MyPoolThreads extends Thread {
        public void run() {
            Runnable r;
            while (true) {
                synchronized (queue) {
                    while (queue.isEmpty() && (!shutdown)) {
                        try {
                            queue.wait(); // espera alguma tarefa
                        } catch (InterruptedException ignored) {
                        }
                    }
                    if (queue.isEmpty() && shutdown)
                        return;
                    r = queue.removeFirst(); // retira tarefa para ser executada na pool quando há uma thread livre
                }
                try {
                    r.run(); // executa tarefa
                } catch (RuntimeException e) {
                }
            }
        }
    }
}
// -------------------------------------------------------------------------------

// --PASSO 1: cria uma classe que implementa a interface Runnable
class PrimeTester implements Runnable {
    Integer test;
    AtomicInteger nPrimes;

    public PrimeTester(Integer i, AtomicInteger nPrimes) {
        this.test = i;
        this.nPrimes = nPrimes;
    }

    // metodo executado pela thread, verifica primalidade de um numero teste
    public void run() {
        int i;

        if (test <= 1)
            return;
        if (test == 2)
            nPrimes.incrementAndGet(); // se for primo incrementa o numero de primos encontrado
        if (test % 2 == 0)
            return;
        for (i = 3; i < Math.sqrt(test) + 1; i += 2)
            if (test % i == 0)
                return;
        nPrimes.incrementAndGet(); // se for primo incrementa o numero de primos encontrado
    }
}

public class PrimeCounter {
    private static final int NTHREADS = 6;
    private static final int NTESTS = 10000000;

    public static void main(String[] args) {
        // --PASSO 2: cria o pool de threads
        FilaTarefas pool = new FilaTarefas(NTHREADS);
        AtomicInteger parNPrimes = new AtomicInteger(0);
        AtomicInteger seqNPrimes = new AtomicInteger(0);

        // --PASSO 3: dispara a execução dos objetos runnable usando o pool de threads
        for (Integer i = 0; i < NTESTS; i++) {
            Runnable r = new PrimeTester(i, parNPrimes);
            pool.execute(r);
        }

        // --PASSO 4: esperar pelo termino das threads
        pool.shutdown();

        // --PASSO 5: verificar a quantidade de primos no mesmo intervalo de forma sequencial
        for (int i = 0; i < NTESTS; i++) {
            PrimeTester r = new PrimeTester(i, seqNPrimes);
            r.run();
        }

        System.out.println("Número encontrado pela solução paralela: " + parNPrimes);
        System.out.println("Número encontrado pela solução sequencial: " + seqNPrimes);
        System.out.println("A computação paralela do algoritmo foi " +
                (seqNPrimes.get() == parNPrimes.get() ? "correta" : "incorreta"));
    }
}