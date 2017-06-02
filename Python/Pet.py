maximum_score = 0
contestant = 0
for i in range(5):
    N = raw_input()
    score_list = [int (x) for x in N.split()]
    total_sum = 0
    for x in score_list:
        total_sum += x
    if total_sum > maximum_score:
        maximum_score = total_sum
        contestant = i+1
print str(contestant) + " " + str(maximum_score)

