import subprocess as pr
import sys
import os

os.chdir('./build/')

print("building is doing...")
code = pr.call(["cmake", "../"])
code = pr.call("make")
if code != 0:
    print("building fail")
    sys.exit()
else:
    print("building is done.")

os.chdir('../pyscripts/')

ind = 1
if (len(sys.argv) > 1):
    ind = int(sys.argv[1])

if (ind == 0):
    code = pr.call(["python3", "./full_cycle_of_checks.py"])
    if code != 0:
        print("error of checker")
else:
    code = pr.call(["python3", "./checker.py"])
    if code != 0:
        print("error of checker")
