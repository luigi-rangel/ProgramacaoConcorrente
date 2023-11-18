import numpy as np
import math
from multiprocessing.pool import Pool
import time

#função de verificação de primalidade como descrita pelo pseudocódigo da professora Silvana
def primeCheck(n):
    if n <= 1:
        return 0
    if n == 2:
        return 1
    if n % 2 == 0:
        return 0

    for i in range(3, math.ceil(math.sqrt(n)) + 1):
        if n % i == 0:
            return 0

    return 1


if __name__ == '__main__':
    start = time.time()
    # por default, cria um processo distinto para cada processador da maquina
    pool = Pool(10)

    n_tests = 10000000
    numbers = [i for i in range(n_tests)]

    # map aceita uma funcao e um objeto iteravel, o pool pega cada valor do objeto iteravel e passa para um processo disponivel no poll que aplica a funcao sobre esse valor
    results = np.array(pool.map(primeCheck, numbers))

    end = time.time()

    #printando a soma de '1's no array de resultados, ou seja, a qtd de primos encontrada
    print(results.sum(), "primos foram encontrados entre 0 e", n_tests)
    print('resultado encontrado em {} segundos'.format(end - start))
