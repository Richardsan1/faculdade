apos :: Eq a => a -> [a] -> [a]
apos _ [] = []
apos elt (x:xs)
    | elt == x  = xs 
    | otherwise = apos elt xs  
aposM :: Eq a => a -> [a] -> Maybe [a]
aposM _ [] = Nothing
aposM elt (x:xs)
    | elt == x  = Just xs
    | otherwise = aposM elt xs


