1. O que é seção crítica do código?
   - R: é a seção do código que acessa uma variável que pode ser acessada e modificada por outras threads.

2. O que é corrida de dados no contexto de computação concorrente?
   - R: É o erro gerado pelo acesso concorrente -- ou seja, por mais de uma thread -- a uma mesma área da memória, desde que ao menos um desses acessos seja de escrita.

3. O que significa uma operação ser atômica?
   - R: Significa que a operação só pode ser executada por completo antes que outro fluxo de execução comece a processá-la.

4. O que é sincronização por exclusão mútua?
   - R: É a criação de mecanismos para que trechos críticos do código não sejam executados por mais de uma thread simultaneamente. Nesses trechos do código, a exclusão mútua garante que apenas um dos fluxos está na seção crítica de cada vez, o que garante a estabilidade na sincronização dos dados comuns a várias threads.

5. O que é espera ocupada, qual sua principal desvantagem e em quais situações se aplica?
   - R: Na espera ocupada, um fluxo fica em loop verificando uma variável comum a todos os fluxos que determina se há ou não a liberação para que a seção crítica seja executada no fluxo atual. Apesar de ser simples, é desvantajoso porque ocupa a cpu enquanto ela não precisa ser utilizada de fato.

6. Como funciona o mecanismo de exclusão mútua com locks?
   - R: Funciona com a criação de travas que podem ser atribuídas a apenas um fluxo. Caso outro fluxo possua o lock, o fluxo atual é bloqueado. Quando o lock é liberado, o fluxo atual pode executar a seção crítica.