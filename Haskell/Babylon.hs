{- 
First line is number of test cases
Each test case in the form of numbers and commas.
-}

import Data.Char

main = do
    ph <- getLine
    let n = (read ph :: Int)
    let cases = [1..n]
    func1 cases

func1 [] = return ()
func1 (x:xs) = do
    ph <- getLine
    print (crunch ph 0 0)
    func1 xs

-- Crunch takes a list, 
crunch :: [Char] -> Integer -> Integer -> Integer
crunch [] y z = z*60+y
crunch (',':xs) y z = crunch (xs) 0 (z*60+y)
crunch x y z = crunch (tail(x)) (y*10+toInteger(digitToInt(head(x)))) z

