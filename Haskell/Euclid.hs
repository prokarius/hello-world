{-
Given the Euclid Game, find out who wins
1st player win if there is an even number of 1s in the repeating fraction
-}

main = do
    input <- fmap (map read.words) getLine
    if input /= [0, 0]
        then do
            output (thething input)
            main
        else return 0

thething :: [Int] -> Bool
thething a
    | a!!0 == a!!1 = True
    | a!!0 > a!!1 = func (a!!0) (a!!1) 0
    | otherwise = func (a!!1) (a!!0) 0

-- a > b, c is counter
func :: Int -> Int -> Int -> Bool
func a b c =
    if (a-b) > b
        then if c `mod` 2 == 0
            then True
            else False
        else func b (a-b) (c+1)


output :: Bool -> IO ()
output c =
    if c
        then putStrLn "Stan wins"
        else putStrLn "Ollie wins"
