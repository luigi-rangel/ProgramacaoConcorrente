#exemplo de uso de futuros em Python

import concurrent.futures
import time

#funcao que sera executada de forma assincrona
def task(x):
    for i in range(50000000):
        pass
    return x ** 2

if __name__ == '__main__':
    start = time.time()
    #cria um pool de threads OU de processos com no maximo 5 intancias 
    #with concurrent.futures.ThreadPoolExecutor(max_workers=5) as executor:
    with concurrent.futures.ProcessPoolExecutor(max_workers=5) as executor:
        futures = []
        
        #submete a tarefa para execucao assincrona
        for aux in range(10):
            futures.append(executor.submit(task, aux))
        #recebe os resultados
        for future in futures:
            result = future.result()
            print(result)
    end = time.time()
    print('work took {} seconds'.format(end - start))
