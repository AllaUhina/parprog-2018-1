import subprocess as pr
import sys
import os

os.chdir('./build/')

print("building is doing...")
code = pr.call(["cmake", "../"])
code = pr.call("make")
if code != 0:
    print("building fail")
else:
    print("building is done.")

os.chdir('../pyscripts/')

code = pr.call(["python3", "./checker.py"])
if code != 0:
    print("error of checker")
    
