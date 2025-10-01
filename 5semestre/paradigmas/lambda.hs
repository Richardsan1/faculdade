
true :: a -> a -> a
true = \x y -> x

false :: a -> a -> a  
false = \x y -> y

notOp :: (a -> a -> a) -> a -> a -> a
notOp = \p x y -> p y x

xor :: (a -> a -> a) -> (a -> a -> a) -> a -> a -> a
xor = \x y a b -> x (notOp y a b) (y a b)

toBool :: (Bool -> Bool -> Bool) -> Bool
toBool f = f True False