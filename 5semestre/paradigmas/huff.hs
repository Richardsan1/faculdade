-- Nome: Matheus Gabriel Viana Araujo - RA: 10420444
-- Nome: Richard Barbosa Sanches - RA: 10420179

import Data.List (sort, group, sortBy)
import qualified Data.Map as Map

-- Tipo da árvore de Huffman
data Huffman = Folha Int Char | No Int Huffman Huffman
  deriving (Show, Eq)

-- Peso da árvore
peso :: Huffman -> Int
peso (Folha i _)   = i
peso (No i _ _)    = i

-- Construtor de nó (já guarda o peso total)
junta :: Huffman -> Huffman -> Huffman
junta e d = No (peso e + peso d) e d

-- Cria lista de frequências (caractere, frequência)
frequencias :: String -> [(Char, Int)]
frequencias str =
  let grupos = group (sort str)
   in [(x, length xs + 1) | (x:xs) <- grupos]

-- Converte lista de frequências em folhas
freqParaFolha :: (Char, Int) -> Huffman
freqParaFolha (c, n) = Folha n c

-- Monta a árvore de Huffman
monta :: [Huffman] -> Huffman
monta [t] = t
monta (x:y:xs) =
  let novo = junta x y
   in monta (inserirOrdenado novo xs)

-- Insere um nó na lista já ordenada por peso
inserirOrdenado :: Huffman -> [Huffman] -> [Huffman]
inserirOrdenado t [] = [t]
inserirOrdenado t (x:xs)
  | peso t <= peso x = t : x : xs
  | otherwise        = x : inserirOrdenado t xs

-- Ordena lista de Huffman pelo peso
ordenar :: [Huffman] -> [Huffman]
ordenar = sortBy (\a b -> compare (peso a) (peso b))

-- Gera tabela de códigos (Map Char String)
codigos :: Huffman -> Map.Map Char String
codigos arv = Map.fromList (codigosAux arv "")
  where
    codigosAux (Folha _ c) caminho = [(c, caminho)]
    codigosAux (No _ esq dir) caminho =
      codigosAux esq (caminho ++ "0") ++
      codigosAux dir (caminho ++ "1")

-- Codifica um texto usando a tabela
codificar :: Map.Map Char String -> String -> String
codificar tabela = concatMap (\c -> tabela Map.! c)

-- Programa principal
main :: IO ()
main = do
  -- lê arquivo
  texto <- readFile "in.txt"
  -- gera lista de frequências
  let freq = frequencias texto
  -- cria folhas ordenadas
  let folhas = ordenar (map freqParaFolha freq)
  -- monta árvore
  let arvore = monta folhas
  -- gera tabela de códigos
  let tabela = codigos arvore
  -- codifica texto original
  let textoCodificado = codificar tabela texto
  -- escreve saída em arquivo
  writeFile "out.txt" textoCodificado
  putStrLn "Arquivo 'out.txt' gerado com sucesso!"
