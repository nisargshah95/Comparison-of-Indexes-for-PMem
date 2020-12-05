workloads=(0 10 50)
threads=(1 2 4 8 16)

for index in dash lbtree bztree; do
    file=${index}_benchmark_result
    tps=($(grep -oP '(?<=Throughput:\s)\d+' $file | tr '\n' ' '))
    for (( i=0 ; i<=${#tps[@]}-1 ; i++ )) ; do
        tps[$i]=$(bc <<< "scale=6; ${tps[$i]}/1000000.0")
    done
    # echo ${tps[@]}
    p50=($(grep -oP '(?<=50%:\s)\d+' $file | tr '\n' ' '))
    # echo ${p50[@]}
    p99=($(grep -oP '(?<=\s99%:\s)\d+' $file | tr '\n' ' '))
    # echo ${p99[@]}

    for i in `seq 0 $((${#workloads[@]}-1))`; do
        if [[ $index = "lbtree" ]]; then
            k=$((i*5)) # file contains data for 1 2 4 8 16 threads (total 5)
        else
            k=$((i*7)) # file contains data for 1 2 4 8 16 32 64 threads (total 7)
        fi
        # echo "k = $k"
        l=${#threads[@]}
        echo "${index}_${workloads[i]}_tp = [$(echo ${tps[@]:k:l} | tr ' ' ',')]"
        echo "${index}_${workloads[i]}_p50 = [$(echo ${p50[@]:k:l} | tr ' ' ',')]"
        echo "${index}_${workloads[i]}_p99 = [$(echo ${p99[@]:k:l} | tr ' ' ',')]"
    done
done