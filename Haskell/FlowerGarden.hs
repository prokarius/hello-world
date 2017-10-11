import Data.Array

-- I COPIED THE SIEVE! --
-- Returns a list of primes as a list of Ints

pri = 2 : 3 : 5 : primes'
  where
    isPrime (p:ps) n = p*p > n || n `rem` p /= 0 && isPrime ps n
    primes' = 7 : filter (isPrime primes') (scanl (+) 11 $ cycle [2,4,2,4,6,2,6,4])

primes = listArray (0, 4096) (take 4096 pri)

-- Loop through the test cases
main = do
    ph <- getLine
    let n = (read ph :: Int)
    let cases = [1..n]
    func1 cases

func1 [] = return ()
func1 (x:xs) = do
    n <- readInts
    func2 (n!!0) (n!!0) (n!!1) [(0,0)]
    func1 xs

func2 0 n y z = print (func3 (array (0,40005) (z)) y 0 n)
func2 m n y a = do
    x <- readInts
    func2 (m-1) n y (a:([[(x!!0, 2*n-2*m)]]:[[(x!!0, 1+2*n-2*m)]]))

func3 listx d c n
    | c > n = look n 2047 1024
    | d > 0 = func3 listx (d-(dist (listx!(2*c)) (listx!(2*c+1)) (listx!(2*c+2)) (listx!(2*c+3)))) (c+1) n
    | otherwise = look (c-1) 2047 1024

look :: Int -> Int -> Int -> Int
look counter n k
    | k == 1 = counter
    | counter < 2 = 0
    | counter < (primes!n) = look counter (n+k) (div k 2)
    | counter > (primes!n) = look counter (n-k) (div k 2)
    | counter == (primes!n) = primes!n

readInts :: IO [Int]
readInts = fmap (map read.words) getLine

--dist :: [Float] -> [Float] -> Float
dist x1 x2 y1 y2 = sqrt ((x1 - x2)^2 + (y1 - y2)^2)

