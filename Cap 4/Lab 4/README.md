Médias por implementação:

| # de threads | main_list | main_list_rwlock | main_luigi |
|--------------|-----------|------------------|------------|
| 1            | 0.5338s   | 0.5826s          | 0.6416s    |
| 2            | 1.3153s   | 1.3513s          | 2.0015s    |
| 4            | 1.0665s   | 1.5641s          | 3.3586s    |

Podemos ver que, apesar de mais especializado para situações com grande quantidades de leituras, o grande custo de manutenção do padrão faz com que o padrão rwlock seja recomendado apenas em cenários deste tipo.
