rm -f results1.csv

TIMEFORMAT=%U
for x in {1..2};do
  for y in {0..2};do
    cache_size=$((x * 1000))
    echo "$(./main 500000 1 500000 LRU $cache_size),$cache_size,LRU" >> results1.csv
  done
done
for x in {195..200};do
  for y in {0..30};do
    cache_size=$((x * 1000))
    echo "$(./main 500000 1 500000 FIFO $cache_size),$cache_size,FIFO" >> results1.csv
    sleep 1
  done
done