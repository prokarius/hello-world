main = do
    input <- getLine -- Scan in input
    let x = run (read input :: Integer) -- Run our shit
    print x -- Print it out

-- This is the main function. Takes an integer and returns the largest other
-- integer that can divide into it evenly 9 times.
run :: Integer -> Integer
run n = (filter (check n) [140, 139..1] !! 0)

-- This is the check function that will be passed into filter
check original divisor = checkhelper original 9 divisor

-- Recursively checks if we can divide the number 9 times.
checkhelper input numleft divisor
    | numleft == 0 = True
    | mod input divisor /= 0 = False
    | otherwise = checkhelper (div input divisor) (numleft-1) divisor

