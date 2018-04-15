-- I COPIED THE SIEVE! --
-- Returns a list of primes as a list of Ints

pri = 2 : 3 : 5 : primes'
  where
    isPrime (p:ps) n = p*p > n || n `rem` p /= 0 && isPrime ps n
    primes' = 7 : filter (isPrime primes') (scanl (+) 11 $ cycle [2,4,2,4,6,2,6,4])

primes = take 2500 pri

-- Loop through the test cases
main = do
    ph <- getLine
    let n = (read ph :: Int)
    let cases = [1..n]
    func1 cases

func1 [] = return ()
func1 (x:xs) = do
    n <- readInts
    func2 (n!!0) (round (n!!0)) [[0,0]] (n!!1)
    func1 xs

func2 0 n z y = print (func3 z y 0 n)
func2 m n a y = do
    x <- readInts
    func2 (m-1) n (a++[x]) y

func3 :: [[Float]] -> Float -> Int -> Int -> Int
func3 listx d counter n
    | counter > n = look n 0
    | d > 0 = func3 listx (d-(dist (listx!!counter) (listx!!(counter+1)))) (counter+1) n
    | otherwise = look (counter-1) 1

look :: Int -> Int -> Int
look counter n
    | counter < 2 = 0
    | counter < (primes!!n) = primes!!(n-1)
    | counter == (primes!!n) = primes!!n
    | otherwise = look counter (n+1)

readInts :: IO [Float]
readInts = fmap (map read.words) getLine

--dist :: [Float] -> [Float] -> Float
dist x y = sqrt ((x!!0 - y!!0)^2 + (x!!1 - y!!1)^2)
