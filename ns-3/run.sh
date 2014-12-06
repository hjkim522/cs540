FILE="bc-zipf-5x5"
for size in "100" "150" "200" "250" "300" "350" "400" "450" "500"
do
./waf --run "${FILE} --cacheSize=${size}"
done

