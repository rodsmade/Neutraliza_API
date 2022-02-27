# Neutraliza

A Neutraliza é uma API escrita em C que te ajuda a traduzir sua comunicação para uma linguagem **_não-binária_**, **_gênero-neutra_** e **_inclusiva_**.

Palavras importam. E palavras constroem mundo. Se a língua é viva, então temos em mãos todos os dias a possibilidade de construir uma língua que abarca a existência de todes.

A Neutraliza surge então como um esforço objetivo em direção a construir um mundo novo, mais inclusivo e receptivo da pluralidade de existências. Vamos juntes construir esse mundo, começando pelas palavras :)

## Como rodar a neutraliza localmente
---
A Neutraliza está dando seus primeiros passos, e por isso ainda não é possível acessá-la via web, fazendo-se necessário baixar, compilar e subir o servidor para então poder utilizá-la na porta 4242 da máquina local (`localhost:4242`).

Passo 1 - baixar este repositório
``` bash
git clone https://github.com/42sp/42labs-selection-process-v2-rodsmade.git Neutraliza
```

Passo 2 - compilar o servidor
``` bash
cd Neutraliza/web-server
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

## Endpoints
---
- ` GET /` -  raiz. Teste para verificar o status do servidor
- ` GET /home` - landing page. 
- ` POST /translate + body` - envie seu texto para ser traduzido!

## Tech Stack
---
### Backend:
- Mongoose - web server [embedded]
- cJSON - parsing de json [embedded]
- libcurl - chamadas a APIs externas [`apt-get install libcurl4-gnutls-dev` + -lcurl na compilação]

### Front-end:
- HTML
- CSS
- Javascript

### Integração:
- [Dicio-API](https://github.com/ThiagoNelsi/dicio-api/link) por ThiagoNelsi no Github.
- (WIP) Banco de dados local (SQL? SQLite?) para buscar substituições inteiras

## Árvore de diretórios
---
* ```bin/```
	Onde se encontram os binários (arquivos executáveis) do servidor (`neutraliza-web-server`) e da CLI (`neutre-cli`) após a compilação.

* ```headerfiles/```
	Todos os arquivos de header (.h) necessários para cada programa.
	

## Sobre os logs
---
Uma estimativa grosseira do arquivo de logs estima em média 500 bytes de informação por log, ou seja, o equivalente a 2 tweets. Nada mal!

## FAQ
---
### O que é uma linguagem gênero-neutra?
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



