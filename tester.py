from random import seed, randint

qtd, qtd_max_palavras, seed_num = input().split()
qtd = int(qtd)
seed_num = int(seed_num)
qtd_max_palavras = int(qtd_max_palavras)

seed(seed_num)

rand = randint(0, 99)

dir = "./entradas/teste100_2/pages/" + str(rand) + ".txt"

with open(dir, "r") as file:
    palavras = file.read()
    palavras = palavras.split()
    tam = len(palavras)
    with open("./entradas/teste100_2/stopwords.txt", "r") as stopwords_file:
        stopwords = stopwords_file.read()
        for _ in range(qtd):
            cont = 0
            num_pal = randint(1, qtd_max_palavras)
            while cont < num_pal:
                palavra = palavras[randint(0, tam - 1)]
                if palavra not in stopwords:
                    if(cont < num_pal - 1):
                        print(palavra, end=" ")
                    else:
                        print(palavra, end="")
                    cont += 1
            print()
