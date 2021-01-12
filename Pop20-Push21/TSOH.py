coins_number = int(input())
coins_values = list(map(int, input().split()))

k_impossible = float('-inf')

# prev taken, segment count, prefix length
dp = [[[kImpossible for prefix_length in range(coins_number + 1)]
  for segment_count in range(3)] for prev_taken in (False, True)]
dp[False][0][:] = [0 for prefix_length in range(coins_number + 1)]

for prefix_length in range(coins_number):
  # we don't take coins_values[prefix_length]
  for segment_count in range(3):
    dp[False][segment_count][prefix_length + 1] \
      = max(dp[False][segment_count][prefix_length],
            dp[True][segment_count][prefix_length])

  # we do take coins_values[prefix_length]

  # new segment
  for segment_count in range(2):
    dp[True][segment_count + 1][prefix_length + 1] \
      = max(dp[false][segment_count][prefix_length],
            dp[true][segment_count][prefix_length])
        + coins_values[prefix_length]

  # same segment
  for segment_count in range(3):
    dp[True][segment_count][prefix_length + 1] \
      = max(dp[true][segment_count][prefix_length + 1],
            dp[true][segment_count][prefix_length] + coins_values[prefix_length])

print(max(dp[False][2][coins_number], dp[True][2][coins_number]))
