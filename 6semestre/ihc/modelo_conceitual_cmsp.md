## Centro de Memoria Virtual do CMSP
Sistema digital para organizar, preservar e disponibilizar materiais historicos e pedagogicos do CMSP.

### 1. Metaforas principais
- Estante digital: representa o acervo.
- Linha do tempo: organiza materiais por periodo.
- Favoritos: pasta pessoal do usuario.
- Curadoria: revisao antes da publicacao.

### 2. Conceitos centrais
- Usuario: busca, visualiza e salva materiais.
- Item de acervo: possui titulo, tipo, data, descricao e status.
- Colecao: agrupa itens por tema.
- Curador: revisa, aprova ou arquiva itens.

### 3. Relacionamentos
1. Usuario (1) - (N) Item de acervo (favoritos).
2. Colecao (1) - (N) Item de acervo.
3. Curador (1) - (N) Item de acervo.

### 4. Interface x dominio
- Busca -> consulta ao acervo.
- Cartao do item -> documento resumido.
- Detalhe do item -> metadados completos.
- Favoritos -> colecao pessoal.
- Painel de curadoria -> processo editorial.

### 5. Sintese
O modelo conceitual do CMSP, em formato simples, cobre as tarefas essenciais do sistema: buscar, consultar, salvar e curar conteudo.