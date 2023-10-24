#Define funcoes para verificar a logica de execucao de uma aplicacao leitor/escritor

class LE:
	def __init__(self):
		self.escritores = 0
		self.leitores = 0
		self.escritoresEsperando = 0 # incrementado a cada escritor bloqueado e decrementado a cada liberação da escrita
		self.linha = 2 # exibir a linha em que ocorre o erro

	def leitorBloqueado(self,id):
		'''Recebe o id do leitor. Verifica se a decisao de bloqueio esta correta.'''
		self.linha += 1
		if self.escritores == 0 and self.escritoresEsperando == 0:
			print(str(self.linha) + " - ERRO: leitor " + str(id) + " bloqueado quando nao ha escritores!")

	def escritorBloqueado(self,id):
		'''Recebe o id do escritor. Verifica se a decisao de bloqueio esta correta.'''
		self.linha += 1
		if self.escritores==0 and self.leitores==0:
			print(str(self.linha) + " - ERRO: escritor " + str(id) + " bloqueado quando nao ha escritores nem leitores!")
		self.escritoresEsperando += 1

	def leitorLendo(self,id):
		'''Recebe o id do leitor, verifica se pode ler e registra que esta lendo.'''
		self.linha += 1
		if self.escritores>0 and self.escritoresEsperando != 0:
			print(str(self.linha) + " - ERRO: leitor " + str(id) + " esta lendo quando ha escritor escrevendo ou esperando!")
		self.leitores+=1

	def escritorEscrevendo(self,id):
		'''Recebe o id do escritor, verifica se pode escrever e registra que esta escrevendo'''
		self.linha += 1
		if self.escritores>0 or self.leitores>0:
			print(str(self.linha) + " - ERRO: escritor " + str(id) + " esta escrevendo quando ha outro escritor ou leitores!")
		self.escritores+=1
		self.escritoresEsperando -= 1

	def leitorSaindo(self,id):
		'''Recebe o id do leitor e registra que terminou a leitura.'''
		self.linha += 1
		self.leitores-=1

	def escritorSaindo(self,id):
		'''Recebe o id do escritor e registra que terminou a leitura.'''
		self.linha += 1
		self.escritores-=1