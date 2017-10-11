main = do
    ph <- getLine
    let n = (read ph :: Float)
    x1 <- readInts
    x2 <- readInts
    let grad = m x1 x2
    let inter = c x1 grad
    let xx = x inter grad
    let yy = y inter grad xx
    let d = dist xx yy
    print (code n d 0)

readInts :: IO [Float]
readInts = fmap (map read.words) getLine

dist :: Float -> Float -> Float
dist x y = sqrt (x*x + y*y)

m :: [Float] -> [Float] -> Float
m a b
    | a!!0 /= b!!0 = (a!!1 - b!!1) / (a!!0 - b!!0)
    | otherwise = 999999999999999

c :: [Float] -> Float -> Float
c a m = a!!1 - m*(a!!0)

x :: Float -> Float -> Float
x c m = (-c*m) / (1+m*m)

y :: Float -> Float -> Float -> Float
y c m x = (m*x) + c

code :: Float -> Float -> Int -> Int
code a b c
    | (area_check a b (fromIntegral c)) = c
    | otherwise = code a b (c+1)

area_check :: Float -> Float -> Float -> Bool
area_check l dist currad
    | currad < dist = pi*currad*currad > l
    | otherwise = (area dist currad) > l

area :: Float -> Float -> Float
area a c = pi*c*c - (c*c)*(theta a c - sin (theta a c))/2

theta a c = 2 * acos (a/c)
