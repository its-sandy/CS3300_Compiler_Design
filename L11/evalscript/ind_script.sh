# script for individual submission evaluation
# base script credits: bikash

LAB="l11"

# Change this
BASE_FOLDER=$(pwd)

# must contain all testcases and outputfiles
# test cases must be named as input([0-9]+) and correspondings outputs as output([0-9]+)
TEST_CASES_DIR=$BASE_FOLDER/testcases

# submission folder must contain all submissions downloaded from moodle, should follow the filename convention, else rename manually
SUB_DIR=$BASE_FOLDER/submissions

# contains result files of individual students with score in the end. Named after the roll number. 
RESULT_DIR=$BASE_FOLDER/results

mkdir -p $RESULT_DIR

RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'

if [ $# -lt 1 ]
then
	echo "usage: ./ind_script.sh <ROLL NUMBER>"
	exit
fi

# argument to the script should be the roll number in CSXXBXXX format.
ROLL_NO=$1

echo "--> Evaluating ${ROLL_NO}"
echo "-------------------------"

# temp directory for extracting the files, NOTE: /tmp gets cleaned after restart
SRC_DIR=$SUB_DIR/src
mkdir -p ${SRC_DIR}

#remove (if)any previous evaluation files
rm -rf ${SRC_DIR}/${ROLL_NO}
#Doesn't recognize the format
tar -xf ${SUB_DIR}/${ROLL_NO}.tar.gz -C $SRC_DIR
#recognizes the .xz .gz. .tar formats
#tar xf ${SUB_DIR}/${ROLL_NO}.tar.gz -C $SRC_TEMP_DIR 
#tar xf ${SUB_DIR}/${ROLL_NO}.* -C $SRC_TEMP_DIR 
if [ $? -ne 0 ]
then
		echo -e "${RED}Failed to extract files${NC}"
		exit
fi 
cp $PWD/script.py $SRC_DIR/$ROLL_NO

cd $SRC_DIR/$ROLL_NO
rm -f a.out *.tab.* lex.yy.c
make > /dev/null 2>&1
if [ ! -f a.out ]; then 
	echo -e "${RED}Make failed!${NC}"
	exit
fi
echo "Make Successful"
#cd - > /dev/null
#exit

# Execute testcases
marks=0

echo "$ROLL_NO:" >> result
count=0

# output file for students
mkdir -p output
# make sure only testcase files are present in TEST_CASES_DIR
TEST_CASES_DIR="$TEST_CASES_DIR"
echo $TEST_CASES_DIR
for testcase in `ls ${TEST_CASES_DIR}/input*`
do
    #echo $testcase
    fname=`echo "$testcase" | sed "s/.*\///"`
    no=$(echo "$fname" | grep -o -E [0-9]+)
    #echo $no
    ofile="output$no"
    taofile="${TEST_CASES_DIR}/output$no"
    ./a.out < $testcase > output/$ofile 2>/dev/null
    #./a.out < $testcase 2&1 > output/$ofile
		val=$(python script.py output/$ofile $taofile | bc -l)
		#echo $val
		# remove these lines
		#echo
		#cat output/$ofile
		#echo '-----'
		#cat $taofile
		#echo '--xx---'
    ## no partial marks for any testcases
		count=$(echo "${count} + $val" | bc -l)
		echo -e "testcase $no: score=$val"
		#if [ $val -eq 0 ]
		#then
				#echo -e "testcase $no: failed" >> result
				#echo -e "testcase $no: ${RED}failed${NC}"
				#echo '--xx---'
				
		#else
				#echo -e "testcase $no: passed" >> result
				#echo -e "testcase $no: ${GREEN}passed${NC}"
		#fi
done 

marks=$(echo "$count" | bc -l)
echo "Marks: $marks" 
echo "Marks: $marks" >> result

# copy the result file, only thing that matter to us, for uploading scores
cp result $RESULT_DIR/$ROLL_NO 
rm script.py
# go back to script folder
cd - > /dev/null

