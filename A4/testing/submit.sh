if [ -z "$1" ]; then
   echo Usage: "./submit.sh <ROLL_NO>.tar.gz"
   exit 1
fi

declare -a arr=("10.6.15.118" "10.6.15.143" "10.6.15.145" "10.6.15.154" "10.6.15.178" "10.6.15.180" "10.6.15.187")
index=$(shuf -i 0-4 -n 1)
IP=${arr[index]}
#IP=10.6.15.145
echo IP $IP
curl -X POST -F file=@$1 $IP:5000/submit
