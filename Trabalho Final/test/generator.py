import networkx as nx
import random

num_nodes = 500
num_edges = 5000
''
fPath = "./test.in"

# Gere um grafo aleatório
G = nx.gnm_random_graph(num_nodes, num_edges)

# Adicione pesos aleatórios às arestas
for edge in G.edges():
    weight = random.uniform(1.0, 10.0)  # Peso aleatório entre 1 e 10
    G[edge[0]][edge[1]]['weight'] = weight

nx.write_edgelist(G, fPath)

# Leia o conteúdo do arquivo
with open(fPath, "r") as file:
    content = file.read()

# Adicione o comentário ao início do conteúdo
content = f"# {num_nodes}\n" + content

# Reescreva o arquivo com o comentário
with open(fPath, "w") as file:
    file.write(content)