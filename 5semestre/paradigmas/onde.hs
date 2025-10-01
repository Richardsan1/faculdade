
onde :: Eq a => a -> [a] -> Maybe Int
onde _ [] = Nothing
onde x (y:ys)
    | x == y    = Just 0
    | otherwise = case onde x ys of
                    Nothing -> Nothing
                    Just n  -> Just (n + 1)

onde' :: Eq a => a -> [a] -> Int
onde' x xs = ondeAux x xs 0
  where
    ondeAux _ [] _ = -1
    ondeAux x (y:ys) pos
        | x == y    = pos
        | otherwise = ondeAux x ys (pos + 1)
