# Projeto Etapa 1 Parte 2 - Modelo Conceitual e Protótipo

## Sistema Proposto
VR Memory - Centro Digital Imersivo para exploracao, estudo e curadoria de acervos historico-culturais de povos indígenas.

## 1. Modelo Conceitual

### 1.1 Metáforas do Sistema
As metáforas do sistema foram organizadas nas categorias definidas para o projeto:

#### Metáforas visuais
- Lupa para sinalizar pesquisa.
- Casa para voltar ao menu inicial.
- Livro para simbolizar documentos.
- Stickman correndo para simbolizar o acesso ao passeio virtual.
- Mão para simbolizar objetos interativos.

#### Metáforas funcionais
- Toque com o indicador para selecionar um item do menu.
- Agarrar e manipular manualmente um objeto para inspecionar.

#### Metáforas conceituais
- Andar pelo ambiente virtual.
- Manipular um objeto.

### 1.2 Conceitos/Objetos, Atributos e Ações

#### Usuario
Atributos:
- idUsuario
- nome
- perfil (visitante, curador)
- colecaoPessoal

Ações:
- entrar na experiencia
- navegar entre salas
- buscar itens e colecoes
- abrir detalhes de artefatos
- salvar item na colecao pessoal

#### Curador
Atributos:
- idCurador
- nome
- areaResponsavel
- historicoAprovacoes

Ações:
- visualizar itens em revisao
- aprovar item para exposicao
- rejeitar/remover item
- consultar metadados para decisao curatorial

#### Item do Acervo
Atributos:
- idItem
- titulo
- categoria
- origem
- periodoHistorico
- descricao
- palavrasChave
- statusCuradoria (em revisao, aprovado, rejeitado)

Ações:
- ser visualizado na galeria
- exibir metadados no painel
- ser pesquisado por nome/categoria/colecao
- ser adicionado na colecao pessoal
- receber decisao de curadoria

#### Exposicao
Atributos:
- idExposicao
- nome
- tema
- descricao
- listaDeSalas
- listaDeItens

Ações:
- organizar itens por tema
- permitir exploracao livre
- direcionar o usuario entre secoes do acervo

#### Sala Virtual
Atributos:
- idSala
- nomeSala
- temaCultural
- itensDaSala
- pontoDeEntrada

Ações:
- agrupar artefatos por contexto
- permitir deslocamento interno
- conectar salas por teleporte

#### Colecao Pessoal
Atributos:
- idColecao
- nomeColecao
- itensSalvos
- dataCriacao

Ações:
- armazenar itens favoritos
- listar itens salvos
- reabrir item salvo para consulta

#### Mecanismo de Busca
Atributos:
- termoBusca
- filtros (tipo, colecao, sala)
- resultados

Ações:
- localizar colecoes e artefatos
- levar o usuario para a sala ou artefato selecionado

### 1.3 Relacionamentos entre Conceitos/Objetos

1. Usuario (1) - (1) Colecao Pessoal
Cada usuario possui uma colecao pessoal principal no prototipo.

2. Colecao Pessoal (1) - (N) Item do Acervo
Uma colecao pessoal pode conter varios itens.

3. Item do Acervo (N) - (N) Colecao Pessoal
Um mesmo item pode ser salvo por varios usuarios.

4. Exposicao (1) - (N) Sala Virtual
Uma exposicao e composta por varias salas temáticas.

5. Sala Virtual (1) - (N) Item do Acervo
Uma sala apresenta varios itens.

6. Item do Acervo (N) - (1) Exposicao
Cada item exibido pertence a uma exposicao ativa.

7. Curador (1) - (N) Item do Acervo
Um curador pode avaliar varios itens.

8. Item do Acervo (1) - (1) Status de Curadoria
Cada item possui estado atual no fluxo curatorial.

9. Mecanismo de Busca (1) - (N) Item do Acervo/Colecao
A busca retorna conjuntos de itens e/ou colecoes para navegacao.

### 1.4 Mapeamento entre Conceitos da Interface e Conceitos do Domínio

| Conceito da Interface | Conceito do Domínio da Tarefa | Intencao de Uso |
| --- | --- | --- |
| Cena 3D imersiva | Museu/centro cultural | Simular visita guiada ou livre ao acervo |
| Sala Marajo / Sala Tupi-Guarani | Galerias temáticas | Organizar conhecimento por contexto historico-cultural |
| Artefato interativo | Peca museologica/documento cultural | Permitir observacao e interpretacao do objeto |
| Painel de informacoes do item | Ficha catalografica/museologica | Exibir origem, periodo, descricao e categoria |
| Botao Salvar na Minha Colecao | Caderno de pesquisa pessoal | Registrar itens relevantes para estudo posterior |
| Painel Minha Colecao | Acervo pessoal do visitante | Consultar rapidamente o que foi selecionado |
| Busca (Ctrl+K) | Consulta ao catalogo | Recuperar itens por nome, tema ou colecao |
| Teleporte entre salas | Deslocamento entre galerias | Reduzir esforco de navegacao no espaco virtual |
| Painel do Curador | Processo de curadoria museologica | Validar, aprovar ou rejeitar itens antes da exposicao |
| Status Em Revisao/Aprovado/Rejeitado | Estado de publicacao do acervo | Controlar qualidade e confiabilidade do conteudo |

## 2. Protótipo de Baixa Fidelidade (Navegável)

Para atender ao item 2 do enunciado, foi elaborado um protótipo navegável com foco nas interfaces principais e na interacao basica do usuario.

Arquivos do protótipo:
- prototipo_baixa_fidelidade.html (wireframe navegável)
- index.html (experiencia de exploracao imersiva)
- curadoria.html (painel de curadoria)

obs: como o envio só pode ser feito em pdf, os arquivos html estão com a extensão .html.pdf para serem enviados, mas devem ser renomeados para .html para visualizacao. para vê-los, basta abrir os arquivos com um navegador web (ex: Chrome, Firefox).

### Interfaces contempladas
1. Tela inicial (entrada no sistema)
2. Galeria/Salas temáticas
3. Painel de detalhes do item
4. Minha Colecao
5. Busca de itens e colecoes
6. Painel do Curador

### Interações implementadas
1. Navegar entre telas/salas
2. Selecionar item para abrir detalhes
3. Salvar item em Minha Colecao
4. Buscar item por termo
5. Aprovar/rejeitar item no fluxo de curadoria

### Roteiro rápido de validacao do protótipo
1. Abrir prototipo_baixa_fidelidade.html
2. Entrar na galeria e escolher uma sala temática
3. Abrir um artefato e acionar Salvar na Minha Colecao
4. Consultar a tela Minha Colecao para confirmar o item salvo
5. Ir para Painel do Curador e testar Aprovar/Rejeitar

## 3. Considerações Finais
O modelo conceitual do VR Memory alinha linguagem de interface e domínio historico-cultural, reduzindo a distancia entre o que o usuario vê no sistema e as tarefas reais de visita, estudo e curadoria de acervo. As metáforas adotadas favorecem reconhecimento, aprendizado e navegacao, enquanto o protótipo navegável demonstra as principais interações previstas para o sistema.
