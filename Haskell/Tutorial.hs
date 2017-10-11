{-
Input :: [Int]
Input = [m, n, type]
Type number | 1  |  2  |  3  |  4  |  5  |  6  | 7 |
Definition  | n! | 2^n | n^4 | n^3 | n^2 | nln | n |
Print "AC" if type(n) <= m. Else print "TLE"
-}

import Data.List

main = do
    input <- fmap (map read.words) getLine
    output input

output input
    | (compareN (input!!0) (input!!1) (input!!2)) = putStrLn "AC"
    | otherwise = putStrLn "TLE"

unpower :: Integer -> Integer
unpower m = 1+ floor(logBase 2 (fromInteger m))

unfac :: Float -> Integer -> Integer
unfac m n
    | m < fromInteger(n) = n
    | otherwise = unfac (m/fromInteger(n)) (n+1) 

compareN :: Integer -> Integer -> Integer -> Bool
compareN m n t
    | t == 1 = not (n >= unfac (fromInteger(m)) 1)
    | t == 2 = not (n >= unpower m)
    | otherwise = ((generate n t) <= m)

generate :: Integer -> Integer -> Integer
generate a b -- a = n, b = type
    | b == 3 = a^4
    | b == 4 = a^3
    | b == 5 = a^2
    | b == 6 = 1 + floor(fromInteger(a) * (logBase 2 (fromInteger a)))
    | b == 7 = a

