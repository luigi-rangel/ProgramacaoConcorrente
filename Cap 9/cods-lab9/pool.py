#exemplo de uso de pool de processos em Python

from multiprocessing.pool import Pool
import time

#funcao que sera executada de forma concorrente
def task(x):
    for i in range(50000000):
        pass
    return x ** 2

if __name__ == '__main__':
    start = time.time()
    pool = Pool() #por default, cria um processo distinto para cada processador da maquina

    numbers = list(range(10))
    #map aceita uma funcao e um objeto iteravel, o pool pega cada valor do objeto iteravel e passa para um processo disponivel no poll que aplica a funcao sobre esse valor
    results = pool.map(task, numbers)
    print(results)
    end = time.time()
    print('work took {} seconds'.format(end - start))
