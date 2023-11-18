#/* Disciplina: Programacao Concorrente */
#/* Prof.: Silvana Rossetto */
#/* Módulo 4 - Laboratório: 7 */
#/* Codigo: exemplo de aplicacao IO-bound */ 

#extraido de: "Python 3 Object-oriented Programming" (Cap 13), Dusty Phillips, 2nd edition, 2015.

from threading import Thread

#classe da thread
class InputReader(Thread):
    def run(self):
        #bloqueia esperando a entrada padrao
        print("Enter some text and press enter: ")
        self.line_of_text = input()

#funcao principal
if __name__ == '__main__':
    #cria e dispara a thread
    thread = InputReader()
    thread.start()
    #thread.run()

    #computacao que usa a CPU enquando a thread nao termina
    count = result = 1
    while thread.is_alive():
        result = count * count
        count += 1

    print("calculated squares up to {0} * {0} = {1}".format(count, result))
    print("while you typed '{}'".format(thread.line_of_text))
