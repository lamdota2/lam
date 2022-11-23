import os
import sys
import time
import subprocess
"""
useage:
    execute cmd:
        cd snapshot file
        python unzip.py Snapshot_20220926-182739_SBTS22R4_ENB_0000_000558_000000T1.zip
"""
if len(sys.argv) < 2:
    sys.exit("Please specify the dirctory ...")
    
read_path = sys.argv[1]
print('Try to unzip archives recursively under the director ' + read_path)

name = sys.argv[1]
file_name = os.path.splitext(name)[0]           
unzippath = os.path.join(file_name)

print("Prepare to auto parse snapshot")

if not os.path.exists(unzippath):
    os.mkdir(unzippath)
    print("Create directory:" + unzippath)
cmdline = 'unzip ' + os.path.join(name) + ' -d ' + unzippath
print("Unzip:" + cmdline)
sub = subprocess.Popen(cmdline,shell=True,stdout=subprocess.PIPE)
#time.sleep(0.1)
sub.wait()
cdline = 'cd ' + unzippath
sub = subprocess.Popen(cdline,shell=True,stdout=subprocess.PIPE)
#3 refers to decompressing to the second level subdirectory, and multiple formats can be specified
for i in range(1,3):
    name = sys.argv[1]
    file_name = os.path.splitext(name)[0]
    for root, dirs, files in os.walk(file_name):
        #print(root, dirs, files)
        for name in files:
            if name.endswith('.zip'):
                file_name = os.path.splitext(name)[0]           
                unzippath = os.path.join(root,file_name)

                if not os.path.exists(unzippath):
                    os.mkdir(unzippath)
                    print("Create directory:" + unzippath)
                
                cmdline = 'unzip ' + os.path.join(root,name) + ' -d ' + unzippath
                print("Unzip:" + cmdline)
                sub = subprocess.Popen(cmdline,shell=True,stdout=subprocess.PIPE)
                sub.wait()
                           
                cmdline = 'rm ' + '"' + os.path.join(root,name) + '"'
                print("Delete:" + cmdline)
                sub = subprocess.Popen(cmdline,shell=True,stdout=subprocess.PIPE)
                sub.wait()
            if  name.endswith('.tar'): 
                file_name = os.path.splitext(name)[0]           
                unzippath = os.path.join(root,file_name)

                if not os.path.exists(unzippath):
                    os.mkdir(unzippath)
                    print("Create directory:" + unzippath)
                #tar -xvf -C to the specified directory
                cmdline = 'tar -xvf ' + os.path.join(root,name) + ' -C ' + unzippath
                print("tar :" + cmdline)
                sub = subprocess.Popen(cmdline,shell=True,stdout=subprocess.PIPE)
                sub.wait()

                cmdline = 'rm ' + '"' + os.path.join(root,name) + '"'
                print("Delete tar :" + cmdline)
                sub = subprocess.Popen(cmdline,shell=True,stdout=subprocess.PIPE)
                sub.wait()
