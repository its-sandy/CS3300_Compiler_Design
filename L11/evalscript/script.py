import os, sys

def get_power_map(string):
    power_map = {}
    delimiter = '*'
    tokens = string.split(delimiter)
    for i in range(len(tokens)):
        tokens[i] = tokens[i].strip()

    for token in tokens:
        bp = token.split('^')
        base = bp[0]
        power = 1;
        if len(bp) == 2:
            power = bp[1]
        # if base in power_map:
            # power_map[base] += int(power)
        # else:
        power_map[base] = int(power)
    return power_map

def get_line_map(filename):
    line_map = {}
    line_count=0
    for line in open(filename):
        line_count += 1
        try:
            line_map[line_count] = get_power_map(line.strip())
        except:
            line_map[line_count] = {}

    return line_count, line_map

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage python script.py file1 file2")
        print("\tfile1: expected output file")
        print("\tfile2: student output file")
        sys.exit(0)
    else:
        # print(sys.argv)
        l1, map1 = get_line_map(sys.argv[1])
        l2, map2 = get_line_map(sys.argv[2])
        # print(map1, map2)
        # result = True
        if map1 == map2:
            # score = 0.5 + score
            print("0.5")
        # for testcase, result in map1.iteritems():
            # if testcase not in map2:
                # result = False
            # else:
                # for base, power in map1[testcase]:

        else:
            if l1 != l2:
                print("0")
            else:
                c = 0
                for k, v in map1.iteritems():
                    if map2[k] == v:
                        c += 1
                print((c*0.5)/l1)

