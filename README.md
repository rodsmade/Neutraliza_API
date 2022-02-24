# Neutraliza

A Neutralize é uma API escrita em C que te ajuda a traduzir sua comunicação para uma linguagem _gênero-neutra_ e _inclusiva_.

## Como utilizar

A Neutraliza está dando seus primeiros passos, e por isso ainda não é possível acessá-la via web, fazendo-se necessário baixar, compilar e subir o servidor para então poder utilizá-la na porta 4242 da máquina local (localhost:4242).

Passo 1 - baixar este repositório
``` bash
git clone https://github.com/42sp/42labs-selection-process-v2-rodsmade.git Neutraliza
```

Passo 2 - compilar o servidor
``` bash
cd Neutraliza
make
```

Passo 3 - botar o servidor de pé
``` bash
./bin/server
```

Passo 4 - abrir o neutraliza no navegador
``` bash
http://localhost:4242/home
```

Pronto! Agora é só enviar seus textos para serem neutralizados! :)

## Endpoints:
- ` GET /` -  raiz. Teste para verificar o status do servidor
- ` GET /home` - landing page. 
- ` POST /translate + body` - envie seu texto para ser traduzido!

## Tech Stack
Backend:
- Mongoose - web server [embedded]
- cJSON - parsing de json [embedded]
- libcurl - chamadas a APIs externas [comando instalar + -lcurl na compilação]

Front-end:
- HTML
- CSS
- Javascript

Integração:
- Dicio-API (link)
- Banco de dados local (SQL? SQLite?) para buscar substituições inteiras

## Árvore de diretórios
* ```bin/``` 
	Onde se encontram os binários (arquivos executáveis) do servidor (`server`) e da CLI (`neutra`) após a compilação.

* ```headerfiles/``` 
	Keeps all the custom-made .h header files used in the project.
	


## FAQ

### O que é linguagem gênero-neutra?
- É uma linguagem que reconhece a existência de mais gêneros além do masculino e feminino e que não favorece um gênero ao outro.

### Por que usar linguagem gênero-neutra?
- Pessoas não-binárias e intersexuais existem.
- Exemplo das manchetes sobre as cientistas brasileiras do Covid

### O que é linguagem inclusiva?
- Uma linguagem que é acessível para pessoas com diferentes habilidades de leitura. O uso de desinências como o X ou o @ (como em "amig@s" / "amigxs") prejudica a compreensão de pessoas que utilizam leitores de tela. 

### Por quê precisamos de um tradutor para linguagem gênero-neutra e inclusiva?
- Quebrar a resistência. Ao te entregar um texto traduzido
- Disseminar conhecimento e avançar a pauta
- mais empresas e instituições acolhendo a diversidade
- Palavras constroem mundo! Está no nosso alcance construir o mundo em que queremos viver.



