gera_n :: Int -> [Int]
gera_n n
    | n <= 0    = []
    | otherwise = [1..n]

gera_n_rec :: Int -> [Int]
gera_n_rec n
    | n <= 0    = []
    | n == 1    = [1]
    | otherwise = gera_n_rec (n-1) ++ [n]

gera_n_tail :: Int -> [Int]
gera_n_tail n = gera_aux 1 n
  where
    gera_aux i limite
        | i > limite = []
        | otherwise  = i : gera_aux (i+1) limite

gera_n_acc :: Int -> [Int]
gera_n_acc n = reverse (gera_aux 1 n [])
  where
    gera_aux i limite acc
        | i > limite = acc
        | otherwise  = gera_aux (i+1) limite (i:acc)

