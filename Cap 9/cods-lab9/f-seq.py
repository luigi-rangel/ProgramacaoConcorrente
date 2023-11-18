import time

#funcao que sera executada de forma sequencial
def task(x):
    for i in range(50000000):
        pass
    return x ** 2

if __name__ == '__main__':
    start = time.time()
    for aux in range(10):
        result = task(aux)
        print(result)
    end = time.time()
    print('work took {} seconds'.format(end - start))

