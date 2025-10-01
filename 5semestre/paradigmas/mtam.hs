mtam :: [a] -> [b] -> Bool
mtam [] [] = True 
mtam [] _  = False
mtam _  [] = False
mtam (_:xs) (_:ys) = mtam xs ys 

mtam' :: [a] -> [b] -> Bool
mtam' [] [] = True
mtam' (_:xs) (_:ys) = mtam' xs ys
mtam' _ _ = False

mtam_guards :: [a] -> [b] -> Bool
mtam_guards xs ys
    | null xs && null ys = True
    | null xs || null ys = False
    | otherwise = mtam_guards (tail xs) (tail ys)